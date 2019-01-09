#include "explosion.h"

#include <QRandomGenerator>

#include "game.h"

Explosion::Explosion(QGraphicsScene *scene)
    : Entity(scene),
      pixmapPathMask_(""),
      pixmapCount_(0),
      framerate_(0),
      time_(0),
      currentPixmap_(1)
{
}

void Explosion::update(Game *game, int dt)
{
    time_ += dt;
    if(time_ > framerate_)
    {
        this->setPixmap(usePixmap(currentPixmap_));
        currentPixmap_++;
        time_ = 0;
    }
    Entity::update(game, dt);

    // 'kills' the animation when all pixmap were displayed...
    if(currentPixmap_ >= pixmapCount_)
    {
        currentPixmap_ = 0;
        life_ = -1;
    }
}

GroundExplosion::GroundExplosion(QGraphicsScene *scene) : Explosion (scene)
{
    pixmapPathMask_ = (EXP_GND_MASK);
    framerate_ = (EXP_GND_FRAMERATE);
    pixmapCount_ = (EXP_GND_COUNT);
    setZValue(position_.y()/GAME_HEIGHT); //objects close to the bottom are on top of others

    //load the pixmaps to be used by the explosion
    int i = 0;
    for(auto e : pixmapList_)
    {
        QPixmap pix;
        SpritePackCache::find(pixmapPathMask_.arg(i), pix);
        e  = pix;
        i++;
    }
    this->setPixmap(pixmapList_[0]);
}

void GroundExplosion::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    vel.setY(0);
    Entity::init(pos, vel, angle, life);
    currentPixmap_ = 1;
    time_ = 0;
    name_ = "explosion";
    collidable_ = false;
    enemy_ = false;
}

QPixmap &GroundExplosion::usePixmap(int i)
{
    return pixmapList_[i];
}

AirExplosion::AirExplosion(QGraphicsScene *scene) : Explosion(scene)
{
    pixmapPathMask_ = (EXP_AIR_MASK);
    framerate_ = (EXP_AIR_FRAMERATE);
    pixmapCount_ = (EXP_AIR_COUNT);

    int i = 0;
    //load the pixmaps to be used by the explosion
    for(auto e : pixmapList_)
    {
        QPixmap pix;
        SpritePackCache::find(pixmapPathMask_.arg(i), pix);
        e  = pix;
        i++;
    }
    this->setPixmap(pixmapList_[0]);
}

void AirExplosion::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    vel.setY(0);
    Entity::init(pos, vel, angle, life);
    currentPixmap_ = 1;
    time_ = 0;
    name_ = "explosion";
    collidable_ = false;
    enemy_ = false;

    setZValue(QRandomGenerator::global()->bounded(Z_PLANE_PROP_TOP));

}

QPixmap &AirExplosion::usePixmap(int i)
{
    return pixmapList_[i];
}
