#include "enemyshot.h"

#include <QGraphicsPixmapItem>
#include <QPixmapCache>
#include <QRandomGenerator>

#include "game.h"

EnemyShot::EnemyShot(QGraphicsScene* scene) : Entity(scene)
{
    QPixmap p;
    if(SpritePackCache::find("air_enemy_bullet_1", p))
        setPixmap(p);
}

void EnemyShot::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    Entity::init(pos, vel, angle, life);
    name_= QString("enemy shot #%0").arg(QRandomGenerator::global()->bounded(1000));
    setZValue(QRandomGenerator::global()->bounded(Z_PLANE_SHOTS));
    air_ = true;
    collidable_ = true;
    enemy_ = true;
    destructible_ = false;

    Q_UNUSED(vel)
}
