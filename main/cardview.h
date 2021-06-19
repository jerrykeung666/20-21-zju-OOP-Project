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

public:
    // card view properties
    // TODO
    static const int width;
    static const int height;
    static const int overlap;

protected:
    // animations
    // TODO
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

public:
    explicit CardView(QObject *parent = nullptr);

    //void select();
    //void flip();

signals:

};

#endif // CARDVIEW_H
