#ifndef CLOUD_H
#define CLOUD_H

#include "entity.h"

//!
static const qreal CLOUD_STD_VELOCITY_X = -0.10;
static const qreal CLOUD_STD_VELOCITY_Y = 0.0;
//!
static const QPointF CLOUD_STD_VELOCITY = QPointF(CLOUD_STD_VELOCITY_X, CLOUD_STD_VELOCITY_Y);

//!
//! \brief The Cloud class - representes a cloud prop on the scene (placed in the air)
//!
class Cloud : public Entity
{
public:
    Cloud(QGraphicsScene *scene);
    ~Cloud() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = CLOUD_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;

};

#endif // CLOUD_H
