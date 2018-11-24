#include "aircraft.h"

#include <QPixmapCache>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

#include <QtMath>

#include "game.h"

Aircraft::Aircraft(QGraphicsScene *scene) : Entity(scene), firerate_ (0)
{
    QPixmap p;
    bool ok = false;
    // randomly attribute a model to this enemy
    switch(QRandomGenerator::global()->bounded(5))
    {
        case 0:
            ok = QPixmapCache::find("air_enemy_1", p);
            break;
        case 1:
            ok = QPixmapCache::find("air_enemy_2", p);
            break;
        case 2:
            ok = QPixmapCache::find("air_enemy_3", p);
            break;
        case 3:
            ok = QPixmapCache::find("air_enemy_4", p);
            break;
        case 4:
            ok = QPixmapCache::find("air_enemy_5", p);
            break;
    }
    if(ok)
        setPixmap(p);
}

void Aircraft::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    qreal x = GAME_WIDTH + QRandomGenerator::global()->bounded(SCENE_WIDTH - GAME_WIDTH);
    qreal y = QRandomGenerator::global()->bounded(GAME_HEIGHT/2.0) + pixmap().height();
    Entity::init(QPointF(x, y), vel, angle, life);

    air_ = true;
    enemy_ = true;
    collidable_ = true;
    destructible_ = true;
    name_ = QString("enemy aircraft #%0").arg(QRandomGenerator::global()->bounded(500));
    firerate_ = 0;
    setZValue(GAME_HEIGHT/(GAME_HEIGHT-y));

    Q_UNUSED(pos)
    Q_UNUSED(vel)
}

void Aircraft::update(Game *game, int dt)
{
    //aircraft movement
    velocity_.setY(0.1*qFastSin(qDegreesToRadians(position_.x())));

    //aircraft attack
    firerate_+= dt;
    if(firerate_ > AIR_FIRE_RATE)
    {
        game->createEnemyShot(position_ + boundingRect().center(), ES_STD_VELOCITY);
        firerate_ = 0;
    }
    Entity::update(game, dt);
}
