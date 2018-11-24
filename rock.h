#ifndef ROCK_H
#define ROCK_H

#include "entity.h"

//!
static const qreal ROCK_STD_VELOCITY_X = -0.15;
static const qreal ROCK_STD_VELOCITY_Y = 0.0;
//!
static const QPointF ROCK_STD_VELOCITY = QPointF(ROCK_STD_VELOCITY_X, ROCK_STD_VELOCITY_Y);

//!
//! \brief The Bush class - is a prop that represents vegetation on the ground
//!
class Rock : public Entity
{
public:
    Rock(QGraphicsScene *scene);
    ~Rock() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = ROCK_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;

};


#endif // ROCK_H
