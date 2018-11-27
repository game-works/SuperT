#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QObject>

static const int LEVEL_MANAGER_POINT_BASE = 40;
static const int LEVEL_MANAGER_SPECIAL_BASE = 100;
static const int LEVEL_MANAGER_LIFE_BASE = 50;


//!
//! \brief The LevelManager class - "manage" level changes and game overall difficulty associated with level
//! changes...
//!
class LevelManager final : public QObject
{
    Q_OBJECT
signals:
    void increaseLevel();
    void increaseLife();

public:
    LevelManager();
    ~LevelManager() = default;

    Q_DISABLE_COPY(LevelManager)

    //!
    //! \brief currentBackground - a background to be used on the current level
    //! \return
    //!
    QString currentBackground();

    //!
    //! \brief enemyLifeBase - the base life value for enemy on the current level
    //! \return
    //!
    int enemyLifeBase();

    //!
    //! \brief enemySpawnBase - the base time for enemy creating on the current level
    //! \return
    //!
    qreal enemySpawnBase();

    //!
    //! \brief currentLevel - return the number of the current level
    //! \return
    //!
    int currentLevel() const;

    //!
    //! \brief reset - reset level to the start (zero)
    //!
    void reset();

    void increasePlayerPoint();

    void consumePlayerSpecial();

    int playerPoints() const;

    int playerSpecials() const;

private:

    //!
    //! \brief level_ - the numerical identity of a level, 1, 2, 3...
    //!
    int level_;

    //!
    //! \brief baseLife_ - basic life points for entities
    //!
    int baseLife_;

    //!
    //! \brief baseSpawn_ - the basic timing for spawning entities
    //!
    int baseSpawn_;

    //!
    //! \brief playerPoints_ - current gameplay points
    //!
    int playerPoints_;

    //!
    //! \brief playerSpecials_ - player special power quantity
    //!
    int playerSpecials_;
};

#endif // LEVELMANAGER_H
