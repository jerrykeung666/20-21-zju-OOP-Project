#ifndef CARDGROUPS_H
#define CARDGROUPS_H

#include <QObject>
#include <QVector>
#include "card.h"

//出牌类型
enum GroupType
{
    Group_Unknown,			// 未知
    Group_Pass,				// 过
    Group_Single,			// 单
    Group_Pair,				// 对
    Group_Triple,			// 三个
    Group_Triple_Single,	// 三带一
    Group_Triple_Pair,		// 三带二
    Group_Plane,			// 飞机，555_666
    Group_Plane_Two_Single,	// 飞机带两单，555_666_3_4
    Group_Plane_Two_Pair,	// 飞机带两双，555_666_33_44
    Group_Seq_Single,		// 顺子，34567(8...)
    Group_Seq_Pair,			// 连对，33_44_55(_66...)
    Group_Bomb,				// 炸弹
    Group_Bomb_Jokers,		// 王炸
};


class CardGroups
{
public:
    CardGroups() {}
    CardGroups(const QVector<Card>& cards);
    CardGroups(GroupType type, CardPoint base, int extra);

    void setCards(const QVector<Card>&cards);   // 设置牌
    QVector<Card> getCards() const;

    void analyseCards();    // 对牌进行分析
    bool canBeat(const CardGroups &cardGroups);   // 判断牌能否打过

    int getCardsNum();
    GroupType getCardsType();
    CardPoint getBasePoint();
    int getExtraNum();



private:
    QVector<Card> cards;
    GroupType type = Group_Unknown;   // 牌型
    CardPoint basePoint = CardPoint::Card_Begin;  // 基本点数
    int extraNum = 0;  // 顺子用的
};

#endif // CARDGROUPS_H
