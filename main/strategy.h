#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"
#include "card.h"

class Strategy
{
public:
    Strategy(Player* player, const QVector<Card>& cards);

    int countOfPoint(QVector<Card> &cards, CardPoint point);    // 计算牌数量
    QVector<Card> findSamePointCards(CardPoint point, int count);	// 找出count张点数为point的牌
    QVector<QVector<Card>> findCardsByCount(int count);		// 找出所有张数为count的所有牌数组
    QVector<Card> getRangeCards(CardPoint beginPoint, CardPoint endPoint);	// 根据点数范围找牌
    QVector<Card> getFirstSeqSingleRange();		// 找到第一个能构成顺子的牌集合

    // 在cards中挑出一个顺子，seqInherited记录逐步拨除顺子，allSeqRecord记录所能分离出的顺子
    void pickSeqSingles(QVector<QVector<QVector<Card>> >& allSeqRecord, const QVector<QVector<Card>>& seqInherited, QVector<Card> cards);
    QVector<QVector<Card>> pickOptimalSeqSingles();

    // 按牌型找到若干手牌，beat为true表示要大过hand
    QVector<QVector<Card>> findHand(CardGroups hand, bool beat);

    QVector<Card> playFirst();		// 主动出牌
    QVector<Card> playBeatHand(CardGroups hand);		// 大过指定牌型

    bool whetherToBeat(const QVector<Card>& myCards);	// 能大过时，判断是打还是放行

    QVector<Card> makeStragety();
private:
    Player* player;
    QVector<Card> cards;
};

#endif // STRATEGY_H
