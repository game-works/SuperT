#include "game.h"

#include <QTime>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QPixmapCache>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QDebug>

#include "movecommand.h"
#include "shotcommand.h"
#include "bombcommand.h"
#include "specialcommand.h"

#include "hud.h"
#include "menu.h"
#include "spritesheet.h"

Game::Game(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView (scene, parent),
      time_(0),
      fps_counter_(0),
      player_(QSharedPointer<Player>(new Player(scene))),
      bushMs_(TIMER_STD_BUSH),
      rockMs_(TIMER_STD_ROCK),
      cloudMs_(TIMER_STD_CLOUD),
      aircraftMs_(TIMER_STD_AIR_ENEMY),
      vultureMs_(TIMER_STD_VULTURE),
      helicopterMs_(TIMER_STD_HELICOPTER),
      artilleryMs_(TIMER_STD_ARTILLERY),
      tankMs_(TIMER_STD_TANK),
      fps_(0),
      aircraft_(new EntityPool<Aircraft, 300>(scene)),
      bushes_(new EntityPool<Bush, 1500>(scene)),
      rocks_(new EntityPool<Rock, 2500>(scene)),
      clouds_(new EntityPool<Cloud, 300>(scene)),
      vultures_(new EntityPool<Vulture, 100>(scene)),
      helicopter_(new EntityPool<Helicopter, 100>(scene)),
      playerShots_(new EntityPool<PlayerShot, 3000>(scene)),
      playerBombs_(new EntityPool<PlayerBomb, 2000>(scene)),
      airExplosions_(new EntityPool<AirExplosion, 400>(scene)),
      groundExplosions_(new EntityPool<GroundExplosion, 400>(scene)),
      tanks_(new EntityPool<Tank, 150>(scene)),
      artillery_(new EntityPool<Artillery, 150>(scene)),
      enemyShots_(new EntityPool<EnemyShot, 5000>(scene)),
      artilleryShots_(new EntityPool<ArtilleryShot, 300>(scene)),
      hud_(QSharedPointer<Hud>(new Hud(scene))),
      menu_(QSharedPointer<Menu>(new Menu(scene))),
      special_(QSharedPointer<Special>(new Special(scene))),
      level_(QSharedPointer<LevelManager>(new LevelManager())),
      tankLife_(LIFE_TANK),
      vultureLife_(LIFE_VULTURE),
      helicopterLife_(LIFE_HELICOPTER),
      aircraftLife_(LIFE_AIR_ENEMY),
      artilleryLife_(LIFE_ARTILLERY),
      state_(GS_DEMO)
{
    setCacheMode(QGraphicsView::CacheNone);

    // connect the main loop event
    connect(&tick_, &QTimer::timeout, this, &Game::loop);
    // props
    connect(&bushTimer_, &QTimer::timeout, this, &Game::createBush);
    connect(&rockTimer_, &QTimer::timeout, this, &Game::createRock);
    connect(&cloudTimer_, &QTimer::timeout, this, &Game::createCloud);
    // entities
    connect(&aircraftTimer_, &QTimer::timeout, this, &Game::createAircraft);
    connect(&vultureTimer_, &QTimer::timeout, this, &Game::createVulture);
    connect(&helicopterTimer_, &QTimer::timeout, this, &Game::createHelicopter);
    connect(&artilleryTimer_, &QTimer::timeout, this, &Game::createArtillery);
    connect(&tankTimer_, &QTimer::timeout, this, &Game::createTank);
    //hud fps updates
    connect(&fpsTimer_, &QTimer::timeout, this, &Game::fpsUpdate);
    // level handling events
    connect(level_.data(), &LevelManager::increaseLevel, this, &Game::processLevel);
    connect(level_.data(), &LevelManager::increaseLife, this, &Game::processLife);

    connect(menu_.data(), &Menu::start, this, &Game::play);
    connect(menu_.data(), &Menu::showSignal, this, &Game::init);

    explosion_ = QSharedPointer<SpriteSheet>(new SpriteSheet(130, 125, ":/exp/air/images/supert_exp.png", 37, 0, 0, -40));
    explosion_->setParentItem(player_.data()); // bind explosion effect with player
    explosion_->setVisible(false);
    connect(explosion_.data(), &SpriteSheet::animationEnd, this, &Game::removeExplosion);

    //start game initial values and the main loop
    inputhandler_.bind(Qt::Key_Up, QSharedPointer<Command>(new MoveCommand(DIR_UP)));
    inputhandler_.bind(Qt::Key_Down, QSharedPointer<Command>(new MoveCommand(DIR_DOWN)));
    inputhandler_.bind(Qt::Key_Right, QSharedPointer<Command>(new MoveCommand(DIR_RIGHT)));
    inputhandler_.bind(Qt::Key_Left, QSharedPointer<Command>(new MoveCommand(DIR_LEFT)));
    inputhandler_.bind(Qt::Key_Space, QSharedPointer<Command>(new ShotCommand()));
    inputhandler_.bind(Qt::Key_Control, QSharedPointer<Command>(new BombCommand()));
    inputhandler_.bind(Qt::Key_Alt, QSharedPointer<Command>(new SpecialCommand()));

    background1_ = QPixmap(":/scenario/images/background_1.png");
    background2_ = QPixmap(":/scenario/images/background_2.png");
    background3_ = QPixmap(":/scenario/images/background_3.png");
    background4_ = QPixmap(":/scenario/images/background_4.png");
    background5_ = QPixmap(":/scenario/images/background_5.png");
    background6_ = QPixmap(":/scenario/images/background_6.png");
    background7_ = QPixmap(":/scenario/images/background_7.png");

    currentBackground_ = background1_;

    hud_->init();
    menu_->init();
}

Game::~Game()
{    
    for(auto e : entities_)
        e.clear();
    entities_.clear();

    delete aircraft_;
    delete bushes_;
    delete rocks_;
    delete clouds_;
    delete vultures_;
    delete helicopter_;
    delete playerShots_;
    delete playerBombs_;
    delete airExplosions_;
    delete groundExplosions_;
    delete tanks_;
    delete artillery_;
    delete enemyShots_;
    delete artilleryShots_;

    player_.clear();
    explosion_.clear();
    special_.clear();
    hud_.clear();
    menu_.clear();
    level_.clear();
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(state_ == GS_PLAY)
        keys_.insert(Qt::Key(event->key()));

}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    if(state_ == GS_PLAY)
        keys_.remove(Qt::Key(event->key()));
}

void Game::demo()
{
    if(state_ == GS_DEMO)
    {
        QPointF v;
        // simple random movement
        qreal div = QRandomGenerator::global()->bounded(50, 100);
        qreal x = QRandomGenerator::global()->bounded(-10, 11);
        qreal y = QRandomGenerator::global()->bounded(-10, 11);
        v.setX(x/div);
        v.setY(y/div);
        player_->setVelocity(v);

        keys_.clear();
        keys_.insert(Qt::Key_Space);
        auto r = static_cast<int>(x);
        if(r % 10 == 0)
            keys_.insert(Qt::Key_Control);
    }
}

void Game::processLevel()
{
    qreal basetime = level_->enemySpawnBase();
    tankMs_ = static_cast<int>(TIMER_STD_TANK - basetime);
    tankTimer_.start(tankMs_);
    vultureMs_ = static_cast<int>(TIMER_STD_VULTURE - basetime);
    vultureTimer_.start(vultureMs_);
    helicopterMs_ = static_cast<int>(TIMER_STD_HELICOPTER - basetime);
    helicopterTimer_.start(helicopterMs_);
    aircraftMs_ = static_cast<int>(TIMER_STD_AIR_ENEMY - basetime);
    aircraftTimer_.start(aircraftMs_);
    artilleryMs_ = static_cast<int>(TIMER_STD_ARTILLERY - basetime);
    artilleryTimer_.start(artilleryMs_);

    int baselife = level_->enemyLifeBase();
    tankLife_ = baselife + LIFE_TANK;
    vultureLife_ = baselife + LIFE_VULTURE;
    helicopterLife_ = baselife + LIFE_HELICOPTER;
    aircraftLife_ = baselife + LIFE_AIR_ENEMY;
    artilleryLife_ = baselife + LIFE_ARTILLERY;

    // selects the next background based on level id
    if(state_ == GS_DEMO)
    {
        currentBackground_ = background1_;
    }
    else
    {
        switch(level_->currentBackground())
        {
            case 1:
                currentBackground_ = background1_;
            break;
            case 2:
                currentBackground_ = background2_;
            break;
            case 3:
                currentBackground_ = background3_;
            break;
            case 4:
                currentBackground_ = background4_;
            break;
            case 5:
                currentBackground_ = background5_;
            break;
            case 6:
                currentBackground_ = background6_;
            break;
            case 7:
                currentBackground_ = background7_;
            break;
            default:
                currentBackground_ = background1_;
            break;
        }
    }
}

void Game::processLife()
{
    int i = player_->life();
    player_->setLife(++i);
    // TODO maybe introduce a temporary invencibility for fun
}

void Game::removeExplosion()
{
    explosion_->setVisible(false);
}

void Game::fpsUpdate()
{
    fps_ = fps_counter_;
    fps_counter_ = 0;
}

void Game::init()
{
    tick_.stop();

    level_->reset();

    resetEntities();
    keys_.clear();

    time_ = 0;
    fps_counter_ = 0;

    //re-create a new player
    player_->init(PLAYER_START_POS, PLAYER_STD_VELOCITY);

    hud_->show(false);

    state_ = GS_DEMO;

    // start event timers
    tick_.start(MS_TICK);
    bushTimer_.start(bushMs_);
    rockTimer_.start(rockMs_);
    cloudTimer_.start(cloudMs_);
    fpsTimer_.start(1000);

    processLevel();

    aircraftTimer_.start(aircraftMs_);
    vultureTimer_.start(vultureMs_);
    helicopterTimer_.start(helicopterMs_);
    artilleryTimer_.start(artilleryMs_);
    tankTimer_.start(tankMs_);

    clock_.start();
}

void Game::resetEntities()
{
    for(const auto &e : entities_)
    {
        e->reset();
    }
    entities_.clear();
}

void Game::play()
{
    tick_.stop();

    keys_.clear();

    resetEntities();

    hud_->show(true);

    player_->init(PLAYER_START_POS, PLAYER_STD_VELOCITY);

    state_ = GS_PLAY;

    tick_.start();
}

QSharedPointer<Bush> Game::createBush()
{
    return createEntity(bushes_);
}

QSharedPointer<Rock> Game::createRock()
{
    return createEntity(rocks_);
}

QSharedPointer<Cloud> Game::createCloud()
{
    return createEntity(clouds_);
}

QSharedPointer<Aircraft> Game::createAircraft()
{
    return createEntity(aircraft_, aircraftLife_, QPointF(), AIR_STD_VELOCITY);
}

QSharedPointer<Vulture> Game::createVulture()
{
    return createEntity(vultures_, vultureLife_);
}

QSharedPointer<Helicopter> Game::createHelicopter()
{
    return createEntity(helicopter_, helicopterLife_);
}

QSharedPointer<PlayerShot> Game::createPlayerShoot(QPointF pos, QPointF vel, int life)
{
    return createEntity(playerShots_, life, pos, vel);
}

QSharedPointer<Explosion> Game::createAirExplosion(QPointF pos, QPointF vel)
{
    return createEntity(airExplosions_, LIFE_PROP, pos, vel);
}

QSharedPointer<Explosion> Game::createGroundExplosion(QPointF pos, QPointF vel)
{
    return createEntity(groundExplosions_, LIFE_PROP, pos, vel);
}

QSharedPointer<Tank> Game::createTank()
{
    return createEntity(tanks_, tankLife_);
}

QSharedPointer<Artillery> Game::createArtillery()
{
    return createEntity(artillery_, artilleryLife_);
}

QSharedPointer<PlayerBomb> Game::createPlayerBomb(QPointF pos, QPointF vel, int life)
{
    return createEntity(playerBombs_, life, pos, vel);
}

QSharedPointer<EnemyShot> Game::createEnemyShot(QPointF pos, QPointF vel, qreal angle)
{
    return createEntity(enemyShots_, LIFE_PROP, pos, vel, angle);
}

QSharedPointer<ArtilleryShot> Game::createArtilleryShot(QPointF pos, QPointF vel, qreal angle)
{
    return createEntity(artilleryShots_, LIFE_PROP, pos, vel, angle);
}

QSharedPointer<Special> Game::createSpecial()
{
    if(!special_.isNull())
    {
        entities_.insert(special_);
        special_->init();
    }
    return special_;
}

int Game::playerSpecials() const
{
    return level_->playerSpecials();
}

int Game::playerPoints() const
{
    return level_->playerPoints();
}

void Game::specialCoolDownWarning(int currentcooldown)
{
    hud_->displayCoolDownWarning(currentcooldown);
    level_->consumePlayerSpecial();
}

int Game::fps() const
{
    return fps_;
}

int Game::gameLevel() const
{
    return level_->currentLevel();
}

QSharedPointer<Player> Game::player() const
{
    return player_;
}

void Game::loop()
{
    int elapsed = clock_.restart();
    time_ += elapsed;

    if(state_ != GS_OVER)
    {
        demo();

        // process key input from the player and execute the corresponding commands
        QSet<Qt::Key>::Iterator it;
        for(it = keys_.begin() ; it != keys_.end() ; ++it)
        {
            QSharedPointer<Command> cmd = inputhandler_.process(*it);
            if(!cmd.isNull())
            {
                cmd->execute(this, player_, elapsed);
            }
        }

        // update player state
        player_->update(this, elapsed);

        // update all entities states
        foreach(QSharedPointer<Entity> e, entities_)
        {
            // check if the entity is visible on the scene
            if(e->dead())
            {
                if(e->destructible())
                {
                    if(e->air())
                        createAirExplosion(e->position(), e->velocity());
                    else
                        createGroundExplosion(e->position(), e->velocity());
                }
                e->reset();
                entities_.remove(e);
            }
            else if(e->position().x() < (GAME_WIDTH-SCENE_WIDTH) || // adds margin area
                    e->position().x() > SCENE_WIDTH ||
                    e->position().y() < (GAME_HEIGHT-SCENE_HEIGHT) || // adds margin area
                    e->position().y() > SCENE_HEIGHT) // simple and fast to check if the entity is out of the scene
            {
                // resets internal entity value, also "return" an entity to the its pool
                e->reset();
                entities_.remove(e);
            }
            else
            {
                e->update(this, elapsed);

                // check enemies hit by friends only
                if(e->enemy() && e->collidable() && e->destructible())
                {
                    QList<QGraphicsItem*> entityList = e->collidingItems();
                    QListIterator<QGraphicsItem*> eIt(entityList);
                    while(eIt.hasNext())
                    {
                        QGraphicsItem* graph = eIt.next();
                        auto bullet = dynamic_cast<Entity*>(graph); //TODO enhance this solution to avoid the dyn cast perf. cost
                        if(bullet != nullptr &&
                                bullet->collidable() &&
                                !bullet->destructible() &&
                                !bullet->enemy()) //enemy hit by a shot
                        {
                            e->hit();
                            bullet->hit(); //remove the used bullet from the game
                            if(state_ == GS_PLAY && e->dead())
                            {
                                level_->increasePlayerPoint();
                            }
                        }
                    }
                }
            }
        }

        //player collision detection
        QList<QGraphicsItem*> entityList = player_->collidingItems();
        QListIterator<QGraphicsItem*> eIt(entityList);
        while(eIt.hasNext())
        {
            QGraphicsItem* graph = eIt.next();
            auto enemy = dynamic_cast<Entity*>(graph); //TODO enhance this solution to avoid the dyn cast perf. cost
            if(enemy != nullptr && enemy->enemy()) // friend hit by any kind of enemies, including enemies shots
            {
                player_->hit();
                enemy->hit();
                explosion_->setVisible(true);
                explosion_->animate(35);
                if(state_ == GS_PLAY && player_->dead())
                {
                    state_ = GS_OVER;
                    menu_->showGameOver();
                    hud_->show(false);
                }
            }
        }

        fps_counter_++;
        hud_->update(this, elapsed);
        menu_->update(this, elapsed);
    }
}

template<class T, int N>
QSharedPointer<T> Game::createEntity(EntityPool<T, N> *pool, int life, QPointF pos, QPointF vel, qreal angle)
{
    QSharedPointer<T> e = pool->useEntity();
    if(!e.isNull())
    {
        entities_.insert(e);
        e->init(pos, vel, angle, life);
    }
    return e;
}

void Game::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(rect, currentBackground_, rect);
}

