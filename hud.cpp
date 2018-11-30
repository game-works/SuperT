#include "hud.h"

#include <QFont>

#include "game.h"

static const int HUD_LEVEL_X = static_cast<int>(GAME_WIDTH/2) - 30;
static const int HUD_LEVEL_Y = 5;
static const int HUD_POINTS_X = 10;
static const int HUD_POINTS_Y = 5;
static const int HUD_FPS_X = static_cast<int>(GAME_WIDTH - 70);
static const int HUD_FPS_Y = 5;
static const int HUD_LIFE_X = static_cast<int>(GAME_WIDTH/5 + 20);
static const int HUD_LIFE_Y = 5;
static const int HUD_SPECIAL_X = static_cast<int>(4*GAME_WIDTH/5 - 100);
static const int HUD_SPECIAL_Y = 5;

Hud::Hud(QGraphicsScene *scene)
    : scene_(scene),
      points_(new QGraphicsSimpleTextItem),
      level_(new QGraphicsSimpleTextItem),
      fps_(new QGraphicsSimpleTextItem),
      life_(new QGraphicsSimpleTextItem),
      special_(new QGraphicsSimpleTextItem),
      time_(0),
      blinkspecial_(false),
      blinkspecialtime_(0)
{

}

Hud::~Hud()
{
    delete points_;
    delete level_;
    delete fps_;
    delete special_;
}

void Hud::init()
{
    QFont f;
    f.setFamily("Arial");
    f.setBold(true);
    f.setPixelSize(18);

    level_->setFont(f);
    points_->setFont(f);
    fps_->setFont(f);
    life_->setFont(f);
    special_->setFont(f);

    scene_->addItem(level_);
    scene_->addItem(points_);
    scene_->addItem(fps_);
    scene_->addItem(life_);
    scene_->addItem(special_);

    level_->setPos(HUD_LEVEL_X, HUD_LEVEL_Y);
    points_->setPos(HUD_POINTS_X, HUD_POINTS_Y);
    fps_->setPos(HUD_FPS_X, HUD_FPS_Y);
    life_->setPos(HUD_LIFE_X, HUD_LIFE_Y);
    special_->setPos(HUD_SPECIAL_X, HUD_SPECIAL_Y);

    QPen pen(Qt::black, 0.3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);    level_->setPen(pen);
    points_->setPen(pen);
    fps_->setPen(pen);
    life_->setPen(pen);
    special_->setPen(pen);

    level_->setBrush(Qt::darkGreen);
    points_->setBrush(Qt::gray);
    fps_->setBrush(Qt::darkYellow);
    life_->setBrush(Qt::darkCyan);
    special_->setBrush(Qt::lightGray);

    level_->setZValue(Z_PLANE_HUD);
    points_->setZValue(Z_PLANE_HUD);
    fps_->setZValue(Z_PLANE_HUD);
    life_->setZValue(Z_PLANE_HUD);
    special_->setZValue(Z_PLANE_HUD);
    time_ = 0;
    blinkspecial_ = false;
}

void Hud::update(Game *game, int dt)
{
    time_ += dt;
    level_->setText(QString(HUD_LEVEL.arg(game->gameLevel())));
    points_->setText(QString(HUD_POINTS.arg(game->playerPoints())));
    life_->setText(QString(HUD_LIFE.arg(game->player()->life())));
    fps_->setText(QString(HUD_FPS.arg(game->fps())));
    special_->setText(QString(HUD_SPECIAL.arg(game->playerSpecials())));


    if(blinkspecial_)
    {
        if(blinkspecialtime_ > 0)
        {
            int s = blinkspecialtime_ / 1000;
            special_->setText(QString("Cooldown %0").arg(s));
        }
        else
        {
            blinkspecial_ = false;
            special_->setBrush(Qt::lightGray);
        }
        blinkspecialtime_ -= dt;
    }
}

void Hud::show(bool show)
{
    points_->setVisible(show);
    level_->setVisible(show);
    fps_->setVisible(show);
    life_->setVisible(show);
    special_->setVisible(show);
}

void Hud::displayCoolDownWarning(int currentcooldown)
{
    if(!blinkspecial_)
    {
        special_->setBrush(Qt::red);
        blinkspecial_ = true;
        blinkspecialtime_ = currentcooldown;
    }
}
