#include "playershot.h"

#include <QGraphicsPixmapItem>
#include <QPixmapCache>
#include <QRandomGenerator>

#include "game.h"

PlayerShot::PlayerShot(QGraphicsScene* scene) : Entity(scene)
{
    QPixmap p;
    if(QPixmapCache::find("bullet", p))
        setPixmap(p);
}

void PlayerShot::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    Entity::init(pos, SHOT_STD_VELOCITY, angle);
    name_= QString("player shot #%0").arg(QRandomGenerator::global()->bounded(1000));
    setZValue(QRandomGenerator::global()->bounded(Z_PLANE_SHOTS));
    air_ = true;
    life_ = life;
    collidable_ = true;
    enemy_ = false;
    destructible_ = false;

    Q_UNUSED(vel)
}
