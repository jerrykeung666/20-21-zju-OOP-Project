#include "card.h"

Card::Card(QObject *parent) : QObject(parent)
{

}

Card::Card(CardPoint p, CardSuit s)
{
    point = p;
    suit = s;
}
