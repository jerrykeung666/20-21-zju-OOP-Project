#ifndef CARDS_H
#define CARDS_H

#include <QObject>
#include <QVector>

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

// 单张牌
struct Card
{
    CardPoint point;
    CardSuit suit;
    Card() : point(Card_Begin), suit(Suit_Begin) {}
};


class Cards : public QObject
{
    Q_OBJECT
public:
    explicit Cards(QObject *parent = nullptr);
    int size();

public:
    QVector<Card> cards;

};

#endif // CARDS_H
