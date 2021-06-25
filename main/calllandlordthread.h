#ifndef CALLLANDLORDTHREAD_H
#define CALLLANDLORDTHREAD_H

#include <QThread>
//#include "player.h"
class Player;

class CallLandLordThread : public QThread
{
    Q_OBJECT
public:
    explicit CallLandLordThread(Player* player);

protected:
    virtual void run();

private:
    Player* m_player;

};

#endif // CALLLANDLORDTHREAD_H
