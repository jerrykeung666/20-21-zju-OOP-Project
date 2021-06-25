#ifndef USER_H
#define USER_H
#include "player.h"

#include <QObject>
class User : public Player
{
    Q_OBJECT
public:
    User(QObject* parent = NULL);
    virtual void startCallLord();
    virtual void startPlayHand();
};

#endif // USER_H
