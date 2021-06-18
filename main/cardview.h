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
    QString imagePath;
    bool isSelect;

public:
    // card view properties
    static const int width;
    static const int height;

public:
    explicit CardView(QObject *parent = nullptr);

signals:

};

#endif // CARDVIEW_H
