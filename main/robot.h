#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "player.h"

class Robot : public Player
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = nullptr);

signals:

};

#endif // ROBOT_H
