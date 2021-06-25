#include "cardwidget.h"
#include <QPainter>
#include <QMouseEvent>

CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
    owner = NULL;
    isSelected = false;
    isFront = true;
    back = QPixmap(":/PokerImage/back.png");
}

void CardWidget::setPix(const QPixmap &pix)
{
    this->pix = pix;
    resize(pix.size());
}

QPixmap CardWidget::getPix() const
{
    return pix;
}

void CardWidget::setOwner(Player *owner)
{
    this->owner = owner;
}

Player* CardWidget::getOwner() const
{
    return owner;
}

void CardWidget::setCard(const Card &card)
{
    this->card = card;
}

Card CardWidget::getCard() const
{
    return card;
}

void CardWidget::setFront(bool isFront)
{
    if (this->isFront != isFront) {
        this->isFront = isFront;
        //update();
    }
}

bool CardWidget::getIsFront() const
{
    return isFront;
}

void CardWidget::setIsSelected(bool isSelect)
{
    this->isSelected = isSelect;
}

bool CardWidget::getIsSelected() const
{
    return isSelected;
}

void CardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (isFront) {
        painter.drawPixmap(rect(), pix);
    } else {
        painter.drawPixmap(rect(), back);
    }
}

void CardWidget::mousePressEvent(QMouseEvent *event)
{
    emit notifySelected(event->button());
    QWidget::mousePressEvent(event);
}

