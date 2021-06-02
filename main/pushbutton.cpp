#include "pushbutton.h"

#include <QPropertyAnimation>
#include <QDebug>

pushbutton::pushbutton(QString inputpath)
{
    inputImgPath = inputpath;

    QPixmap pix;
    bool ret = pix.load(inputImgPath);
    if(!ret) return;

    // set pic size
    setFixedSize(pix.width(), pix.height());

    // set Icon size
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));
}


void pushbutton::zoom_in_out(){
    QPropertyAnimation animation(this, "geometry");

    // set duration
    animation.setDuration(1000);

    // set startvalue & endvalue
    animation.setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //animation.setEndValue(QRect(this->x(), this->y(), this->width()*0.75, this->height()*0.75));
    animation.setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));

    // set curves
    animation.setEasingCurve(QEasingCurve::OutBounce);

    // start animation
    animation.start();
}


void pushbutton::on_pushbutton_clicked(){
    qDebug() << "Enter mode";
    this->zoom_in_out();
}


//pushbutton::~pushbutton(){}
