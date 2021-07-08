#include "playhandthread.h"
#include <QMetaType>

PlayHandThread::PlayHandThread(Player* player) :
    QThread(player)
{
    qRegisterMetaType<Card>("Card");
    //qRegisterMetaType<CardGroups>("cards");
    qRegisterMetaType<QVector<Card>>("QVector<Card>");
    this->player = player;
}

void PlayHandThread::run()
{
    msleep(600);
    this->player->thinkPlayHand();
}
