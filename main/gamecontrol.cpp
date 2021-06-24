#include "gamecontrol.h"
#include "cardgroups.h"
#include <QMessageBox>
#include <QTime>

GameControl::GameControl(QObject *parent) :
    QObject(parent)
{
    currentPlayer = NULL;
    //current_combo = CardGroups(); //有效牌
    //landLordCards = CardGroups();
    effectivePlayer = NULL;

    betCalledNum = 0;
}

void GameControl::init()
{
    playerA = new Player(this);
    playerB = new Player(this);
    playerC = new Player(this);

    playerA->setPlayerID(1);
    playerB->setPlayerID(2);
    playerC->setPlayerID(3);

    playerA->setIsPerson(true);


    playerA->setNextPlayer(playerB);
    playerB->setNextPlayer(playerC);
    playerC->setNextPlayer(playerA);

    currentPlayer = playerA;
}

void GameControl::initAllCards(){
    for(int pt = Card_Begin+1;pt<Card_SJ;pt++){
        for (int st = Suit_Begin+1;st<Suit_End;st++){
            Card tcard((CardPoint)pt, (CardSuit)st);
            allCards.push_back(tcard);
        }
    }

    //单独初始化大小王
    Card scard(Card_SJ,Suit_Begin);
    allCards.push_back(scard);
    Card bcard(Card_BJ,Suit_Begin);
    allCards.push_back(bcard);
}

QVector<Card> GameControl::getRandomCards(int cardnum){
    QVector<Card> sdcards;
    for (int i=1;i<=cardnum;i++){
        int num =  allCards.size();
        QTime time;
        time = QTime::currentTime();
        qsrand(time.msec() + time.second() * 1000);
        int randomIndex=qrand()%num;
        QVector<Card>::iterator it=allCards.begin()+randomIndex;
        Card takecard = *it;
        allCards.erase(it);
        sdcards.push_back(takecard);
    }
    return sdcards;
}



void GameControl::initCards(){
    //初始化所有卡牌
    initAllCards();

    //给玩家发牌
    playerA->setHandCards(getRandomCards(17));
    playerB->setHandCards(getRandomCards(17));
    playerC->setHandCards(getRandomCards(17));

    //留下地主牌
    landLordCards = getRandomCards(3);

    emit callGamewindowShowCards();
    // debug
    playerA->showCards();
    playerB->showCards();
    playerC->showCards();

    for (const auto &card : landLordCards) {
        qDebug() << "card: " << card.point << " " << card.suit;
    }
}

void GameControl::updateBetPoints(int bet){
    //记录每个玩家叫分
    BetRecord tbet;
    tbet.player = currentPlayer;
    tbet.bet = bet;
    betList.push_back(tbet);

    //叫3分直接地主
    if (bet ==3){
        currentPlayer->setIsLandLord(true);
        return;
    }

    //叫完分判断谁是地主
    if(betList.size() == 3){
        QVector<BetRecord>::iterator landlord = betList.begin();
        for(QVector<BetRecord>::iterator it = betList.begin()+1; it < betList.end(); it++){
            if (it->bet > landlord->bet){
                landlord = it;
            }
        }
        landlord->player->setIsLandLord(true);
        landlord->player-> addLandLordCards(landLordCards);
        return;
    }

    //继续叫分
    currentPlayer = currentPlayer->getNextPlayer();
    if (currentPlayer->getIsPerson()){
        //emit  //通知前段显示叫分button
    }
    else{
       //调用机器人策略
    }

}





Player* GameControl::getCurrentPlayer(){
    return currentPlayer;
}
Player* GameControl::getPlayerA(){
    return playerA;
}
Player* GameControl::getPlayerB(){
    return playerB;
}
Player* GameControl::getPlayerC(){
    return playerC;
}
/*
CardGroups GameControl::GetCurrentCombo(){
    return current_combo;
}
*/
Player* GameControl::getEffectivePlayer(){
    return effectivePlayer;
}

QVector<Card> GameControl::getLandLordCards(){
    return landLordCards;
}


