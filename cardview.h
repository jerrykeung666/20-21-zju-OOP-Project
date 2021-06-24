#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QObject>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPushButton>

class CardView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

private:
    // TODO
    QString imagePath;
    bool isSelect;
    QPointF stdPos;

public:
    // card view properties
    // TODO
    static const int width;
    static const int height;
    static const int overlap;
    static const int animationDuration;
    static const int upDist;

protected:
    // animations
    // TODO
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

public:
    explicit CardView(QObject *parent = nullptr);

    void setStdPos(const QPointF &_stdPos);

    void select();
    void flip();
    void unselect();
    bool isSelected();

    void setLeftCards();
    void setRightCards();
    void setLandlordCards();
    //void setMyCards();

signals:

};

#endif // CARDVIEW_H
