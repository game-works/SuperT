#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "entity.h"

//!
static const qreal AIR_STD_VELOCITY_X = -0.15;
static const qreal AIR_STD_VELOCITY_Y = 0.0;
//!
static const QPointF AIR_STD_VELOCITY = QPointF(AIR_STD_VELOCITY_X, AIR_STD_VELOCITY_Y);
//!
static const int AIR_FIRE_RATE = 500;

//!
//! \brief The Aircraft class - defines the aircraft enemy entity
//!
class Aircraft : public Entity
{
public:
    Aircraft(QGraphicsScene *scene);
    ~Aircraft() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = AIR_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;

private:

    int firerate_;

};

#endif // AIRCRAFT_H
