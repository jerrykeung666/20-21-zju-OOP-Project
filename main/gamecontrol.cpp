#include "gamecontrol.h"
#include "cardgroups.h"
#include <QMessageBox>

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


    playerA-> setNextPlayer(playerB);
    playerB-> setNextPlayer(playerC);
    playerC-> setNextPlayer(playerA);

    current_player = playerA;
}



void GameControl::initCards(){

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


