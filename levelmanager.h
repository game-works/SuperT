#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <QPixmap>

//!
//! \brief The LevelManager class - "manage" level changes and game overall difficulty associated with level
//! changes...
//!
class LevelManager final : public QObject
{
    Q_OBJECT
signals:
    void increaseLevel();

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

    int currentLevel() const;

public slots:

    //!
    //! \brief processPlayerPoints -
    //! \param points
    //!
    void processPlayerPoints(int points);

private:

    //!
    //! \brief level_ - the numerical identity of a level, 1, 2, 3...
    //!
    int level_;

    int baseLife_;

    int baseSpawn_;

};

#endif // LEVELMANAGER_H
