#include "robot.h"
#include "calllandlordthread.h"
#include <QDebug>

Robot::Robot(QObject *parent) : Player(parent)
{
    isPerson = false;
}

void Robot::startCallLord()
{
    CallLandLordThread* thread = new CallLandLordThread(this);
    thread->start();
}

void Robot::startPlayHand()
{

}

void Robot::thinkCallLord()
{
    qDebug() << "1111";
    callLord(0);

}

void Robot::thinkPlayHand()
{

}
