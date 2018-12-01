#include "menu.h"

#include <QFont>
#include <QList>

#include "game.h"

static const qreal MENU_X = GAME_WIDTH / 2.9; //looks much better than 3.0 :P

static const qreal MENU_TITLE_Y = 0;
static const qreal MENU_START_Y = 100;
static const qreal MENU_SCORE_Y = 150;
static const qreal MENU_HELP_Y = 200;
static const qreal MENU_ABOUT_Y = 250;
static const qreal MENU_BACK_Y = 300;

Menu::Menu(QGraphicsScene *scene)
    : scene_(scene),
      title_(new CustomTextItem(Qt::darkYellow, false, false)),
      start_(new CustomTextItem(Qt::darkGray)),
      score_(new CustomTextItem(Qt::darkCyan)),
      help_(new CustomTextItem(Qt::darkMagenta)),
      about_(new CustomTextItem(Qt::darkBlue)),
      back_(new CustomTextItem(Qt::darkGreen)),
      gameOver_(new CustomTextItem(Qt::yellow, false, false)),
      scoretext_(new QGraphicsTextItem),
      helptext_(new QGraphicsTextItem),
      abouttext_(new QGraphicsTextItem),
      time_(0)
{
    connect(start_, &CustomTextItem::clickEvent, this, &Menu::startEvent);
    connect(score_, &CustomTextItem::clickEvent, this, &Menu::showScore);
    connect(help_, &CustomTextItem::clickEvent, this, &Menu::showHelp);
    connect(about_, &CustomTextItem::clickEvent, this, &Menu::showAbout);
    connect(back_, &CustomTextItem::clickEvent, this, &Menu::showMenu);
}

Menu::~Menu()
{
    delete start_;
    delete score_;
    delete help_;
    delete about_;
    delete scoretext_;
    delete helptext_;
    delete abouttext_;
    delete back_;
    delete title_;
}

void Menu::init()
{
    QFont t;
    t.setFamily("Arial");
    t.setBold(true);
    t.setItalic(true);
    t.setPixelSize(56);
    title_->setFont(t);
    gameOver_->setFont(t);

    QFont f;
    f.setFamily("Arial");
    f.setBold(true);
    f.setPixelSize(48);

    start_->setFont(f);
    score_->setFont(f);
    help_->setFont(f);
    about_->setFont(f);

    QFont b;
    b.setFamily("Arial");
    b.setBold(true);
    b.setItalic(true);
    b.setPixelSize(28);

    back_->setFont(b);

    QFont f2;
    f2.setFamily("Arial");
    f2.setPixelSize(22);

    scoretext_->setFont(f2);
    helptext_->setFont(f2);
    abouttext_->setFont(f2);

    scene_->addItem(title_);
    scene_->addItem(start_);
    scene_->addItem(score_);
    scene_->addItem(help_);
    scene_->addItem(about_);
    scene_->addItem(back_);
    scene_->addItem(gameOver_);
    scene_->addItem(scoretext_);
    scene_->addItem(helptext_);
    scene_->addItem(abouttext_);

    title_->setZValue(Z_PLANE_HUD);
    start_->setZValue(Z_PLANE_HUD);
    score_->setZValue(Z_PLANE_HUD);
    help_->setZValue(Z_PLANE_HUD);
    about_->setZValue(Z_PLANE_HUD);
    back_->setZValue(Z_PLANE_HUD);
    gameOver_->setZValue(Z_PLANE_HUD);
    scoretext_->setZValue(Z_PLANE_HUD);
    helptext_->setZValue(Z_PLANE_HUD);
    abouttext_->setZValue(Z_PLANE_HUD);

    title_->setPlainText(MENU_TITLE);
    score_->setPlainText(MENU_SCORE);
    help_->setPlainText(MENU_HELP);
    about_->setPlainText(MENU_ABOUT);
    start_->setPlainText(MENU_START);
    back_->setPlainText(MENU_BACK);
    gameOver_->setPlainText(MENU_GAMEOVER);

    abouttext_->setPlainText(MENU_ABOUT_TEXT);
    helptext_->setPlainText(MENU_HELP_TEXT);
    scoretext_->setPlainText(MENU_SCORE_TEXT);

    scoretext_->setPos((GAME_WIDTH/2.0)-scoretext_->boundingRect().center().x(), MENU_START_Y);
    helptext_->setPos((GAME_WIDTH/2.0)-helptext_->boundingRect().center().x(), MENU_START_Y);
    abouttext_->setPos((GAME_WIDTH/2.0)-abouttext_->boundingRect().center().x(), MENU_START_Y);

    scoretext_->setDefaultTextColor(Qt::darkCyan);
    helptext_->setDefaultTextColor(Qt::darkMagenta);
    abouttext_->setDefaultTextColor(Qt::darkBlue);

    title_->setPos((GAME_WIDTH/2.0)-title_->boundingRect().center().x(), MENU_TITLE_Y);
    start_->setPos(MENU_X, MENU_START_Y);
    score_->setPos(MENU_X, MENU_SCORE_Y);
    help_->setPos(MENU_X, MENU_HELP_Y);
    about_->setPos(MENU_X, MENU_ABOUT_Y);
    back_->setPos((GAME_WIDTH/2.0)-back_->boundingRect().center().x(), MENU_BACK_Y);
    gameOver_->setPos((GAME_WIDTH/2.0)-gameOver_->boundingRect().center().x(), GAME_HEIGHT/3.0);

    gameOver_->configureColorAnimation(1000, true, Qt::red);
    gameOver_->configureSizeAnimation(1000, true, Qt::red);

    time_ = 0;

    showMenu();
}

void Menu::update(Game *game, int dt)
{
    time_ += dt;
    Q_UNUSED(game)
}

void Menu::show(bool show)
{
    start_->setVisible(show);
    score_->setVisible(show);
    help_->setVisible(show);
    about_->setVisible(show);
    title_->setVisible(show);
    abouttext_->setVisible(false);
    helptext_->setVisible(false);
    scoretext_->setVisible(false);
}

void Menu::startSlot()
{
    emit start();
}

void Menu::showAbout()
{
    show(false);
    title_->setVisible(true);
    abouttext_->setVisible(true);
    back_->setVisible(true);
}

void Menu::showScore()
{
    show(false);
    title_->setVisible(true);
    scoretext_->setVisible(true);
    back_->setVisible(true);
}

void Menu::showHelp()
{
    show(false);
    title_->setVisible(true);
    helptext_->setVisible(true);
    back_->setVisible(true);
}

void Menu::showGameOver()
{
    show(false);
    title_->setVisible(true);
    gameOver_->setVisible(true);
    back_->setVisible(true);
    gameOver_->animateColor();
    gameOver_->animateSize();
}

void Menu::showMenu()
{
    emit showSignal();
    show(true);
    back_->setVisible(false);
    gameOver_->setVisible(false);
    gameOver_->reset();
    title_->animateColor();
    title_->animateSize();
}

void Menu::startEvent()
{
    emit start();
    show(false);
    back_->setVisible(false);
    title_->setVisible(false);
}

