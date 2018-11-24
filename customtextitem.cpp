#include "customtextitem.h"

#include <QGraphicsItemAnimation>
#include <QTimeLine>

CustomTextItem::CustomTextItem(QColor color, bool hoverable, bool clickable, QGraphicsItem *parent)
    : QGraphicsTextItem (parent),
      sizetimer_(new QTimeLine),
      sizeloop_(false),
      hoverable_(hoverable),
      animation_(new QGraphicsItemAnimation),
      colortimer_(new QTimeLine),
      colorloop_(false),
      clickable_(clickable),
      flick_(false),
      colorAnimColor_(DEFAULT_COLOR_ANIM_COLOR),
      sizeAnimColor_(DEFAULT_SIZE_ANIM_COLOR),
      defaultColor_(std::move(color))
{
    setDefaultTextColor(defaultColor_);

    sizetimer_->setDuration(DEFAULT_SIZE_ANIM_TIME);
    sizetimer_->setFrameRange(0, DEFAULT_SIZE_ANIM_UPPER_FRAME);

    animation_->setTimeLine(sizetimer_);
    animation_->setItem(this);
    qreal scale = 1;
    //increase size
    for (int i = 0; i < DEFAULT_SIZE_ANIM_UPPER_FRAME/2; ++i)
    {
        scale += DEFAULT_SIZE_ANIM_SCALE;
        animation_->setScaleAt(i / static_cast<qreal>(DEFAULT_SIZE_ANIM_UPPER_FRAME), scale, scale);
    }
    //decrease size
    for (int i = DEFAULT_SIZE_ANIM_UPPER_FRAME/2; i < DEFAULT_SIZE_ANIM_UPPER_FRAME; ++i)
    {
        scale -= DEFAULT_SIZE_ANIM_SCALE;
        animation_->setScaleAt(i / static_cast<qreal>(DEFAULT_SIZE_ANIM_UPPER_FRAME), scale, scale);
    }
    colortimer_->setDuration(DEFAULT_COLOR_ANIM_TIME);
    colortimer_->setFrameRange(0, DEFAULT_COLOR_ANIM_UPPER_FRAME);

    connect(colortimer_, &QTimeLine::frameChanged, this, &CustomTextItem::colorAnimationStep);

    //! emits the clickEvent(); signal only when the animation finishes/
    if(clickable_)
        connect(colortimer_, &QTimeLine::finished, this, &CustomTextItem::clicked);

    connect(colortimer_, &QTimeLine::finished, this, &CustomTextItem::restoreColor);
}

CustomTextItem::~CustomTextItem()
{
    delete animation_;
    delete colortimer_;
    delete sizetimer_;
}

void CustomTextItem::configureSizeAnimation(int time, bool loop, QColor color)
{
    sizetimer_->setDuration(time);
    sizeAnimColor_ = std::move(color);
    if(loop)
        connect(sizetimer_, &QTimeLine::finished, this, &CustomTextItem::sizeLoop);

}

void CustomTextItem::configureColorAnimation(int time, bool loop, QColor color)
{
    colortimer_->setDuration(time);
    colorAnimColor_ = std::move(color);
    if(loop)
        connect(colortimer_, &QTimeLine::finished, this, &CustomTextItem::colorLoop);
}

void CustomTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(hoverable_)
    {
        setDefaultTextColor(sizeAnimColor_);
        animateSize();
        QGraphicsTextItem::hoverEnterEvent(event);
    }
}

void CustomTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(hoverable_)
    {
        setDefaultTextColor(defaultColor_);
        QGraphicsTextItem::hoverLeaveEvent(event);
    }
}

void CustomTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(clickable_)
    {
        animateColor();
        QGraphicsTextItem::mousePressEvent(event);
    }
}

void CustomTextItem::animateSize()
{
    if(sizetimer_->state() == QTimeLine::NotRunning)
        sizetimer_->start();
}

void CustomTextItem::animateColor()
{
    if(colortimer_->state() == QTimeLine::NotRunning)
        colortimer_->start();
}

void CustomTextItem::clicked()
{
    emit clickEvent();
}

void CustomTextItem::sizeLoop()
{
    sizetimer_->start();
}

void CustomTextItem::colorLoop()
{
    colortimer_->start();
}

void CustomTextItem::colorAnimationStep()
{
    if(flick_)
    {
        setDefaultTextColor(colorAnimColor_);
    }
    else
    {
        setDefaultTextColor(defaultColor_);
    }
    flick_ = !flick_;
}

void CustomTextItem::restoreColor()
{
    //restores original color
    setDefaultTextColor(defaultColor_);
}

void CustomTextItem::reset()
{
    colortimer_->stop();
    sizetimer_->stop();
}
