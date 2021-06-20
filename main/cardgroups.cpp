#include "cardgroups.h"

CardGroups::CardGroups(QObject *parent) : QObject(parent)
{

}


void CardGroups::addCard(Card card)
{
    cards.push_back(card);
}

int CardGroups::getCardsNum()
{
    return cards.size();
}

CardPoint CardGroups::getBasePoint()
{
    return basePoint;
}

void CardGroups::analyseCards()
{

}
