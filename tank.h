#ifndef TANK_H
#define TANK_H

#include "entity.h"

//!
static const qreal TANK_STD_VELOCITY_X = -0.10;
static const qreal TANK_STD_VELOCITY_Y = 0.0;
//!
static const QPointF TANK_STD_VELOCITY = QPointF(TANK_STD_VELOCITY_X, TANK_STD_VELOCITY_Y);

//! in miliseconds
static const int TANK_FIRE_RATE = 300;
static const int TANK_WAIT_TO_ATTACK = 2000;
static const int TANK_WAIT_TO_MOVE = 4000;
//!
static const QPointF TANK_FIRE_A_DELTA_POS = QPointF(9, 23);
static const QPointF TANK_FIRE_B_DELTA_POS = QPointF(18, 22);
static const QPointF TANK_FIRE_VELOCITY = QPointF(-0.35,-0.2);
static const qreal TANK_FIRE_ANGLE = 45.0;

//!
//! \brief The Tank class
//!
class Tank : public Entity
{
public:
    Tank(QGraphicsScene *scene);
    ~Tank() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = TANK_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;

private:
    int firerate_;
    int time_;
};

#endif // TANK_H
