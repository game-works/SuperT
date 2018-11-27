#include "entity.h"

#include "game.h"

Entity::Entity(QGraphicsScene *scene, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    position_(QPointF(0.0, 0.0)),
    velocity_(QPointF(0.0, 0.0)),
    life_(0),
    lastLife_(life_),
    name_(""),
    inuse_(false),
    air_(false),
    collidable_(false),
    enemy_(false),
    destructible_(false),
    scene_(scene)
{
}

void Entity::move(qreal delta_x, qreal delta_y)
{
    position_ += QPointF(delta_x, delta_y);
}

void Entity::move(QPoint p)
{
    position_ += p;
}

void Entity::update(Game *game, int dt)
{
    position_.setX(position_.x() + (velocity_.x() * dt));
    position_.setY(position_.y() + (velocity_.y() * dt));
    setPos(position_);

    if(lastLife_ != life_)
    {
        lastLife_ = life_;
    }
    else
    {
        this->setOpacity(1.0);
    }

    Q_UNUSED(game);
}

void Entity::reset()
{
    position_ = (QPointF(0.0, 0.0));
    velocity_ = (QPointF(0.0, 0.0));
    life_ = (0.0f);
    name_.clear();
    inuse_ = (false);
    air_ = (false);
    collidable_ = (false);
    enemy_ = (false);
    destructible_ = (false);

    setOpacity(1.0);
    setScale(1.0);
    setZValue(Z_PLANE_ENTITIES);
    setVisible(false);
    setRotation(0.0);
    scene_->removeItem(this);
}

void Entity::init(QPointF pos, QPointF vel, qreal angle, int life)
{
    position_ = pos;
    velocity_ = vel;
    life_ = life;
    //name_.clear();
    inuse_ = (false);
    air_ = (false);
    collidable_ = (false);
    enemy_ = (false);
    destructible_ = (false);

    setZValue(Z_PLANE_ENTITIES);
    setVisible(true);
    if(!scene_->items().contains(this))
        scene_->addItem(this);
    setPos(position_);
    velocity_ = vel;
    setRotation(angle);
}

void Entity::hit()
{
    this->setOpacity(0.2);
    --life_; //decrease life
}

bool Entity::dead()
{
    return life_ <= 0;
}

bool Entity::air() const
{
    return air_;
}

QString Entity::name() const
{
    return name_;
}

bool Entity::collidable() const
{
    return collidable_;
}

bool Entity::enemy() const
{
    return enemy_;
}

bool Entity::destructible() const
{
    return destructible_;
}

int Entity::life() const
{
    return life_;
}

void Entity::setLife(int life)
{
    life_ = life;
}

bool Entity::inUse() const
{
    return inuse_;
}

void Entity::setUse(bool use)
{
    inuse_ = use;
}

QPointF Entity::position() const
{
    return position_;
}

void Entity::setPosition(const QPointF &position)
{
    position_ = position;
}

QPointF Entity::velocity() const
{
    return velocity_;
}

void Entity::setVelocity(const QPointF &velocity)
{
    velocity_ = velocity;
}
