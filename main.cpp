#include "game.h"
#include "spritepackcache.h"

#include <QApplication>
#include <QPixmapCache>
#include <QOpenGLWidget>
#include "spritepackcache.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //load all sprites from sprite pack
    SpritePackCache::setCacheLimit(50240);
    SpritePackCache::loadFromSpritePack(":/sprite/images/sprite_pack.png", ":/sprite/images/sprite_pack.txt");
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

    //QOpenGLWidget *glWidget = new QOpenGLWidget();
    //view->setViewport(glWidget); //to switch to openGl.

    // performance tuning
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);  // FullViewportUpdate  (QGraphicsView::SmartViewportUpdate);
    view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    view->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    // quality settings
    view->setRenderHint(QPainter::Antialiasing, true);
    view->setRenderHint(QPainter::SmoothPixmapTransform, true);

    // display the graphics area and main window
    view->show();
    // qt application loop / event
    return QApplication::exec();
}

