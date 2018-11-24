#include "rock.h"

#include <QPixmapCache>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

#include <QDebug>

#include "game.h"

Rock::Rock(QGraphicsScene *scene) : Entity(scene)
{
    QPixmap p;
    bool ok = false;
    // randomly attribute a model to this bush
    switch(QRandomGenerator::global()->bounded(2))
    {
        case 0:
            ok = QPixmapCache::find("rock_01", p);
            break;
        case 1:
            ok = QPixmapCache::find("rock_02", p);
            break;
    }
    if(ok)
        setPixmap(p);
}

void Rock::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    qreal x = GAME_WIDTH + QRandomGenerator::global()->bounded(SCENE_WIDTH - GAME_WIDTH);
    qreal y = GAME_HEIGHT - QRandomGenerator::global()->bounded(GAME_HEIGHT / 3.0) - pixmap().height();
    Entity::init(QPointF(x, y), vel, angle, life);

    qreal ratio = qAbs(QRandomGenerator::global()->bounded(1.0) - ((GAME_HEIGHT - y)/GAME_HEIGHT));
    // the lower the bush is on screen it will be bigger, more opaque and faster
    setScale(ratio);
    setOpacity(ratio);
    velocity_.setX(ROCK_STD_VELOCITY_X * ratio);

    setZValue(Z_PLANE_PROP);

    name_ = QString("rock #%0").arg(QRandomGenerator::global()->bounded(500));
    air_ = false;
    collidable_ = false;
    enemy_ = false;
    destructible_ = false;

    Q_UNUSED(pos)
    Q_UNUSED(vel)
}

