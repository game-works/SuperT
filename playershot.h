#ifndef PLAYERSHOT_H
#define PLAYERSHOT_H

#include "entity.h"

//!
static const qreal SHOT_STD_VELOCITY_X = 0.45;
static const qreal SHOT_STD_VELOCITY_Y = 0.0;
//!
static const QPointF SHOT_STD_VELOCITY = QPointF(SHOT_STD_VELOCITY_X, SHOT_STD_VELOCITY_Y);

class QGraphicsScene;

//!
//! \brief The PlayerShot class
//!
class PlayerShot : public Entity
{
public:
    PlayerShot(QGraphicsScene*);
    virtual ~PlayerShot() override = default;

    // Entity interface
public:
    void init(QPointF pos, QPointF vel, qreal angle = 0.0, int life = 1) override;

};

#endif // PLAYERSHOT_H
