#include "vulture.h"

#include <QPixmapCache>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

#include "game.h"

Vulture::Vulture(QGraphicsScene *scene) : Entity(scene), timer_(0), wait_(0)
{
    QPixmap p;
    if(QPixmapCache::find("vulture", p))
        setPixmap(p);
}

void Vulture::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    qreal x = GAME_WIDTH + QRandomGenerator::global()->bounded(SCENE_WIDTH - GAME_WIDTH);
    qreal y = QRandomGenerator::global()->bounded(GAME_HEIGHT / 2.0) + pixmap().height();
    Entity::init(QPointF(x, y), VUL_STD_VELOCITY, angle, life);

    timer_ = 0;
    wait_ = VUL_WAIT_TO_MOVE + QRandomGenerator::global()->bounded(VUL_WAIT_TO_ATTACK);
    setZValue(GAME_HEIGHT/(GAME_HEIGHT-y));
    name_ = QString("vulture #%0").arg(QRandomGenerator::global()->bounded(50));
    air_ = true;
    enemy_ = true;
    collidable_ = true;
    destructible_ = true;
    Q_UNUSED(pos)
    Q_UNUSED(vel)
}

void Vulture::update(Game *game, int dt)
{
    timer_ += dt;
    velocity_.setY(0.5 - QRandomGenerator::global()->bounded(1.0));
    if(timer_ > VUL_WAIT_TO_MOVE && timer_ < wait_)
    {
        velocity_.setX(0); // stops for a random period of time
    }
    else if(timer_ > wait_) // full attack
    {
        velocity_.setX(-1.0 + QRandomGenerator::global()->bounded(0.5));
    }
    else // normal move
    {
         velocity_.setX(VUL_STD_VELOCITY_X);
    }
    Entity::update(game, dt);
}
