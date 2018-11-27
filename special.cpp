#include "special.h"

#include <QPixmapCache>
#include <QtMath>
#include "game.h"
#include "shotcommand.h"

Special::Special(QGraphicsScene *scene) : Entity(scene), time_(0), firerate_(0)
{
    QPixmap p;
    if(QPixmapCache::find("friend", p))
        setPixmap(p);
}

void Special::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    Q_UNUSED(pos)
    Q_UNUSED(vel)
    Entity::init(SPECIAL_START_POS, SPECIAL_STD_VELOCITY, angle, life);
    name_ = "Special";
    air_ = true;
    enemy_ = false;
    collidable_ = false;
    destructible_ = false;
    time_ = (0);
    firerate_ = (0);
}

void Special::update(Game *game, int dt)
{
    time_ += dt;
    //first pass
    if(time_ < 2800) //2.8 sec
    {
        velocity_.setY(0.3*qFastSin(qDegreesToRadians(position_.x())));
        //aircraft attack
        firerate_+= dt;
        if(firerate_ > 50)
        {
            QPointF v = SHOT_STD_VELOCITY;
            v.setX(v.x() + velocity_.x());
            game->createPlayerShoot(position_ + boundingRect().center(), v, SPECIAL_SHOT_LIFE);
            firerate_ = 0;
        }
    }
    else if(position_.x() > (GAME_WIDTH))
    {
        position_.setX(0);
        position_.setY(GAME_HEIGHT/4);
    }
    // second pass
    if(time_ > 3000) // 3 sec
    {
        velocity_.setY(0.1*qFastSin(qDegreesToRadians(position_.x())));
        //aircraft attack
        firerate_+= dt;
        if(firerate_ > 150)
        {
            game->createPlayerBomb(position_ + boundingRect().center(), PBOMB_STD_VELOCITY, SPECIAL_BOMB_LIFE);
            firerate_ = 0;
        }
    }
     Entity::update(game, dt);

    if(time_ > 6500) //remove special after 6.5s
        life_--;

    Q_UNUSED(game);
}

