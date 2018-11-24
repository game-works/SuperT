#ifndef ARTILLERYSHOT_H
#define ARTILLERYSHOT_H

#include "entity.h"

//  minimum and max launch vel
static const qreal AS_MIN_VEL = 40;
static const qreal AS_MAX_VEL = 100;
// min and max launch angle
static const qreal AS_MIN_ANGLE = 45;
static const qreal AS_MAX_ANGLE = 70;
// min and max launch speed
static const qreal AS_MIN_SPEED = 1;
static const qreal AS_MAX_SPEED = 4;

class QGraphicsScene;

//!
//! \brief The ArtilleryShot class - is a entity representing a shot from ground artillery
//! the shot movement is calculated using projectile motion formulas
//!
class ArtilleryShot : public Entity
{
public:
    ArtilleryShot(QGraphicsScene*);
    virtual ~ArtilleryShot() override = default;

    // Entity interface
public:
    void init(QPointF pos, QPointF vel, qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;

private:

    qreal time_; // advances animation timing
    qreal vx_; // starting velocity in x, calculated
    qreal vy_; // starting velocity in y, calculated
    qreal x_; // current position in x, calculated
    qreal y_; // current position in y, calculated
    qreal angle_; // shooting angle
    qreal vel_; // shooting velocity
    qreal speed_; // shooting speed multiplier
};

#endif // ARTILLERYSHOT_H
