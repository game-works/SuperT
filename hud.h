#ifndef HUD_H
#define HUD_H

#include <QString>

class QGraphicsScene;
class QGraphicsTextItem;
class Game;


static const QString HUD_POINTS = "Points: %0";
static const QString HUD_LEVEL = "Level: %0";
static const QString HUD_FPS = "%0 FPS";
static const QString HUD_LIFE = "Lifes: %0";
static const QString HUD_SPECIAL = "Specials: %0";


//!
//! \brief The Hud class - draws the information of gameplay to the player
//!
class Hud final
{
public:
    Hud(QGraphicsScene *scene);
    ~Hud();
    void update(Game* game, int dt);

    //!
    //! \brief show - show or hide the hud
    //! \param show - true display hud, false otherwise
    //!
    void show(bool show);

    Q_DISABLE_COPY(Hud)

    void displayCoolDownWarning(int);

    void init();
private:
    QGraphicsScene *scene_;
    //screen texts
    QGraphicsTextItem* points_;
    QGraphicsTextItem* level_;
    QGraphicsTextItem* fps_;
    QGraphicsTextItem* life_;
    QGraphicsTextItem* special_;

    int time_;
    bool blinkspecial_;
    int blinkspecialtime_;
};

#endif // HUD_H
