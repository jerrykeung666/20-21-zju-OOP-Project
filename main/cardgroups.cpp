#include "cardgroups.h"

CardGroups::CardGroups(QObject *parent) : QObject(parent)
{

}

void CardGroups::addCard(const Card &card)
{
    cards.push_back(card);
}

void CardGroups::clear()
{
    cards.clear();
}

int CardGroups::getCardsNum()
{
    return cards.size();
}

CardPoint CardGroups::getBasePoint()
{
    return basePoint;
}

int CardGroups::getExtraNum()
{
    return extraNum;
}

GroupType CardGroups::getCardsType()
{
    return type;
}

void CardGroups::analyseCards()
{
    QVector<int> cardMeta((int)CardPoint::Card_End, 0);

    for (auto &card : cards) {
        cardMeta[(int)card.point]++;
    }

    QVector<CardPoint> oneCard;
    QVector<CardPoint> twoCards;
    QVector<CardPoint> threeCards;
    QVector<CardPoint> fourCards;

    for (int i = 0; i < cardMeta.size(); ++i) {
        if (cardMeta[i] == 1) {
            oneCard.push_back((CardPoint)i);
        } else if (cardMeta[i] == 2) {
            twoCards.push_back((CardPoint)i);
        } else if (cardMeta[i] == 3) {
            threeCards.push_back((CardPoint)i);
        } else if (cardMeta[i] == 4) {
            fourCards.push_back((CardPoint)i);
        }
    }

    if (oneCard.isEmpty() && twoCards.isEmpty() &&
        threeCards.isEmpty() && fourCards.isEmpty()) {
        type = Group_Pass;
    } else if (oneCard.size() == 1 && twoCards.isEmpty() &&
               threeCards.isEmpty() && fourCards.isEmpty()) {
        type = Group_Single;  // 单牌
        basePoint = oneCard[0];
    } else if (oneCard.isEmpty() && twoCards.size() == 1 &&
               threeCards.isEmpty() && fourCards.isEmpty()) {
        type = Group_Pair;  // 对子
        basePoint = twoCards[0];
    } else if (oneCard.isEmpty() && twoCards.isEmpty() &&
               threeCards.size() == 1 && fourCards.isEmpty()) {
        type = Group_Triple;  //三张
        basePoint = threeCards[0];
    } else if (oneCard.size() == 1 && twoCards.isEmpty() &&
               threeCards.size() == 1 && fourCards.isEmpty()) {
        type = Group_Triple_Single;  // 三带一
        basePoint = threeCards[0];
    } else if (oneCard.isEmpty() && twoCards.size() == 1 &&
               threeCards.size() == 1 && fourCards.isEmpty()) {
        type = Group_Triple_Pair;  // 三带二
        basePoint = threeCards[0];
    } else if (oneCard.isEmpty() && twoCards.isEmpty() &&
               threeCards.size() == 2 && fourCards.isEmpty()) {
        std::sort(threeCards.begin(), threeCards.end());
        if (threeCards[1] - threeCards[0] == 1 && threeCards[1] < Card_2) {
            type = Group_Plane;  // 飞机
            basePoint = threeCards[0];
        }
    } else if (oneCard.size() == 2 && twoCards.isEmpty() &&
               threeCards.size() == 2 && fourCards.isEmpty()) {
        std::sort(threeCards.begin(), threeCards.end());
        std::sort(oneCard.begin(), oneCard.end());
        if (threeCards[1] - threeCards[0] == 1 && threeCards[1] < Card_2 &&
            oneCard[0] != CardPoint::Card_SJ && oneCard[0] != CardPoint::Card_BJ) {
            type = Group_Plane_Two_Single;  // 飞机带两单
            basePoint = threeCards[0];
        }
    } else if (oneCard.isEmpty() && twoCards.size() == 2 &&
               threeCards.size() == 2 && fourCards.isEmpty()) {
        std::sort(threeCards.begin(), threeCards.end());
        if (threeCards[1] - threeCards[0] == 1 && threeCards[1] < Card_2) {
            type = Group_Plane_Two_Pair;  // 飞机带两对
            basePoint = threeCards[0];
        }
    } else if (oneCard.isEmpty() && twoCards.size() >= 3 &&
               threeCards.isEmpty() && fourCards.isEmpty()) {
        std::sort(twoCards.begin(), twoCards.end());
        if (twoCards.first() >= Card_3 && twoCards.last() < Card_2 &&
            twoCards.last() - twoCards.first() == (twoCards.size() - 1)) {
            type = Group_Seq_Pair;  // 连对
            basePoint = twoCards[0];
            extraNum = twoCards.size();
        }
    } else if (oneCard.size() >= 5 && twoCards.isEmpty() &&
               threeCards.isEmpty() && fourCards.isEmpty()) {
        std::sort(oneCard.begin(), oneCard.end());
        if (oneCard.first() >= Card_3 && oneCard.last() < Card_2 &&
            oneCard.last() - oneCard.first() == (oneCard.size() - 1)) {
            type = Group_Seq_Single;  // 顺子
            basePoint = oneCard[0];
            extraNum = oneCard.size();
        }
    } else if (oneCard.isEmpty() && twoCards.isEmpty() &&
               threeCards.isEmpty() && fourCards.size() == 1) {
        type = Group_Bomb;
        basePoint = fourCards[0];
    } else if (oneCard.size() == 2 && twoCards.isEmpty() &&
               threeCards.isEmpty() && fourCards.size() == 1) {
        std::sort(oneCard.begin(), oneCard.end());
        if (oneCard[0] != CardPoint::Card_SJ && oneCard[1] != CardPoint::Card_BJ) {
            type = Group_Bomb_Two_Single;  // 炸弹带两单
            basePoint = fourCards[0];
        }
    } else if (oneCard.isEmpty() && twoCards.size() == 2 &&
               threeCards.isEmpty() && fourCards.size() == 1) {
        type = Group_Plane_Two_Pair;   // 炸弹带两对
        basePoint = fourCards[0];
    } else if (oneCard.size() == 2 && twoCards.isEmpty() &&
               threeCards.isEmpty() && fourCards.isEmpty()) {
        std::sort(oneCard.begin(), oneCard.end());
        if (oneCard[0] == CardPoint::Card_SJ && oneCard[1] == CardPoint::Card_BJ) {
            type = Group_Bomb_Jokers;  // 王炸
        }
    }
}

bool CardGroups::canBeat(const CardGroups &cardGroups) const
{
    if (type == Group_Unknown) {
        return false;
    }

    if (type == Group_Bomb_Jokers) {
        return true;
    }

    if (cardGroups.type == Group_Pass) {
        return true;
    }

    if (type == Group_Bomb &&
        cardGroups.type >= Group_Single &&
        cardGroups.type <= Group_Bomb_Two_Pair) {
        return true;
    }

    if (type == cardGroups.type) {
        if (type == Group_Seq_Pair || type == Group_Seq_Single) {
            return (basePoint > cardGroups.basePoint && extraNum == cardGroups.extraNum);
        } else {
            return basePoint > cardGroups.basePoint;
        }
    }

    return false;
}
