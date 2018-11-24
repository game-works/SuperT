#ifndef SPECIAL_H
#define SPECIAL_H

#include "entity.h"

//!
//! \brief SPECIAL_START_POS
//!
static const QPointF SPECIAL_START_POS = QPointF(-50,0);

//!
//! \brief SPECIAL_STD_VELOCITY
//!
static const QPointF SPECIAL_STD_VELOCITY = QPointF(0.2, 0.0);


//!
//! \brief The Special class
//!
class Special : public Entity
{
public:
    Special(QGraphicsScene *scene);
    ~Special() override = default;

    // Entity interface
public:

    void init(QPointF pos = QPointF(0.0, 0.0), QPointF vel = QPointF(0.0, 0.0), qreal angle = 0.0, int life = 1) override;
    void update(Game *game, int dt) override;

private:
    int time_;
    int firerate_;
};



#endif // SPECIAL_H
