#include "calllandlordthread.h"
#include "player.h"

CallLandLordThread::CallLandLordThread(Player* player):QThread(player)
{
    m_player = player;
}

void CallLandLordThread::run()
{
    msleep(20);
    m_player->thinkCallLord();
    //exec();
}
