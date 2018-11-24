#ifndef ENEMYSHOT_H
#define ENEMYSHOT_H

#include "entity.h"

//
static const QPointF ES_STD_VELOCITY = QPointF(-0.3, 0.0);

class QGraphicsScene;

//!
//! \brief The EnemyShot class - represents a enemy shot (simple small bullet with straight trajectory)
//!
class EnemyShot : public Entity
{
public:
    EnemyShot(QGraphicsScene*);
    virtual ~EnemyShot() override = default;

    // Entity interface
public:
    void init(QPointF pos, QPointF vel = ES_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;

};


#endif // ENEMYSHOT_H
