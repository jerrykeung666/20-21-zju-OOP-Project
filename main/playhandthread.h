#ifndef PLAYHANDTHREAD_H
#define PLAYHANDTHREAD_H
#include "player.h"
#include <QThread>
class PlayHandThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayHandThread(Player* player);

protected:
    virtual void run();

private:
    Player* player;
};

#endif // PLAYHANDTHREAD_H
