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
      points_(new QGraphicsTextItem),
      level_(new QGraphicsTextItem),
      fps_(new QGraphicsTextItem),
      life_(new QGraphicsTextItem),
      special_(new QGraphicsTextItem),
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
    f.setPixelSize(16);

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

    level_->setDefaultTextColor(Qt::darkGreen);
    points_->setDefaultTextColor(Qt::black);
    fps_->setDefaultTextColor(Qt::darkYellow);
    life_->setDefaultTextColor(Qt::darkCyan);
    special_->setDefaultTextColor(Qt::darkBlue);

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
    level_->setPlainText(QString(HUD_LEVEL.arg(game->gameLevel())));
    points_->setPlainText(QString(HUD_POINTS.arg(game->playerPoints())));
    life_->setPlainText(QString(HUD_LIFE.arg(game->player()->life())));
    fps_->setPlainText(QString(HUD_FPS.arg(game->fps())));
    special_->setPlainText(QString(HUD_SPECIAL.arg(game->playerSpecials())));
    if(blinkspecial_)
    {
        if(blinkspecialtime_ > 0)
        {
            int s = blinkspecialtime_ / 1000;
            special_->setPlainText(QString("Cooldown %0").arg(s));
        }
        else
        {
            blinkspecial_ = false;
            special_->setDefaultTextColor(Qt::darkBlue);
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
        special_->setDefaultTextColor(Qt::red);
        blinkspecial_ = true;
        blinkspecialtime_ = currentcooldown;
    }
}
