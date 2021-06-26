#include "player.h"
#include <QDebug>

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

Player* Player::getPunchPlayer()
{
    return punchPlayer;
}

CardGroups Player::getPunchCards()
{
    return punchCards;
}


void Player::setHandCards(const QVector<Card> &cards)
{
    handCards << cards;
    sortHandCards();
}

QVector<Card> Player::getHandCards() const
{
    return handCards;
}

void Player::setSelectCards(const QVector<Card> &cards)
{
    selectCards.setCards(cards);
}

QVector<Card> Player::getSelectCards() const
{
    return selectCards.getCards();
}

void Player::setBetPoints(int bet)
{
    //qDebug() << "robot think";
    betPoints = bet;
}

void Player::callLord(int bet){
    emit notifyCallLord(bet);
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
        if (a.point != b.point) {
            return a.point < b.point;
        } else {
            return a.suit < b.suit;
        }
    });
}

void Player::showCards()
{
    qDebug() << "show cards";
    for (auto &card : handCards) {
        qDebug() << "card: " << card.point << " " << card.suit;
    }
}

void Player::clear()
{
    handCards.clear();
}

void Player::startCallLord()
{

}

void Player::startPlayHand()
{

}

void Player::thinkCallLord()
{

}

void Player::thinkPlayHand()
{

}

void Player::onPlayerPunch(Player* player, const CardGroups& cards)
{
    this->punchPlayer = player;
    punchCards = cards;
}

void Player::playHand(const QVector<Card> &cards)
{
    for (auto &card : cards) {
        handCards.removeOne(card);
    }
}
