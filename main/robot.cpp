#include "robot.h"
#include "calllandlordthread.h"
#include "strategy.h"
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
    CardGroups cg;
    qDebug() << "robot thinking hand card";
    emit notifyPlayHand(this,cg);
}

void Robot::thinkCallLord()
{
    int weight = 0;
    Strategy st(this, handCards);
    weight += st.getRangeCards(Card_SJ, Card_BJ).size() * 6;
    int count = st.countOfPoint(handCards, Card_2);
    weight += count * 3;

    QVector<QVector<Card>> optSeq = st.pickOptimalSeqSingles();
    weight += optSeq.size() * 5;

    QVector<Card> left = handCards;
    for(int i=0;i<optSeq.size();i++)
            for(int j=0;j<optSeq[i].size();j++)
                left.removeOne(optSeq[i][j]);
    Strategy stLeft(this, left);

    QVector<QVector<Card>> bombs = stLeft.findCardsByCount(4);
    weight += bombs.size() * 5;

    QVector<QVector<Card>> triples = stLeft.findCardsByCount(3);
    weight += triples.size() * 4;

    QVector<QVector<Card>> pairs = stLeft.findCardsByCount(2);
    weight += pairs.size() * 1;

    if (weight >= 22)
    {
        setBetPoints(3);
        qDebug() << "call 3";
        callLord(3);
    }
    else if (weight < 22 && weight >= 18)
    {
        setBetPoints(2);
        qDebug() << "call 2";
        callLord(2);
    }
    else if (weight > 18 && weight >= 10)
    {
        setBetPoints(1);
        qDebug() << "call 1";
        callLord(1);
    }
    else
    {
        setBetPoints(0);
        qDebug() << "call 0";
        callLord(0);
    }
}

void Robot::thinkPlayHand()
{
    Strategy st(this, handCards);
    playHand(st.makeStragety());
}
