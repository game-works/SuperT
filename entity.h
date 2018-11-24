#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>

class Game;

// default displacement
static const qreal ENTITY_STD_DX = 3.5;
static const qreal ENTITY_STD_DY = 3.5;

// default displacement
static const QPointF ENTITY_STD_DIS = QPointF(ENTITY_STD_DX, ENTITY_STD_DY);

// default velocities
static const qreal ENTITY_STD_VX = 0.0;
static const qreal ENTITY_STD_VY = 0.0;

//!
//! \brief The Entity class - represents a game entity
//!
class Entity : public QGraphicsPixmapItem
{
public:
    Entity(QGraphicsScene *scene, QGraphicsItem *parent = nullptr);
    virtual ~Entity() = default;

    //!
    //! \brief move - move the entity to the delta x, y
    //!
    virtual void move(qreal delta_x, qreal delta_y);

    //!
    //! \brief move - move the entity to by a delta point p , and not to point p
    //!
    virtual void move(QPoint p);

    //!
    //! \brief update - the update method is called by the game main loop to update internal entity states
    //!
    virtual void update(Game* game, int dt);

    //!
    //! \brief reset - return the entity to its default (attributes) state
    //!
    virtual void reset();

    //!
    //! \brief init initialize the entity and its attributes to a specific state/value
    //! \param pos
    //! \param vel
    //!
    virtual void init(QPointF pos = QPointF(0, 0), QPointF vel = QPointF(0,0), qreal angle = 0.0, int life = 1);

    //!
    //! \brief hit - call to indicate that the entity receive a damage
    //!
    virtual void hit();

    //!
    //! \brief dead - a check to tell if the entity is dead (true) or not (false)
    //! \return
    //!
    virtual bool dead();

    /// GETTERS / SETTERS

    bool inUse() const;
    void setUse(bool use);

    QPointF position() const;
    void setPosition(const QPointF &position);

    QPointF velocity() const;
    void setVelocity(const QPointF &velocity);

    bool air() const;

    QString name() const;

    bool collidable() const;

    bool enemy() const;

    bool destructible() const;

    int life() const;

    void setLife(int life);

protected:

    //!
    //! \brief _position - vector of the position for this entity
    //!
    QPointF position_;

    //!
    //! \brief _velocity - vector of the speed for this entity
    //!
    QPointF velocity_;

    //!
    //! \brief _life - current amout of life, 0 or less means dead.
    //!
    int life_;
    int lastLife_;

    //!
    //! \brief _name - name of the entity (maybe to be displayed)
    //!
    QString name_;

     //!
    //! \brief inuse_ - control the use in the pool of entities
    //!
    bool inuse_;

    //!
    //! \brief air_ - indicates if this is air unit (true) or ground unit (false)
    //!
    bool air_;

    //!
    //! \brief collidable_ - indicate if this entity will be check against other entities collisions
    //!
    bool collidable_;

    //!
    //! \brief enemy_ - indicate if it is a friend (false) or enemy (true)
    //!
    bool enemy_;

    //!
    //! \brief destructible_ - indicates if the entity will explode (true)
    //!
    bool destructible_;

    //!
    //! \brief scene_ - reference of the rendering scene (graph data object)
    //!
    QGraphicsScene *scene_;

};

#endif // ENTITY_H
