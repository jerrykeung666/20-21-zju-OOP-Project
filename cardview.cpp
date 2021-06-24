#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QBitmap>
#include <QPropertyAnimation>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "cardview.h"

const int CardView::width = 100;
const int CardView::height = 140;
const int CardView::overlap = CardView::width / 4; // TODO
const int CardView::animationDuration = 50;
const int CardView::upDist = CardView::height / 3;
// TODO

CardView::CardView(QObject *parent) : QObject(parent)
{

}

void CardView::setStdPos(const QPointF &_stdPos){
    stdPos = _stdPos;
}

void CardView::select(){
    isSelect = true;
    hoverEnterEvent(nullptr);
}

//void CardView::flip();

void CardView::unselect(){
    isSelect = false;
    hoverLeaveEvent(nullptr);
}

bool CardView::isSelected(){
    return isSelect;
}

//void CardView::setLeftCards();

//void CardView::setRightCards();

//void CardView::setLandlordCards();

void CardView::hoverEnterEvent(QGraphicsSceneHoverEvent *){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");

    animation->setDuration(animationDuration);
    animation->setEndValue(stdPos + QPointF(0, -upDist));

    animation->start();
}

void CardView::hoverLeaveEvent(QGraphicsSceneHoverEvent *){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");

    animation->setDuration(animationDuration);
    animation->setEndValue(stdPos);

    animation->start();
}

void CardView::mousePressEvent(QGraphicsSceneMouseEvent *){
    if(isSelected()) select();
    else unselect();

    qDebug() << "Selected!";
}
