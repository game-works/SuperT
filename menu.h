#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QSet>
#include <QGraphicsRectItem>

#include "customtextitem.h"

class QGraphicsScene;
class Game;

static const QString MENU_TITLE = "Super-T";
static const QString MENU_START = "START";
static const QString MENU_SCORE = "SCORES";
static const QString MENU_HELP= "HELP";
static const QString MENU_ABOUT = "ABOUT";
static const QString MENU_BACK = "BACK";
static const QString MENU_GAMEOVER = "GAME OVER";

static const QString MENU_HELP_TEXT = "- Use keyboard <<Arrows>> to move.\n"
                                      "- <<Space>> shots main cannon.\n"
                                      "- <<Ctrl>> drop bombs.\n"
                                      "- <<Alt>> call for support.";

static const QString MENU_ABOUT_TEXT = "Super-T\n"
                                       "MIT license, 2018\n"
                                       "www.github.com/sfadiga\n"
                                       "Sandro Fadiga\n";

static const QString MENU_SCORE_TEXT = "  -- SCORES --\n"
                                       "1. cpu...... 1000\n"
                                       "2. me....... 300\n"
                                       "3. loser.... 200\n";

//!
//! \brief The Menu class - game menu
//!
class Menu : public QObject
{
    Q_OBJECT

signals:
    void start();
    void showSignal();

public:
    Menu(QGraphicsScene *scene);
    ~Menu();

    Q_DISABLE_COPY(Menu)

    void init();
    void update(Game* game, int dt);

    //!
    //! \brief show - show or hide the hud
    //! \param show - true display hud, false otherwise
    //!
    void show(bool show);

   // void createScoreTable();

public slots:
    void showGameOver();

private slots:
    void startSlot();
    void showAbout();
    void showScore();
    void showHelp();
    void showMenu();
    void startEvent();

private:
    QGraphicsScene *scene_;
    //screen texts
    CustomTextItem* title_;
    CustomTextItem* start_;
    CustomTextItem* score_;
    CustomTextItem* help_;
    CustomTextItem* about_;
    CustomTextItem* back_;
    CustomTextItem* gameOver_;

    QGraphicsTextItem* scoretext_;
    QGraphicsTextItem* helptext_;
    QGraphicsTextItem* abouttext_;

    int time_;

};

#endif // MENU_H
