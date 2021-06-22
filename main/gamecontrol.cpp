#include "gamecontrol.h"
#include "cardgroups.h"
#include <QMessageBox>
#include <QTime>

GameControl::GameControl(QObject *parent) :
    QObject(parent)
{
    current_player = NULL;
    //current_combo = CardGroups(); //有效牌
    //landlordCards = CardGroups();
    effective_player = NULL;

    betCalledNum = 0;
}

void GameControl::Init()
{
    playerA = new Player(this);
    playerB = new Player(this);
    playerC = new Player(this);

    playerA->setPlayerID(1);
    playerB->setPlayerID(2);
    playerC->setPlayerID(3);

    playerA->setIsPerson(true);


    playerA-> setNextPlayer(playerB);
    playerB-> setNextPlayer(playerC);
    playerC-> setNextPlayer(playerA);

    current_player = playerA;
}

void GameControl::InitAllcars(){
    for(int pt = Card_Begin+1;pt<Card_SJ;pt++){
        for (int st = Suit_Begin+1;st<Suit_End;st++){
            Card tcard(pt,st);
            m_allcards.push_back(tcard);
        }
    }

    //单独初始化大小王
    Card scard(Card_SJ,Suit_Begin);
    m_allcards.push_back(scard);
    Card bcard(Card_BJ,Suit_Begin);
    m_allcards.push_back(bcard);
}

QVector<Card> GameControl::GetRandomCards(int cardnum){
    QVector<Card> sdcards;
    for (int i=1;i<=cardnum;i++){
        int num =  m_allcards.size();
        QTime time;
        time = QTime::currentTime();
        qsrand(time.msec() + time.second() * 1000);
        int randomIndex=qrand()%num;
        QVector<Card>::iterator it=m_allcards.begin()+randomIndex;
        Card takecard = *it;
        m_allcards.erase(it);
        sdcards.push_back(takecard);
    }
    return sdcards;
}



void GameControl::initCards(){
    //初始化所有卡牌
    InitAllcars();

    //给玩家发牌
    playerA->setHandCards(GetRandomCards(17));
    playerB->setHandCards(GetRandomCards(17));
    playerC->setHandCards(GetRandomCards(17));

    //留下地主牌
    landlordCards = GetRandomCards(3);
}

void GameControl::updateBetPoints(int bet){
    //记录每个玩家叫分
    BetRecord tbet;
    tbet.player = current_player;
    tbet.bet = bet;
    betlist.push_back(tbet);

    //叫3分直接地主
    if (bet ==3){
        current_player->setIsLandLord(true);
        return;
    }

    //叫完分判断谁是地主
    if(betlist.size() == 3){
        QVector<BetRecord>::iterator landlord = betlist.begin();
        for(QVector<BetRecord>::iterator it = betlist.begin()+1; it < betlist.end(); it++){
            if (it->bet > landlord->bet){
                landlord = it;
            }
        }
        landlord->player->setIsLandLord(true);
        landlord->player-> addLandLordCards(landlordCards);
        return;
    }

    //继续叫分
    current_player = current_player->getNextPlayer();
    if (current_player->getIsPerson()){
        //emit  //通知前段显示叫分button
    }
    else{
       //调用机器人策略
    }

}





Player* GameControl::GetCurrentPlayer(){
    return current_player;
}
Player* GameControl::GetPlayerA(){
    return playerA;
}
Player* GameControl::GetPlayerB(){
    return playerB;
}
Player* GameControl::GetPlayerC(){
    return playerC;
}
/*
CardGroups GameControl::GetCurrentCombo(){
    return current_combo;
}
*/
Player* GameControl::GetEffectivePlayer(){
    return effective_player;
}
/*
CardGroups* GameControl::GetLandlordCards(){
    return landlordCards;
}
*/


