#ifndef CALLLANDLORDTHREAD_H
#define CALLLANDLORDTHREAD_H

#include <QThread>
#include "player.h"

class CallLandLordThread : public QThread
{
    Q_OBJECT
public:
    explicit CallLandLordThread(Player* player);

protected:
    virtual void run();

private:
    Player* player;

};

#endif // CALLLANDLORDTHREAD_H
