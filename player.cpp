#include "player.h"

#include <QPixmapCache>

#include "game.h"
#include "spritesheet.h"

Player::Player(QGraphicsScene *scene) : Entity(scene)
{
    QPixmap p;
    if(QPixmapCache::find("supert", p))
        setPixmap(p);
}

void Player::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    Entity::init(pos, vel, angle);
    life_ = life;
    name_ = "SuperT";
    air_ = true;
    enemy_ = false;
    collidable_ = true;
    destructible_ = true;
}

void Player::update(Game *game, int dt)
{
    qreal x = position_.x() + (velocity_.x() * dt);
    qreal y = position_.y() + (velocity_.y() * dt);

    //test against game screen boundaries
    if((x >= 0) && (x <= (GAME_WIDTH - boundingRect().width())))
    {
        position_.setX(x);
    }
    if((y >= 0) && (y <= (GAME_HEIGHT - boundingRect().height())))
    {
        position_.setY(y);
    }

    setPos(position_);

    Q_UNUSED(game);
}


void Player::hit()
{
    life_--;
}
