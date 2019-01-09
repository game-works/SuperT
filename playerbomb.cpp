#include "playerbomb.h"

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

#include <QtMath>

#include "game.h"

PlayerBomb::PlayerBomb(QGraphicsScene* scene) : Entity(scene)
{
    QPixmap p;
    if(SpritePackCache::find("bomb", p))
        setPixmap(p);
}

void PlayerBomb::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    Entity::init(pos, SHOT_STD_VELOCITY, angle, life);
    name_= QString("player shot #%0").arg(QRandomGenerator::global()->bounded(1000));
    setZValue(QRandomGenerator::global()->bounded(Z_PLANE_SHOTS));
    air_ = true;
    collidable_ = true;
    enemy_ = false;
    destructible_ = false;
    velocity_ = PBOMB_STD_VELOCITY;
    Q_UNUSED(vel)
}
