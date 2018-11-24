#include "tank.h"

#include <QPixmapCache>
#include <QRandomGenerator>

#include "game.h"

Tank::Tank(QGraphicsScene *scene) : Entity (scene) , firerate_(0), time_(0)
{
    QPixmap p;
    if(QPixmapCache::find("tank", p))
        setPixmap(p);
}

void Tank::init(QPointF pos, QPointF vel, qreal angle, int life)
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
    name_ = QString("enemy tank #%0").arg(QRandomGenerator::global()->bounded(500));
    setZValue(y/GAME_HEIGHT); //objects close to the bottom are on top of others
    Q_UNUSED(pos)
    Q_UNUSED(vel)
}

void Tank::update(Game *game, int dt)
{
    time_ += dt;
    if(time_ < TANK_WAIT_TO_ATTACK)
    {
        velocity_.setX(TANK_STD_VELOCITY_X);
    }
    else if(time_ < TANK_WAIT_TO_MOVE)
    {
        velocity_.setX(0); // stop to fire
        firerate_+= dt;
        if(firerate_ > TANK_FIRE_RATE)
        {
            game->createEnemyShot(position_ + TANK_FIRE_A_DELTA_POS, TANK_FIRE_VELOCITY, TANK_FIRE_ANGLE);
            game->createEnemyShot(position_ + TANK_FIRE_B_DELTA_POS, TANK_FIRE_VELOCITY, TANK_FIRE_ANGLE);
            firerate_ = 0;
        }
    }
    else
    {
        time_ = 0; // go back to start
    }
    Entity::update(game, dt);
}


