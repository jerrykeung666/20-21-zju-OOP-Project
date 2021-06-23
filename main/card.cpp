#include "card.h"

Card::Card(QObject *parent) : QObject(parent)
{

}

Card::Card(CardPoint p, CardSuit s)
{
    point = p;
    suit = s;
}

Card::Card(const Card &card) : point(card.point), suit(card.suit)
{

}

bool Card::operator<(const Card &card) const
{
    if (this->point != card.point) {
        return this->point < card.point;
    }
    return this->suit < card.suit;
}

bool Card::operator==(const Card &card) const
{
    return this->point == card.point && this->suit == card.suit;
}
