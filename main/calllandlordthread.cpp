
#include "calllandlordthread.h"
#include "player.h"

CallLandLordThread::CallLandLordThread(Player* player):QThread(player)
{
    this->player = player;
}

void CallLandLordThread::run()
{

    msleep(20);
    player->thinkCallLord();
    //exec();
}
