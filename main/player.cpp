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
    currentCombo.analyseCards();
    return currentCombo.getCardsType() > Group_Unknown;
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

void Player::showCards()
{
    qDebug() << "show cards";
    for (const auto &card : handCards) {
        qDebug() << "card: " << card.point << " " << card.suit;
    }
}
