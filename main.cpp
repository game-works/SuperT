#include "game.h"
#include <QApplication>
#include <QPixmapCache>
#include <QOpenGLWidget>

void loadPixmapCache()
{
    QPixmapCache::setCacheLimit(40240);
    QPixmapCache::insert("supert", QPixmap(":/entity/air/images/supert.png"));
    //QPixmapCache::insert("background", QPixmap(":/scenario/images/background.png"));
    QPixmapCache::insert("background_5", QPixmap(":/scenario/images/background_1.png"));
    QPixmapCache::insert("background_2", QPixmap(":/scenario/images/background_2.png"));
    QPixmapCache::insert("background_3", QPixmap(":/scenario/images/background_3.png"));
    QPixmapCache::insert("background_4", QPixmap(":/scenario/images/background_4.png"));
    QPixmapCache::insert("background_1", QPixmap(":/scenario/images/background_5.png"));
    QPixmapCache::insert("background_6", QPixmap(":/scenario/images/background_6.png"));
    QPixmapCache::insert("background_7", QPixmap(":/scenario/images/background_7.png"));
    QPixmapCache::insert("bush_1", QPixmap(":/scenario/images/bush_1.png"));
    QPixmapCache::insert("bush_2", QPixmap(":/scenario/images/bush_2.png"));
    QPixmapCache::insert("bush_3", QPixmap(":/scenario/images/bush_3.png"));
    QPixmapCache::insert("cloud_1", QPixmap(":/scenario/images/cloud_01.png"));
    QPixmapCache::insert("cloud_2", QPixmap(":/scenario/images/cloud_02.png"));
    QPixmapCache::insert("cloud_3", QPixmap(":/scenario/images/cloud_03.png"));
    QPixmapCache::insert("bomb", QPixmap(":/shoot/images/bomb.png"));
    QPixmapCache::insert("bullet", QPixmap(":/shoot/images/air_friend_bullet_1.png"));
    QPixmapCache::insert("friend", QPixmap(":/entity/air/images/air_friend_1.png"));
    QPixmapCache::insert("enemy_bullet", QPixmap(":/shoot/images/air_enemy_bullet_1.png"));
    QPixmapCache::insert("artilleryshot", QPixmap(":/shoot/images/gnd_enemy_bullet_1.png"));
    QPixmapCache::insert("air_enemy_1", QPixmap(":/entity/air/images/air_enemy_1.png"));
    QPixmapCache::insert("air_enemy_2", QPixmap(":/entity/air/images/air_enemy_2.png"));
    QPixmapCache::insert("air_enemy_3", QPixmap(":/entity/air/images/air_enemy_3.png"));
    QPixmapCache::insert("air_enemy_4", QPixmap(":/entity/air/images/air_enemy_4.png"));
    QPixmapCache::insert("air_enemy_5", QPixmap(":/entity/air/images/air_enemy_5.png"));
    QPixmapCache::insert("air_enemy_6", QPixmap(":/entity/air/images/air_enemy_6.png"));
    QPixmapCache::insert("vulture", QPixmap(":/entity/air/images/vulture.png"));
    QPixmapCache::insert("tank", QPixmap(":/entity/ground/images/gnd_enemy_1.png"));
    QPixmapCache::insert("artillery", QPixmap(":/entity/ground/images/gnd_enemy_2.png"));
    QPixmapCache::insert("air_exp_1", QPixmap(":/exp/air/images/air_exp_1.png"));
    QPixmapCache::insert("air_exp_2", QPixmap(":/exp/air/images/air_exp_2.png"));
    QPixmapCache::insert("air_exp_3", QPixmap(":/exp/air/images/air_exp_3.png"));
    QPixmapCache::insert("air_exp_4", QPixmap(":/exp/air/images/air_exp_4.png"));
    QPixmapCache::insert("air_exp_5", QPixmap(":/exp/air/images/air_exp_5.png"));
    QPixmapCache::insert("air_exp_6", QPixmap(":/exp/air/images/air_exp_6.png"));
    QPixmapCache::insert("air_exp_7", QPixmap(":/exp/air/images/air_exp_7.png"));
    QPixmapCache::insert("air_exp_8", QPixmap(":/exp/air/images/air_exp_8.png"));
    QPixmapCache::insert("air_exp_9", QPixmap(":/exp/air/images/air_exp_9.png"));
    QPixmapCache::insert("air_exp_10", QPixmap(":/exp/air/images/air_exp_10.png"));
    QPixmapCache::insert("air_exp_11", QPixmap(":/exp/air/images/air_exp_11.png"));
    QPixmapCache::insert("air_exp_12", QPixmap(":/exp/air/images/air_exp_12.png"));
    QPixmapCache::insert("air_exp_13", QPixmap(":/exp/air/images/air_exp_13.png"));
    QPixmapCache::insert("air_exp_14", QPixmap(":/exp/air/images/air_exp_14.png"));
    QPixmapCache::insert("air_exp_15", QPixmap(":/exp/air/images/air_exp_15.png"));
    QPixmapCache::insert("air_exp_16", QPixmap(":/exp/air/images/air_exp_16.png"));
    QPixmapCache::insert("gnd_exp_1", QPixmap(":/exp/ground/images/gnd_exp_1.png"));
    QPixmapCache::insert("gnd_exp_2", QPixmap(":/exp/ground/images/gnd_exp_2.png"));
    QPixmapCache::insert("gnd_exp_3", QPixmap(":/exp/ground/images/gnd_exp_3.png"));
    QPixmapCache::insert("gnd_exp_4", QPixmap(":/exp/ground/images/gnd_exp_4.png"));
    QPixmapCache::insert("gnd_exp_5", QPixmap(":/exp/ground/images/gnd_exp_5.png"));
    QPixmapCache::insert("gnd_exp_6", QPixmap(":/exp/ground/images/gnd_exp_6.png"));
    QPixmapCache::insert("gnd_exp_7", QPixmap(":/exp/ground/images/gnd_exp_7.png"));
    QPixmapCache::insert("gnd_exp_8", QPixmap(":/exp/ground/images/gnd_exp_8.png"));
    QPixmapCache::insert("gnd_exp_9", QPixmap(":/exp/ground/images/gnd_exp_9.png"));
    QPixmapCache::insert("gnd_exp_10", QPixmap(":/exp/ground/images/gnd_exp_10.png"));
    QPixmapCache::insert("gnd_exp_11", QPixmap(":/exp/ground/images/gnd_exp_11.png"));
    QPixmapCache::insert("gnd_exp_12", QPixmap(":/exp/ground/images/gnd_exp_12.png"));
    QPixmapCache::insert("gnd_exp_13", QPixmap(":/exp/ground/images/gnd_exp_13.png"));
    QPixmapCache::insert("gnd_exp_14", QPixmap(":/exp/ground/images/gnd_exp_14.png"));
    QPixmapCache::insert("gnd_exp_15", QPixmap(":/exp/ground/images/gnd_exp_15.png"));
    QPixmapCache::insert("rock_01", QPixmap(":/scenario/images/rock_01.png"));
    QPixmapCache::insert("rock_02", QPixmap(":/scenario/images/rock_02.png"));

    //QPixmapCache::insert("blood_exp", QPixmap(":/exp/air/images/blood_exp.png"));
    //QPixmapCache::insert("supert_exp", QPixmap(":/exp/air/images/supert_exp.png"));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // pre load the images to a memory cache
    loadPixmapCache();
    // ---- SET GAME SCENE
    QGraphicsScene* scene = new QGraphicsScene(QRectF(0, 0, SCENE_WIDTH, SCENE_HEIGHT));
    // performance setting
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    // ---- CREATE GAME VIEW (QGraphicsView) and configure screen size and position
    auto view = new Game(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    view->setSceneRect(QRectF(0,0, GAME_WIDTH, GAME_HEIGHT));
    view->setFixedWidth(static_cast<int>(GAME_WIDTH));
    view->setFixedHeight(static_cast<int>(GAME_HEIGHT));
    view->setMinimumHeight(static_cast<int>(GAME_HEIGHT));
    view->setMaximumHeight(static_cast<int>(GAME_HEIGHT));
    view->setMinimumWidth(static_cast<int>(GAME_WIDTH));
    view->setMaximumWidth(static_cast<int>(GAME_WIDTH));
    view->setDragMode(QGraphicsView::NoDrag);

    //view->setViewport(new QOpenGLWidget());

    // performance tuning
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//SmartViewportUpdate(QGraphicsView::BoundingRectViewportUpdate);
    view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    view->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    // quality settings
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setRenderHint(QPainter::SmoothPixmapTransform, true);

    // display the graphics area and main window
    view->show();
    // qt application loop / event
    return QApplication::exec();
}

