#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "entity.h"

//!
static const qreal EXP_GND_STD_VELOCITY_X = -0.20;
static const qreal EXP_GND_STD_VELOCITY_Y = 0.0;

static const qreal EXP_AIR_STD_VELOCITY_X = -0.10;
static const qreal EXP_AIR_STD_VELOCITY_Y = 0.05;
//!
static const QPointF EXP_GND_STD_VELOCITY = QPointF(EXP_GND_STD_VELOCITY_X, EXP_GND_STD_VELOCITY_Y);
static const QPointF EXP_AIR_STD_VELOCITY = QPointF(EXP_AIR_STD_VELOCITY_X, EXP_AIR_STD_VELOCITY_Y);

static const QString EXP_AIR_MASK = "air_exp_%0";
static const int EXP_AIR_COUNT = 16;
static const QString EXP_GND_MASK = "gnd_exp_%0";
static const int EXP_GND_COUNT = 15;

static const int EXP_AIR_FRAMERATE = 100;
static const int EXP_GND_FRAMERATE = 100;

//!
//! \brief The Explosion class - abstract class representing a sequence of explosion
//!
class Explosion : public Entity
{
public:
    Explosion(QGraphicsScene *scene);
    virtual ~Explosion() override = default;

    // Entity interface
public:
    virtual void init(QPointF pos = QPointF(0, 0), QPointF vel = QPointF(0,0), qreal angle = 0.0, int life = 1) override = 0;
    void update(Game *game, int dt) override;

public:
    virtual QPixmap& usePixmap(int i) = 0;

protected:

    QString pixmapPathMask_;

    int pixmapCount_;

    int framerate_;

    int time_;

    int currentPixmap_;

};

//!
//! \brief The GroundExplosion class
//!
class GroundExplosion : public Explosion
{
public:
    GroundExplosion(QGraphicsScene *scene);
    virtual ~GroundExplosion() override = default;

    // Entity interface
public:
    void init(QPointF pos, QPointF vel = EXP_GND_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;

    // Explosion interface
public:
    QPixmap &usePixmap(int i) override;

private:
    QPixmap pixmapList_[EXP_GND_COUNT];

};

class AirExplosion : public Explosion
{
public:
    AirExplosion(QGraphicsScene *scene);
    virtual ~AirExplosion() override = default;

    // Entity interface
public:
    void init(QPointF pos, QPointF vel = EXP_AIR_STD_VELOCITY, qreal angle = 0.0, int life = 1) override;

    // Explosion interface
public:
    QPixmap &usePixmap(int i) override;

private:
    QPixmap pixmapList_[EXP_AIR_COUNT];

};

#endif // EXPLOSION_H
