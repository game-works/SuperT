#ifndef PLAYERBOMB_H
#define PLAYERBOMB_H

#include "entity.h"

//!
static const qreal PBOMB_STD_VELOCITY_X = 0.05;
static const qreal PBOMB_STD_VELOCITY_Y = 0.25;
//!
static const QPointF PBOMB_STD_VELOCITY = QPointF(PBOMB_STD_VELOCITY_X, PBOMB_STD_VELOCITY_Y);

class QGraphicsScene;

//!
//! \brief The PlayerBomb class
//!
class PlayerBomb : public Entity
{
public:
    PlayerBomb(QGraphicsScene*);
    virtual ~PlayerBomb() override = default;

    // Entity interface
public:
    void init(QPointF pos, QPointF vel, qreal angle = 0.0, int life = 1) override;

};

#endif // PLAYERBOMB_H
