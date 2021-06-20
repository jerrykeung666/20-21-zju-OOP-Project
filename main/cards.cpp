#include "cards.h"

Cards::Cards(QObject *parent) : QObject(parent)
{

}

int Cards::size()
{
    return cards.size();
}
