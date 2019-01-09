#ifndef VULTURE_H
#define VULTURE_H

#include "entity.h"

//!
static const qreal VUL_STD_VELOCITY_X = -0.10;
static const qreal VUL_STD_VELOCITY_Y = 0.0;
//!
static const QPointF VUL_STD_VELOCITY = QPointF(VUL_STD_VELOCITY_X, VUL_STD_VELOCITY_Y);
//! in miliseconds
static const int VUL_WAIT_TO_ATTACK = 5500;
static const int VUL_WAIT_TO_MOVE = 3000;


class SpriteSheet;

//!
//! \brief The Vulture class
//!
class Vulture : public Entity
{
public:
    Vulture(QGraphicsScene *scene);
    ~Vulture() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0, 0), QPointF vel = VUL_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;


private:
    int timer_;
    int wait_;


};
#endif // VULTURE_H
