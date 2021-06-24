#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPixmap>
#include "card.h"

class Player;

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(QWidget *parent = nullptr);

    void setPix(const QPixmap &pix, const QPixmap &back);
    QPixmap getPix() const;

    void setOwner(Player *owner);
    Player* getOwner() const;

    void setCard(const Card &card);
    Card getCard() const;

    void setFront(bool isFront);
    bool getIsFront() const;

    void setIsSelected(bool isSelect);
    bool getIsSelected() const;

signals:
    void notifySelected(Qt::MouseButton);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    bool isSelected;
    bool isFront;

    Player *owner;
    QPixmap pix;
    QPixmap back;
    Card card;
};

#endif // CARDWIDGET_H
