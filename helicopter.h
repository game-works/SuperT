#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "entity.h"

//!
//! \brief HEL_STD_VELOCITY
//!
static const qreal HEL_STD_VELOCITY_X = -0.10;
static const qreal HEL_STD_VELOCITY_Y = 0.05;
//!
static const QPointF HEL_STD_VELOCITY = QPointF(HEL_STD_VELOCITY_X, HEL_STD_VELOCITY_Y);

//! in miliseconds
static const int HELI_FIRE_RATE = 150;
static const int HELI_WAIT_TO_ATTACK = 4000;
static const int HELI_WAIT_TO_MOVE = 1500;
//!
static const QPointF HELI_FIRE_VELOCITY = QPointF(-0.45,0.0);

//!
//! \brief The Helicopter class
//!
class Helicopter  : public Entity
{
public:
    Helicopter(QGraphicsScene *scene);
    ~Helicopter() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = HEL_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;

private:
    void moveForward();
    void moveVertical(bool up);

private:
    int firerate_;
    int time_;
    bool upwards_;
};
#endif // HELICOPTER_H
