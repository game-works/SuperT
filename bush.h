#ifndef BUSH_H
#define BUSH_H

#include "entity.h"

//!
static const qreal BUSH_STD_VELOCITY_X = -0.15;
static const qreal BUSH_STD_VELOCITY_Y = 0.0;
//!
static const QPointF BUSH_STD_VELOCITY = QPointF(BUSH_STD_VELOCITY_X, BUSH_STD_VELOCITY_Y);

//!
//! \brief The Bush class - is a prop that represents vegetation on the ground
//!
class Bush : public Entity
{
public:
    Bush(QGraphicsScene *scene);
    ~Bush() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = BUSH_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;

};

#endif // BUSH_H
