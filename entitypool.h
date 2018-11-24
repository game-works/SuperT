#ifndef ENTITYPOOL_H
#define ENTITYPOOL_H

#include "entity.h"
#include <QSharedPointer>
#include <QDebug>

class QGraphicsScene;

//!
//! \brief The EntityPool class - this template create caches for entities of the game to be reused
//!
//!
template <class T, int POOL_SIZE>
class EntityPool final
{
public:
    //!
    //! \brief EntityPool
    //!
    EntityPool(QGraphicsScene *scene) : lastused(0)
    {
        for(int i = 0 ; i < POOL_SIZE ; i++)
        {
            QSharedPointer<T> t = QSharedPointer<T>(new T(scene));
            t->setUse(false);
            pool_[i] = t;
        }
    }

    //!
    ~EntityPool()
    {
        for(int i = 0 ; i < POOL_SIZE ; i++)
        {
            pool_[i].clear();
        }
    }

    //! this class is just a helper class
    Q_DISABLE_COPY(EntityPool)

public:

    QSharedPointer<T> useEntity()
    {
        QSharedPointer<T> e = pool_[lastused];
        do
        {
            if(!e.isNull() && !e->inUse())
            {
                e->setUse(true);
            }
            lastused++;
        }
        while(lastused < (POOL_SIZE - 1) && pool_[lastused]->inUse());

        if(lastused >= POOL_SIZE)
        {
            lastused = 0;
            qDebug() << typeid(T).name() << " - pool buffer overflow - " << endl;
        }
        return e;
    }


private:

    //!
    //! \brief pool_ - the data cache of objects to be used
    //!
    QSharedPointer<T> pool_[POOL_SIZE];

    //!
    //! \brief lastused - a memory indicating the last used object from the pool
    //!
    int lastused;
};

#endif // ENTITYPOOL_H
