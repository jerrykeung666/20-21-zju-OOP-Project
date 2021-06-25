#include "gamecontrol.h"
#include "cardgroups.h"
#include <QMessageBox>
#include <QTime>
#include <random>

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
    playerA = new User(this);
    playerB = new Robot(this);
    playerC = new Robot(this);

    playerA->setPlayerID(1);
    playerB->setPlayerID(2);
    playerC->setPlayerID(3);

    playerA->setIsPerson(true);
    playerB->setIsPerson(false);
    playerC->setIsPerson(false);


    playerA->setNextPlayer(playerB);
    playerB->setNextPlayer(playerC);
    playerC->setNextPlayer(playerA);


    connect(playerC, &Robot::notifyCallLord, this, &GameControl::updateBetPoints);
    connect(playerB, &Robot::notifyCallLord, this, &GameControl::updateBetPoints);
    //connect(playerA, &Robot::notifyCallLord, this, &GameControl::updateBetPoints);

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

    std::default_random_engine generator (time(nullptr));
    std::uniform_int_distribution<unsigned int> u(0, 53);
    for (int i = 1; i < 54; i++){
        int index = u(generator);
        std::swap(allCards[i], allCards[index]);
    }

    qDebug() << "allcards";
    for (auto &card : allCards) {
        qDebug() << "card: " << card.point << card.suit;
    }
}

QVector<Card> GameControl::getRandomCards(int start, int cardnum){
    QVector<Card> sdcards;
    for (int i = start; i < start + cardnum; i++){
//        int num =  allCards.size();
//        QTime time;
//        time = QTime::currentTime();
//        qsrand(time.msec() + time.second() * 1000);
//        int randomIndex=qrand()%num;
//        QVector<Card>::iterator it=allCards.begin()+randomIndex;
//        Card takecard = *it;
//        allCards.erase(it);
        sdcards.push_back(allCards[i]);
    }
    qDebug() << "random cards";
    for (auto &card : sdcards) {
        qDebug() << "card: " << card.point << card.suit;
    }
    return sdcards;
}



void GameControl::initCards(){
    //初始化所有卡牌
    initAllCards();

    //给玩家发牌
    playerA->setHandCards(getRandomCards(0, 17));
    playerB->setHandCards(getRandomCards(17, 17));
    playerC->setHandCards(getRandomCards(34, 17));

    //留下地主牌
    landLordCards = getRandomCards(51, 3);

//    emit callGamewindowShowCards();
    // debug
    playerA->showCards();
    playerB->showCards();
    playerC->showCards();

    qDebug() << "地主牌";
    for (auto &card : landLordCards) {
        qDebug() << "card: " << card.point << " " << card.suit;
    }

    allCards.clear();
}

void GameControl::updateBetPoints(int bet){
    //记录每个玩家叫分
    BetRecord tbet;
    tbet.player = currentPlayer;
    tbet.bet = bet;
    betList.push_back(tbet);
    currentPlayer->setBetPoints(bet);
    qDebug() << "bet:" << bet;

    emit callGamewindowShowBets(currentPlayer);

    //叫3分直接地主
    if (bet ==3){
        currentPlayer->setIsLandLord(true);
        currentPlayer->addLandLordCards(landLordCards);
        emit callGamewindowShowLandlord();
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
        landlord->player->addLandLordCards(landLordCards);
        //qDebug() << "GameControl: card num: " << playerA->getHandCards().size();
        emit callGamewindowShowLandlord();
        return;
    }

    //继续叫分
    currentPlayer = currentPlayer->getNextPlayer();
    if (currentPlayer->getIsPerson()){
        //emit  //通知前段显示叫分button
    }
    else{
       //调用机器人策略
       //emit 调用自己
       //emit callGamewindowShowBets(currentPlayer);
       qDebug() << "call robot";
       currentPlayer->startCallLord();
    }
/*
    currentPlayer = currentPlayer->getNextPlayer();
    if (currentPlayer->getIsPerson()){
        //emit  //通知前段显示叫分button
    }
    else{
       //调用机器人策略
       //emit 调用自己
       emit callGamewindowShowBets(currentPlayer);
    }

    currentPlayer->setIsLandLord(true);
    emit callGamewindowShowLandlord();
*/

}





Player* GameControl::getCurrentPlayer(){
    return currentPlayer;
}
User* GameControl::getPlayerA(){
    return playerA;
}
Robot* GameControl::getPlayerB(){
    return playerB;
}
Robot* GameControl::getPlayerC(){
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


