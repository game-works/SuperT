#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

//!
//! \brief PLAYER_START_POS
//!
static const QPointF PLAYER_START_POS = QPointF(50, 100);

static const int PLAYER_START_LIFE = 30;

//!
//! \brief PLAYER_STD_VELOCITY
//!
static const QPointF PLAYER_STD_VELOCITY = QPointF(0.01,0.02);

class SpriteSheet;

//!
//! \brief The Player class
//!
class Player : public Entity
{
public:
    Player(QGraphicsScene *scene);
    ~Player() override = default;

    // Entity interface
public:
    void init(QPointF pos = QPointF(0.0, 0.0), QPointF vel = QPointF(0.0, 0.0), qreal angle = 0.0, int life = PLAYER_START_LIFE) override;
    void update(Game *game, int dt) override;
    void hit() override;

};

#endif // PLAYER_H
