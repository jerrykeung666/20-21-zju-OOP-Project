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

public:
    explicit CardView(QObject *parent = nullptr);

signals:

};

#endif // CARDVIEW_H
