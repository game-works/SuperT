#ifndef ARTILLERY_H
#define ARTILLERY_H

#include "entity.h"
//!
static const qreal ART_STD_VELOCITY_X = -0.05;
static const qreal ART_STD_VELOCITY_Y = 0.0;
//!
static const QPointF ART_STD_VELOCITY = QPointF(ART_STD_VELOCITY_X, ART_STD_VELOCITY_Y);
//! in miliseconds
static const int ART_FIRE_RATE = 3000;
static const int ART_WAIT_TO_ATTACK = 4000;
static const int ART_WAIT_TO_MOVE = 8000;
//!
static const QPointF ARTILLERY_SHOT_DELTA_POS = QPointF(15, 3);

//!
//! \brief The Artillery class - represents a ground anti-aircraft enemy, it shoots projectiles to the air
//!
class Artillery : public Entity
{
public:
    Artillery(QGraphicsScene *scene);
    ~Artillery() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = ART_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;

private:
    int firerate_;
    int time_;
};



#endif // ARTILLERY_H
