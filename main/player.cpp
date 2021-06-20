#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

void Player::setPlayerID(int ID)
{
    playerID = ID;
}

int Player::getPlayerID() const
{
    return playerID;
}

void Player::setHandCards(const QVector<Card> &cards)
{
    handCards = cards;
    sortHandCards();
}

QVector<Card> Player::getHandCards() const
{
    return handCards;
}

void Player::setBetPoints(int bet)
{
    betPoints = bet;
}

int Player::getBetPoints() const
{
    return betPoints;
}

void Player::setIsLandLord(bool isLandLord)
{
    this->isLandLord = isLandLord;
}

bool Player::getIsLandLord()
{
    return isLandLord;
}

void Player::setIsPerson(bool isPerson)
{
    this->isPerson = isPerson;
}

bool Player::getIsPerson()
{
    return isPerson;
}

void Player::setNextPlayer(Player *next)
{
    nextPlayer = next;
}

Player* Player::getNextPlayer()
{
    return nextPlayer;
}

int Player::getCardsNumber() const
{
    return handCards.size();
}

bool Player::isWin()
{
    return getCardsNumber() == 0;
}

void Player::addLandLordCards(const QVector<Card> &cards)
{
    for (auto &card : cards) {
        handCards.push_back(card);
    }
    sortHandCards();
}

bool Player::checkCardValid(CardGroups &currentCombo)
{
    int selectNum = selectCards.getCardsNum();
    if (currentCombo.getCardsNum() != selectNum && selectNum != 4 && selectNum != 2) {
        return false;  // 跟牌，但是牌数与上一个玩家的牌数不符且不可能为炸弹，牌无效，只有加速的作用
    }

    selectCards.analyseCards();  // 对选中牌进行分析

    if (selectCards.getCardsType() == GroupType::Group_Unknown) {  // 无效牌
        return false;
    } else if (selectCards.getCardsType() == GroupType::Group_Bomb_Jokers) {  // 玩家牌为王炸
        return true;
    } else if (currentCombo.getCardsType() == GroupType::Group_Bomb_Jokers) { // 前一个人为王炸
        return false;
    } else if (selectCards.getCardsType() == GroupType::Group_Bomb &&
               (currentCombo.getCardsType() != GroupType::Group_Bomb ||
                selectCards.getBasePoint() > currentCombo.getBasePoint())) {  // 玩家牌为炸弹并且前一个不为炸弹或者点数比当前的小
        return true;
    } else if (selectCards.getCardsType() != currentCombo.getCardsType() ||
               selectCards.getCardsNum() != currentCombo.getCardsNum()) {  // 牌型不符或者数量不符
        return false;
    } else if (selectCards.getBasePoint() < currentCombo.getBasePoint()) { // 点数比较小
        return false;
    } else {
        return true;
    }

}

void Player::sortHandCards()
{
    std::sort(handCards.begin(), handCards.end(), [](Card &a, Card &b){
        if (a.point < b.point) {
            return a.point < b.point;
        } else {
            return a.suit < b.suit;
        }
    });
}
