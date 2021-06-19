#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QBitmap>
#include <QPropertyAnimation>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

#include "cardview.h"

const int CardView::width = 100;
const int CardView::height = 140;
const int CardView::overlap = CardView::width / 4; // TODO
// TODO

CardView::CardView(QObject *parent) : QObject(parent)
{

}

//void CardView::select();

//void CardView::flip();

//void CardView::unselect();

bool CardView::isSelected(){
    return isSelect;
}

//void CardView::setLeftCards();

//void CardView::setRightCards();

//void CardView::setLandlordCards();

//void CardView::hoverEnterEvent(QGraphicsSceneHoverEvent *);

//void CardView::hoverLeaveEvent(QGraphicsSceneHoverEvent *);

//void CardView::mousePressEvent(QGraphicsSceneMouseEvent *);
