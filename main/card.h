#ifndef CARD_H
#define CARD_H

#include <QObject>

// 点数
enum CardPoint
{
    Card_Begin,

    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,

    Card_SJ,
    Card_BJ,

    Card_End
};

// 花色
enum CardSuit
{
    Suit_Begin,

    Diamond,	// 方块
    Club,		// 梅花
    Heart,		// 红桃
    Spade,		// 黑桃

    Suit_End
};


class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = nullptr);
    Card(CardPoint p = Card_Begin, CardSuit s = Suit_Begin);
    CardPoint point;
    CardSuit suit;
};

#endif // CARD_H
