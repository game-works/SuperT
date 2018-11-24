#include "cloud.h"
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QPixmapCache>

#include "game.h"

Cloud::Cloud(QGraphicsScene *scene) : Entity(scene)
{
    QPixmap p;
    bool ok = false;
    // randomly attribute a model to this cloud
    switch(QRandomGenerator::global()->bounded(3))
    {
        case 0:
            ok = QPixmapCache::find("cloud_1", p);
            break;
        case 1:
            ok = QPixmapCache::find("cloud_2", p);
            break;
        case 2:
            ok = QPixmapCache::find("cloud_3", p);
            break;
    }
    if(ok)
        setPixmap(p);
}

void Cloud::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    qreal x = GAME_WIDTH + QRandomGenerator::global()->bounded(SCENE_WIDTH - GAME_WIDTH);
    qreal y = QRandomGenerator::global()->bounded(GAME_HEIGHT / 3.0) ;//+ pixmap().height();

    Entity::init(QPointF(x, y), vel, angle, life);

    qreal ratio = (GAME_HEIGHT - y)/GAME_HEIGHT;
    // higher clouds are bigger, lower ones are smaller
    setScale(ratio);
    // lower clouds ones are more translucid
    setOpacity(ratio);
    // higher clouds are faster, lower slower...
    velocity_.setX(CLOUD_STD_VELOCITY_X * ratio);

    setZValue(QRandomGenerator::global()->bounded(Z_PLANE_PROP_TOP));
    name_ = QString("cloud #%0").arg(QRandomGenerator::global()->bounded(100));
    air_ = true;
    enemy_ = false;
    collidable_ = false;
    destructible_ = false;

    Q_UNUSED(pos)
    Q_UNUSED(vel)
}
