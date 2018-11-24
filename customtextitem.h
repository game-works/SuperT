#ifndef ANIMATEDQGRAPHICSTEXTITEM_H
#define ANIMATEDQGRAPHICSTEXTITEM_H

#include <QGraphicsTextItem>

class QTimeLine;
class QGraphicsItemAnimation;

static const int DEFAULT_SIZE_ANIM_TIME = 1000;
static const int DEFAULT_COLOR_ANIM_TIME = 1000;

static const QColor DEFAULT_SIZE_ANIM_COLOR = Qt::darkRed;
static const QColor DEFAULT_COLOR_ANIM_COLOR = Qt::yellow;

const static int DEFAULT_SIZE_ANIM_UPPER_FRAME = 20;
const static qreal DEFAULT_SIZE_ANIM_SCALE = 0.02;

const static int DEFAULT_COLOR_ANIM_UPPER_FRAME = 50;

static const int KEY_COLOR = 1;

//!
//! \brief The CustomTextItem class - this is a graphic text item with two types of
//! animations and a click handling event,
//! the item can be animated in scale with an mouse hover event, or by calling the proper animation method
//! and the item can be color animated by clicking on the item or calling the proper animation method
//!
class CustomTextItem : public QGraphicsTextItem
{
    Q_OBJECT

signals:
    void clickEvent();

public:
    CustomTextItem(QColor color, bool hoverable = true, bool clickable = true, QGraphicsItem *parent = nullptr);
    ~CustomTextItem();

    //!
    //! \brief configureSizeAnimation - custom configuration for size animation
    //! \param time - the total amount of animation time
    //! \param loop - if true will run forever
    //! \param color - the color changes when a hoovering event ocurrs
    //!
    void configureSizeAnimation(int time = 1000, bool loop = false, QColor color = DEFAULT_SIZE_ANIM_COLOR);

    //!
    //!    //! \brief configureColorAnimation - custom configuration for color animation
    //!    //! \param time - the total amount of animation time
    //!    //! \param loop - if true will run forever
    //!    //! \param color - the color that will be used in the flicking effect
    void configureColorAnimation(int time = 1000, bool loop = false, QColor color = DEFAULT_COLOR_ANIM_COLOR);

    void reset();

    // QGraphicsItem interface
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    //!
    //! \brief animateSize - starts the scale/size animation
    //!
    void animateSize();
    //!
    //! \brief animateColor - starts the color animation
    //!
    void animateColor();


protected slots:
    void clicked();
    void sizeLoop();
    void colorLoop();
    void colorAnimationStep();
    void restoreColor();


private:

    QTimeLine *sizetimer_;

    bool sizeloop_;

    bool hoverable_;

    QGraphicsItemAnimation *animation_;

    QTimeLine *colortimer_;

    bool colorloop_;

    bool clickable_;

    bool flick_;

    QColor colorAnimColor_;

    QColor sizeAnimColor_;

    QColor defaultColor_;
};

#endif // ANIMATEDQGRAPHICSTEXTITEM_H
