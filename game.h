#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMutex>
#include <QSet>
#include <QTime>
#include <QTimer>

#include "entitypool.h"
#include "inputhandler.h"

#include "player.h"
#include "playershot.h"
#include "bush.h"
#include "rock.h"
#include "cloud.h"
#include "aircraft.h"
#include "vulture.h"
#include "helicopter.h"
#include "explosion.h"
#include "tank.h"
#include "artillery.h"
#include "playerbomb.h"
#include "enemyshot.h"
#include "artilleryshot.h"
#include "special.h"
#include "levelmanager.h"

//! GAME main loop refresh rate
static const int MS_TICK = 16;

//! standard gravity used across the game
static const qreal GRAVITY = 9.81;

//! game window size
static const qreal GAME_WIDTH = 650;
static const qreal GAME_HEIGHT = 450;
static const qreal SCENE_WIDTH = 750.0;
static const qreal SCENE_HEIGHT = 550.0;

//! timers start values in milliseconds
static const int TIMER_STD_CLOUD = 2600;
static const int TIMER_STD_BUSH = 500;
static const int TIMER_STD_ROCK = 250;
static const int TIMER_STD_AIR_ENEMY = 3500;
static const int TIMER_STD_VULTURE = 9000;
static const int TIMER_STD_HELICOPTER = 8000;
static const int TIMER_STD_ARTILLERY = 7000;
static const int TIMER_STD_TANK = 11000;

//! default life for enemies
static const int LIFE_AIR_ENEMY = 1;
static const int LIFE_VULTURE = 8;
static const int LIFE_HELICOPTER = 3;
static const int LIFE_ARTILLERY = 4;
static const int LIFE_TANK = 3;
static const int LIFE_PROP = 1;

//!
//! \brief Z_PLANE_ - the z coordinate of the graphics
//!
static const int Z_PLANE_PROP = 0;
static const int Z_PLANE_ENTITIES = 2;
static const int Z_PLANE_PLAYER = 3;
static const int Z_PLANE_SHOTS = 4;
static const int Z_PLANE_PROP_TOP = 5;
static const int Z_PLANE_HUD = 10;

class Hud;
class Menu;
class SpriteSheet;

enum GAME_STATES {
    GS_DEMO, GS_PLAY, GS_OVER
};

//!
//! \brief The Game class
//!
class Game : public QGraphicsView
{
    Q_OBJECT
signals:
    void pointIncrease(int);
    //void startPlay();

public:
    Game(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~Game();

    QSharedPointer<Player> player() const;

    int gameLevel() const;

    int fps() const;

    int playerPoints() const;

    int playerSpecials() const;

    void specialCoolDownWarning(int currentcooldown);

protected:
    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

    //!
    //!
    //!
    template<class T, int N>
    QSharedPointer<T> createEntity(EntityPool<T, N> *pool,
                                   int life = 1,
                                   QPointF pos = QPointF(0, 0),
                                   QPointF vel = QPointF(0, 0),
                                   qreal angle = 0.0);

    void init();

    void demo();

    void over();

    void play();


protected slots:

    //!
    //! \brief loop - game main event loop
    //!
    void loop();

    void startDemo();

    //!
    //! \brief processLevel - process a game level increase
    //!
    void processLevel();

public slots:

    //!
    //! \brief removeExplosion
    //!
    void removeExplosion();

    //!
    //! \brief fpsUpdate
    //!
    void fpsUpdate();

    //!
    //! \brief createBush
    //!
    QSharedPointer<Bush> createBush();

    //!
    //! \brief createRock
    //! \return
    //!
    QSharedPointer<Rock> createRock();

    //!
    //! \brief createCloud
    //!
    QSharedPointer<Cloud> createCloud();

    //!
    //! \brief createAircraft
    //!
    QSharedPointer<Aircraft> createAircraft();

    //!
    //! \brief createVulture
    //!
    QSharedPointer<Vulture> createVulture();

    //!
    //! \brief createHelicopter
    //!
    QSharedPointer<Helicopter> createHelicopter();

    //!
    //! \brief createPlayerShoot
    //! \return
    //!
    QSharedPointer<PlayerShot> createPlayerShoot(QPointF pos = QPointF(0, 0),
                                                 QPointF vel = QPointF(0, 0));
    //!
    //! \brief createAirExplosion
    //!
    QSharedPointer<Explosion> createAirExplosion(QPointF pos = QPointF(0, 0),
                                                 QPointF vel = QPointF(0, 0));

    //!
    //! \brief createGroundExplosion
    //!
    QSharedPointer<Explosion> createGroundExplosion(QPointF pos = QPointF(0, 0),
                                                    QPointF vel = QPointF(0, 0));

    //!
    //! \brief createTank
    //! \return
    //!
    QSharedPointer<Tank> createTank();

    //!
    //! \brief createArtillery
    //! \return
    //!
    QSharedPointer<Artillery> createArtillery();

    //!
    //! \brief createPlayerBomb
    //! \param pos
    //! \param vel
    //! \return
    //!
    QSharedPointer<PlayerBomb> createPlayerBomb(QPointF pos = QPointF(0, 0),
                                                QPointF vel = QPointF(0, 0));
    //!
    //! \brief createEnemyShot
    //! \param pos
    //! \param vel
    //! \param angle
    //! \return
    //!
    QSharedPointer<EnemyShot> createEnemyShot(QPointF pos = QPointF(0, 0),
                                               QPointF vel = QPointF(0, 0),
                                               qreal angle = 0.0);

    //!
    //! \brief createArtilleryShot
    //! \param pos
    //! \param vel
    //! \param angle
    //! \return
    //!
    QSharedPointer<ArtilleryShot> createArtilleryShot(QPointF pos = QPointF(0, 0),
                                                      QPointF vel = QPointF(0, 0),
                                                      qreal angle = 0.0);

    //!
    //! \brief createSpecial
    //! \return
    //!
    QSharedPointer<Special> createSpecial();

private:
    //! reset all entities and clear the set
    void resetEntities();

private:

    //!
    //! \brief entities_ - the entities added to the game scene
    //!
    QSet<QSharedPointer<Entity>> entities_;

    //!
    //! \brief inputhandler_ - player control handler
    //!
    InputHandler inputhandler_;

    //!
    //! \brief keys_ - stores keystrokes performed by the player,
    //!  used by input handler to process commands
    //!
    QSet<Qt::Key> keys_;

    //!
    //! \brief _clock - keeps track of the time between loop calls
    //!
    QTime clock_;

    //!
    //! \brief _tick - game main timer, controls the game loop call
    //!
    QTimer tick_;

    //!
    //! \brief fpsTimer_ - calls a fpsUpdate at each second
    //!
    QTimer fpsTimer_;

    //! game events timers
    QTimer bushTimer_;
    QTimer rockTimer_;
    QTimer cloudTimer_;
    QTimer aircraftTimer_;
    QTimer vultureTimer_;
    QTimer helicopterTimer_;
    QTimer artilleryTimer_;
    QTimer tankTimer_;

//  THE FOLLOWING ATTRIBUTES NEED TO BE INITIALIZED IN CONSTRUCTOR

    // total ammount of time since start of the game loop
    int time_;

    int fps_counter_;

    //!
    //! \brief _player - the player entity, it is handled separate from other entities - see@ entities_
    //!
    QSharedPointer<Player> player_;

    //! timer values attributes, used to change timing during gameplay
    int bushMs_;
    int rockMs_;
    int cloudMs_;
    int aircraftMs_;
    int vultureMs_;
    int helicopterMs_;
    int artilleryMs_;
    int tankMs_;

    int fps_; // frames per seconds calculated

    int playerPoints_; // current gameplay points

    int playerSpecials_; // player special power quantity

    //! cache of pre-loaded re-usable entities
    EntityPool<Aircraft, 300> *aircraft_;
    EntityPool<Bush, 800> *bushes_;
    EntityPool<Rock, 2000> *rocks_;
    EntityPool<Cloud, 300> *clouds_;
    EntityPool<Vulture, 100> *vultures_;
    EntityPool<Helicopter, 100> *helicopter_;
    EntityPool<PlayerShot, 1000> *playerShots_;
    EntityPool<PlayerBomb, 1000> *playerBombs_;
    EntityPool<AirExplosion, 400> *airExplosions_;
    EntityPool<GroundExplosion, 400> *groundExplosions_;
    EntityPool<Tank, 150> *tanks_;
    EntityPool<Artillery, 150> *artillery_;
    EntityPool<EnemyShot, 5000> *enemyShots_;
    EntityPool<ArtilleryShot, 300> *artilleryShots_;

    QSharedPointer<Hud> hud_;
    QSharedPointer<Menu> menu_;
    QSharedPointer<SpriteSheet> explosion_;
    QSharedPointer<Special> special_;
    QSharedPointer<LevelManager> level_; // current gameplay level

    int tankLife_;
    int vultureLife_;
    int helicopterLife_;
    int aircraftLife_;
    int artilleryLife_;

    GAME_STATES state_;

};

#endif // GAME_H
