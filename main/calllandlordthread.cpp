
#include "calllandlordthread.h"
#include "player.h"

CallLandLordThread::CallLandLordThread(Player* player):QThread(player)
{
    this->player = player;
}

void CallLandLordThread::run()
{
<<<<<<< HEAD
    msleep(20);
    m_player->thinkCallLord();
=======
    msleep(600);
    player->thinkCallLord();
>>>>>>> d4aa0541c819e43396cf057a2b1d3e5afcb4f894
    //exec();
}
