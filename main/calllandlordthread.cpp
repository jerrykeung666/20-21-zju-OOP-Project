#include "calllandlordthread.h"

CallLandLordThread::CallLandLordThread(Player* player)
{
    this->player = player;
}

void CallLandLordThread::run()
{
    msleep(600);
    player->thinkCallLord();
}
