#include "helicopter.h"

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>

#include <QtMath>

#include "game.h"

Helicopter::Helicopter(QGraphicsScene *scene)
    : Entity(scene), firerate_(0), time_(0), upwards_(false)
{
    QPixmap p;
    if(SpritePackCache::find("air_enemy_6", p))
        setPixmap(p);
}

void Helicopter::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    qreal x = GAME_WIDTH + QRandomGenerator::global()->bounded(SCENE_WIDTH - GAME_WIDTH);
    qreal y = QRandomGenerator::global()->bounded(GAME_HEIGHT/2.0) + pixmap().height();
    Entity::init(QPointF(x, y), vel, angle, life);

    name_ = QString("enemy helicopter #%0").arg(QRandomGenerator::global()->bounded(200));
    setZValue((GAME_HEIGHT - y)/GAME_HEIGHT);
    firerate_ = 0;
    time_ = 0;
    //if close to top next vertical move is to go down , otherwise go upwards
    upwards_ = ((GAME_HEIGHT - position_.y())/GAME_HEIGHT) < 0.5;

    air_ = true;
    enemy_ = true;
    collidable_ = true;
    destructible_ = true;
    Q_UNUSED(pos)
    Q_UNUSED(vel)
}

void Helicopter::moveForward()
{
    if(static_cast<int>(position_.x()) % 25 == 0)
    {
        velocity_.setY(0.05 - QRandomGenerator::global()->bounded(0.1));
        velocity_.setX(-0.05);
    }
    else
    {
        velocity_.setX(HEL_STD_VELOCITY_X);
    }
}

void Helicopter::moveVertical(bool up)
{
    velocity_.setX(0);
    if(up)
    {
        velocity_.setY(-HEL_STD_VELOCITY_Y);
    }
    else
    {
        velocity_.setY(HEL_STD_VELOCITY_Y);
    }
}


void Helicopter::update(Game *game, int dt)
{
    time_ += dt;
    if(time_ < HELI_WAIT_TO_ATTACK)
    {
        moveForward();
        upwards_ = ((GAME_HEIGHT - position_.y())/GAME_HEIGHT) < 0.5;
    }
    else if(time_ < HELI_WAIT_TO_ATTACK + HELI_WAIT_TO_MOVE)
    {
        moveVertical(upwards_);
        firerate_+= dt;
        if(firerate_ > HELI_FIRE_RATE)
        {
            game->createEnemyShot(position_ + boundingRect().center(), HELI_FIRE_VELOCITY);
            firerate_ = 0;
        }
    }
    else
    {
        time_ = 0; // go back to start
    }
    if (dead())
    {
        game->createAirExplosion(this->position(), this->velocity());
    }
    Entity::update(game, dt);
}

