#include "artilleryshot.h"

#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QtMath>

#include "game.h"

ArtilleryShot::ArtilleryShot(QGraphicsScene* scene)
    : Entity(scene), time_(0.0), vx_(0.0), vy_(0.0), x_(0.0), y_(0.0),
      angle_(0.0), vel_(0.0), speed_(0.0)
{
    QPixmap p;
    if(SpritePackCache::find("gnd_enemy_bullet_1", p))
        setPixmap(p);
}

void ArtilleryShot::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    Entity::init(pos, vel, angle, life);

    name_= QString("artillery shot #%0").arg(QRandomGenerator::global()->bounded(1000));
    setZValue(QRandomGenerator::global()->bounded(Z_PLANE_SHOTS));

    air_ = true;
    collidable_ = true;
    enemy_ = true;
    destructible_ = false;
    velocity_ = QPointF();

    time_ = (0.0);
    angle_ = AS_MAX_ANGLE - QRandomGenerator::global()->bounded(AS_MIN_ANGLE);
    vel_ = AS_MAX_VEL - QRandomGenerator::global()->bounded(AS_MIN_VEL);
    speed_ = AS_MAX_SPEED - QRandomGenerator::global()->bounded(AS_MIN_SPEED);
    // calc initial velocities in x and y
    vx_ = vel_ * qFastCos(qDegreesToRadians(angle_));
    vy_ = vel_ * qFastSin(qDegreesToRadians(angle_));
    x_ = pos.x();
    y_ = pos.y();
    setPos(pos);
    //rotate relative to the center of the sprite (see QGraphicsView conventions)
    setTransformOriginPoint(boundingRect().center());
    setRotation(270+angle_); //rotations in qt are clockwise

   // Q_UNUSED(vel)
   // Q_UNUSED(angle)
}

void ArtilleryShot::update(Game *game, int dt)
{
    // apply the motion equation to the prejectille
    time_ += (dt/1000.0) * speed_; // speed_ up/down shot travel
    qreal x = x_ - (vx_ * time_);
    qreal y = y_ - (vy_ * time_ - (GRAVITY/2.0) * time_ * time_);
    position_.setX(x);
    position_.setY(y);
    setPos(x, y);
    // calculate the bullet rotation effect
    qreal vy = vy_ - GRAVITY * time_;
    qreal a = qRadiansToDegrees(qAtan(vy/vx_));
    // 270 degree is necessary to keep the projectile angle oriented to the correct position
    setRotation(270+a);

    Q_UNUSED(game);
}
