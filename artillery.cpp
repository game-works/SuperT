#include "artillery.h"

#include <QPixmapCache>
#include <QRandomGenerator>

#include "game.h"

Artillery::Artillery(QGraphicsScene *scene) : Entity (scene), firerate_(0), time_(0)
{
    QPixmap p;
    if(QPixmapCache::find("artillery", p))
        setPixmap(p);
}

void Artillery::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    qreal x = GAME_WIDTH + QRandomGenerator::global()->bounded(SCENE_WIDTH - GAME_WIDTH);
    qreal y = GAME_HEIGHT - QRandomGenerator::global()->bounded(GAME_HEIGHT/3.0) - pixmap().height();
    Entity::init(QPointF(x, y), vel, angle, life);

    air_ = false;
    enemy_ = true;
    collidable_ = true;
    destructible_ = true;
    firerate_ = 0;
    time_ = 0;
    name_ = QString("enemy artillery #%0").arg(QRandomGenerator::global()->bounded(500));
    setZValue(y/GAME_HEIGHT); //objects close to the bottom are on top of others

    Q_UNUSED(pos)
    Q_UNUSED(vel)
}

void Artillery::update(Game *game, int dt)
{
    time_ += dt;
    if(time_ < ART_WAIT_TO_ATTACK)
    {
        velocity_.setX(ART_STD_VELOCITY_X);
    }
    else if(time_ < ART_WAIT_TO_MOVE)
    {
        velocity_.setX(0);
        firerate_+= dt;
        if(firerate_ > ART_FIRE_RATE)
        {
            game->createArtilleryShot(position_ + ARTILLERY_SHOT_DELTA_POS);
            firerate_ = 0;
        }
    }
    else
    {
        time_ = 0; // go back to start
    }
    Entity::update(game, dt);
}
