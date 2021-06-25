#include "robot.h"
#include "calllandlordthread.h"

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
    setBetPoints(3);
}

void Robot::thinkPlayHand()
{

}
