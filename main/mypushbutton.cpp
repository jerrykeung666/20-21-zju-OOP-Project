#include "mypushbutton.h"
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(const QString &inputpath, const QString &modeinfo)
{
    inputImgPath = inputpath;
    buttonModeInfo = modeinfo;

    QPixmap pix;
    bool ret = pix.load(inputImgPath);
    if(!ret) return;

    // set pic size
    setFixedSize(pix.width()-10, pix.height()-10);

    // set Icon size
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButton::zoomIn()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    // set duration
    animation->setDuration(50);

    // set startvalue & endvalue
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));

    // set curves
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // set loops
    animation->setLoopCount(10);

    // start animation
    animation->start();
}

void MyPushButton::zoomOut()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    // set duration
    animation->setDuration(50);

    // set startvalue & endvalue
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    // set curves
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // set loops
    animation->setLoopCount(10);

    // start animation
    animation->start();
}
