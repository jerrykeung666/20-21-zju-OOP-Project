#include "strategy.h"

Strategy::Strategy(Player* player, const QVector<Card>& cards)
{
    this->player = player;
    this->cards = cards;
}

int Strategy::countOfPoint(QVector<Card> cards, CardPoint point)
{
    int count = 0;
    for(int i = 0; i < cards.size(); i++)
        if(cards[i].point == point)
            count++;
    return count;
}

// 按牌型找到若干手牌，beat为true表示要大过hand
QVector<QVector<Card>> Strategy::findHand(CardGroups hand, bool beat)
{
    GroupType handType = hand.getCardsType();
    CardPoint basePoint = CardPoint(hand.getBasePoint());
    int extra = hand.getExtraNum();

    if (handType == Group_Pass)
    {

    }
    else if (handType == Group_Single)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QVector<Card> findCards = findSamePointCards(point, 1);
            if (!findCards.isEmpty())
            {
                findCardsArray.push_back(findCards);
            }
        }
        return findCardsArray;
    }
    else if (handType == Group_Pair)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QVector<Card> findCards = findSamePointCards(point, 2);
            if (!findCards.isEmpty())
            {
                findCardsArray.push_back(findCards);
            }
        }

        return findCardsArray;
    }
    else if (handType == Group_Triple)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QVector<Card> findCards = findSamePointCards(point, 3);
            if (!findCards.isEmpty())
            {
                findCardsArray.push_back(findCards);
            }
        }

        return findCardsArray;
    }
    else if (handType == Group_Triple_Single)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QVector<Card> findCards = findSamePointCards(point, 3);
            if (!findCards.isEmpty())
            {
                findCardsArray.push_back(findCards);
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QVector<Card> remainCards = cards;
            for(int i=0;i<findCardsArray.size();i++)
            {
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne((findCardsArray[i])[j]);
            }
            //remainCards.Remove(findCardsArray);

            Strategy st(player, remainCards);
            QVector<QVector<Card> > oneCardsArray = st.findHand(CardGroups(Group_Single, Card_Begin, 0), false);
            if (!oneCardsArray.isEmpty())
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    findCardsArray[i] << oneCardsArray[0];
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Group_Triple_Pair)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QVector<Card>  findCards = findSamePointCards(point, 3);
            if (!findCards.isEmpty())
            {
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QVector<Card>  remainCards = cards;
            for(int i=0;i<findCardsArray.size();i++)
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne(findCardsArray[i][j]);

            //            remainCards.Remove(findCardsArray);

            Strategy st(player, remainCards);
            QVector<QVector<Card> > pairCardsArray = st.findHand(CardGroups(Group_Pair, Card_Begin, 0), false);
            if (!pairCardsArray.isEmpty())
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    findCardsArray[i].append(pairCardsArray[0]);
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Group_Plane)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            QVector<Card>  prevCards = findSamePointCards(point, 3);
            QVector<Card>  nextCards = findSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.isEmpty() && !nextCards.isEmpty())
            {
                findCardsArray.append(prevCards);
                findCardsArray.append(nextCards);
            }
        }
    }
    else if (handType == Group_Plane_Two_Single)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            QVector<Card>  prevCards = findSamePointCards(point, 3);
            QVector<Card>  nextCards = findSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.isEmpty() && !nextCards.isEmpty())
            {
                QVector<Card>  findCards;

                findCards.append(prevCards);
                findCards.append(nextCards);
                findCardsArray.append(findCards);
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QVector<Card>  remainCards = cards;
            for(int i=0;i<findCardsArray.size();i++)
            {
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne((findCardsArray[i])[j]);
            }

            Strategy st(player, remainCards);
            QVector<QVector<Card> > oneCardsArray = st.findHand(CardGroups(Group_Single, Card_Begin, 0), false);
            if (oneCardsArray.size() >= 2)
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    QVector<Card>  oneCards;
                    oneCards.append(oneCardsArray[0]);
                    oneCards.append(oneCardsArray[1]);
                    findCardsArray[i] << oneCards;
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Group_Plane_Two_Pair)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            QVector<Card>  prevCards = findSamePointCards(point, 3);
            QVector<Card>  nextCards = findSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.isEmpty() && !nextCards.isEmpty())
            {
                QVector<Card> findCards;
                findCards << prevCards << nextCards;
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            QVector<Card>  remainCards = cards;
            for(int i=0;i<findCardsArray.size();i++)
            {
                for(int j=0;j<findCardsArray[i].size();j++)
                    remainCards.removeOne((findCardsArray[i])[j]);
            }

            Strategy st(player, remainCards);
            QVector<QVector<Card> > pairCardsArray = st.findHand(CardGroups(Group_Pair, Card_Begin, 0), false);
            if (pairCardsArray.size() >= 2)
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    QVector<Card>  pairCards;
                    pairCards << pairCardsArray[0] << pairCardsArray[1];
                    findCardsArray[i] << pairCards;
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Group_Seq_Pair)
    {
        if (beat)
        {
            QVector<QVector<Card> > findCardsArray;
            for (CardPoint point = CardPoint(basePoint + 1); point <= Card_Q; point = CardPoint(point + 1))
            {
                bool seqPairFound = true;
                QVector<Card>  seqPair;

                for (int i = 0; i < extra; i++)
                {
                    QVector<Card>  cards = findSamePointCards(CardPoint(point + i), 2);
                    if (cards.isEmpty() || (point + i >= Card_2))	// 连对中断，或顶到2了
                    {
                        seqPairFound = false;
                        seqPair.clear();
                        break;
                    }
                    else
                    {
                        seqPair << cards;
                    }
                }

                if (seqPairFound)
                {
                    findCardsArray << seqPair;
                    return findCardsArray;
                }
            }

            return findCardsArray;
        }
        else
        {
            QVector<QVector<Card>> findCardsArray;

            for (CardPoint point = Card_3; point <= Card_Q; point = CardPoint(point + 1))
            {
                QVector<Card>  cards0 = findSamePointCards(point, 2);
                QVector<Card>  cards1 = findSamePointCards(CardPoint(point + 1), 2);
                QVector<Card>  cards2 = findSamePointCards(CardPoint(point + 2), 2);

                if (cards0.isEmpty() || cards1.isEmpty() || cards2.isEmpty()) continue;

                QVector<Card>  baseSeq;
                baseSeq << cards0 << cards1 << cards2;
                findCardsArray << baseSeq;

                int followed = 3;
                QVector<Card>  alreadyFollowedCards;

                while (true)
                {
                    CardPoint followedPoint = CardPoint(point + followed);
                    if (followedPoint >= Card_2)
                    {
                        break;
                    }

                    QVector<Card>  followedCards = findSamePointCards(followedPoint, 2);
                    if (followedCards.isEmpty())
                    {
                        break;
                    }
                    else
                    {
                        alreadyFollowedCards << followedCards;
                        QVector<Card>  newSeq = baseSeq;
                        newSeq << alreadyFollowedCards;

                        findCardsArray << newSeq;
                        followed++;
                    }
                }
            }

            return findCardsArray;
        }
    }
    else if (handType == Group_Seq_Single)
    {
        if (beat)
        {
            QVector<QVector<Card> > findCardsArray;
            for (CardPoint point = CardPoint(basePoint + 1); point <= Card_10; point = CardPoint(point + 1))
            {
                bool seqSingleFound = true;
                QVector<Card>  seqSingle;

                for (int i = 0; i < extra; i++)
                {
                    QVector<Card>  cards = findSamePointCards(CardPoint(point + i), 1);
                    if (cards.isEmpty() || (point + extra >= Card_2))
                    {
                        seqSingleFound = false;
                        seqSingle.clear();
                        break;
                    }
                    else
                    {
                        for (auto &card : cards)
                            seqSingle.push_back(card);
                    }
                }

                if (seqSingleFound)
                {
                    findCardsArray.push_back(seqSingle);
                    return findCardsArray;
                }
            }
        }
        else
        {
            QVector<QVector<Card> > findCardsArray;

            for (CardPoint point = Card_3; point <= Card_10; point = CardPoint(point + 1))
            {
                QVector<Card>  cards0 = findSamePointCards(point, 1);
                QVector<Card>  cards1 = findSamePointCards(CardPoint(point + 1), 1);
                QVector<Card>  cards2 = findSamePointCards(CardPoint(point + 2), 1);
                QVector<Card>  cards3 = findSamePointCards(CardPoint(point + 3), 1);
                QVector<Card>  cards4 = findSamePointCards(CardPoint(point + 4), 1);

                if (cards0.isEmpty() || cards1.isEmpty() || cards2.isEmpty()
                        || cards3.isEmpty() || cards4.isEmpty())
                {
                    continue;
                }

                QVector<Card>  baseSeq;
                baseSeq << cards0 << cards1 << cards2 << cards3 << cards4;
                findCardsArray << baseSeq;

                int followed = 5;
                QVector<Card>  alreadyFollowedCards;

                while (true)
                {
                    CardPoint followedPoint = CardPoint(point + followed);
                    if (followedPoint >= Card_2)
                    {
                        break;
                    }

                    QVector<Card>  followedCards = findSamePointCards(followedPoint, 1);
                    if (followedCards.isEmpty())
                    {
                        break;
                    }
                    else
                    {
                        alreadyFollowedCards << followedCards;
                        QVector<Card>  newSeq = baseSeq;
                        newSeq << alreadyFollowedCards;

                        findCardsArray << newSeq;
                        followed++;
                    }
                }
            }

            return findCardsArray;
        }
    }
    else if (handType == Group_Bomb)
    {
        QVector<QVector<Card> > findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            QVector<Card>  findCards = findSamePointCards(point, 4);
            if (!findCards.isEmpty())
            {
                findCardsArray.push_back(findCards);
            }
        }

        return findCardsArray;
    }

    return QVector<QVector<Card> >();
}

QVector<Card> Strategy::findSamePointCards(CardPoint point, int count)
{
    if (point == Card_SJ || point == Card_BJ) {
        if (count > 1) return QVector<Card>();

        Card oneCard;
        oneCard.point = point;
        oneCard.suit = Suit_Begin;
        if (cards.contains(oneCard)) {
            QVector<Card> cards;
            cards.push_back(oneCard);
            return cards;
        }

        return QVector<Card>();
    }

    QVector<Card> findCards;
    int findCount = 0;
    for (int suit = Suit_Begin + 1; suit < Suit_End; suit++) {
        Card oneCard;
        oneCard.point = point;
        oneCard.suit = (CardSuit)suit;

        if (cards.contains(oneCard)) {
            findCount++;
            findCards.push_back(oneCard);

            if (findCount == count) {
                return findCards;
            }
        }
    }

    return QVector<Card>();
}

QVector<QVector<Card>> Strategy::findCardsByCount(int count)
{
    QVector<QVector<Card> > cardsList;
    if (count < 1 || count > 4) return cardsList;   //count不合理

    for(int point = Card_3; point < Card_End; point++)
    {
        if(countOfPoint(cards, (CardPoint)point)==count)
        {
            QVector<Card> cards = findSamePointCards((CardPoint)point, count);
            cardsList.push_back(cards);

        }
    }
    return cardsList;
}

QVector<Card> Strategy::getRangeCards(CardPoint beginPoint, CardPoint endPoint)
{
    QVector<Card> rangeCards;

    for (CardPoint point = beginPoint; point <= endPoint; point=(CardPoint)(point+1))
    {
        int count = countOfPoint(cards, point);
        if(count != 0)
        {
            QVector<Card> cards = findSamePointCards(point, count);
            for (auto &card : cards)
                rangeCards.push_back(card);
        }
    }

    return rangeCards;
}

QVector<Card> Strategy::getFirstSeqSingleRange()
{
    int seqCount = 0;
    CardPoint beginPoint = Card_Begin, endPoint = Card_Begin;

    for(CardPoint point = Card_3; point <= Card_10; point = (CardPoint)(point+1))
    {
        while(true)
        {
            CardPoint findPoint = CardPoint(point+seqCount);
            QVector<Card> oneCard = findSamePointCards(findPoint, 1);
            if(oneCard.isEmpty() || findPoint>Card_A)
            {
                if(seqCount>=5)
                {
                    endPoint = CardPoint(point+seqCount-1);
                    return getRangeCards(point, endPoint);
                }
                point = findPoint;
                beginPoint = endPoint = Card_Begin;
                seqCount = 0;
                break;
            }
            else
            {
                if (seqCount == 0)
                {
                    beginPoint = point;
                }

                seqCount++;
            }
        }
    }
    return QVector<Card>();
}

// 在cards中挑出一个顺子，seqInherited记录逐步拨除顺子，allSeqRecord记录所能分离出的顺子
void Strategy::pickSeqSingles(QVector<QVector<QVector<Card>> >& allSeqRecord, const QVector<QVector<Card>>& seqInherited, QVector<Card> cards)
{
    QVector<QVector<Card> > allSeqScheme = Strategy(player, cards).findHand(CardGroups(Group_Seq_Single, Card_Begin, 0), false);
    if (allSeqScheme.isEmpty())
    {
        allSeqRecord << seqInherited;
    }
    else
    {
        QVector<Card> savedCards = cards;
        for (int i = 0; i < allSeqScheme.size(); i++)
        {
            QVector<Card> aScheme = allSeqScheme[i];
            QVector<Card> leftCards = savedCards;

            for(int j=0;j<aScheme.size();j++)
                leftCards.removeOne(aScheme[j]);

            QVector<QVector<Card> > seqArray = seqInherited;
            seqArray.append(aScheme);
            pickSeqSingles(allSeqRecord, seqArray, leftCards);
        }
    }
}

QVector<QVector<Card>> Strategy::pickOptimalSeqSingles()
{
    QVector<QVector<QVector<Card> > > seqRecord;
    QVector<QVector<Card> > seqInherited;
    Strategy(player, cards).pickSeqSingles(seqRecord, seqInherited, cards);
    if (seqRecord.isEmpty())
    {
        return QVector<QVector<Card> >();
    }

    QMap<int, int> seqMarks;
    for (int i = 0; i < seqRecord.size(); i++)
    {
        QVector<Card> backupCards = cards;
        QVector<QVector<Card> > seqArray = seqRecord[i];
        for(int l=0;l<seqArray.size();l++)
        {
            for(int j=0;j<seqArray[l].size();j++)
            {
                backupCards.removeOne(seqArray[l][j]);
            }
        }

        QVector<QVector<Card> > singleArray = Strategy(player, backupCards).findCardsByCount(1);

        QVector<Card> cardList;
        for (int j = 0; j < singleArray.size(); j++)
        {
            for(int i=0;i<singleArray[j].size();i++)
                cardList<<singleArray[j][i];

        }

        int mark = 0;
        for (int j = 0; j < cardList.size(); j++)
        {
            mark += cardList[j].point + 15;
        }
        seqMarks.insert(i, mark);
    }

    int index = 0;
    int compMark = 1000000;
    QMap<int, int>::ConstIterator it = seqMarks.constBegin();
    for (; it != seqMarks.constEnd(); it++)
    {
        if (it.value() < compMark)
        {
            compMark = it.value();
            index = it.key();
        }
    }

    return seqRecord[index];
}

QVector<Card> Strategy::playFirst()
{
    CardGroups hand(cards);
    if (hand.getCardsType() != Group_Unknown)		// 只剩一手牌，直接出完
    {
        return cards;
    }


    QVector<Card>  seqSingleRange = getFirstSeqSingleRange();
    if (!seqSingleRange.isEmpty())
    {
        QVector<Card>  left = seqSingleRange;

        //清除炸弹和三个
        QVector<QVector<Card> > cards4=Strategy(player,left).findCardsByCount(4);

        for(int i=0;i<cards4.size();i++)
            for(int j=0;j<cards4[i].size();j++)
                left.removeOne(cards4[i][j]);

        QVector<QVector<Card> > cards3=Strategy(player,left).findCardsByCount(3);

        for(int i=0;i<cards3.size();i++)
            for(int j=0;j<cards3[i].size();j++)
                left.removeOne(cards3[i][j]);

        //     left.Remove(Stragety(player, left).FindCardsByCount(4));
        //     left.Remove(Strategy(player, left).FindCardsByCount(3));



        QVector<QVector<Card> > optimalSeq = Strategy(player, left).pickOptimalSeqSingles();
        if (!optimalSeq.isEmpty())
        {
            int oriSingleCount = Strategy(player, left).findCardsByCount(1).size();
            //left.Remove(optimalSeq);

            for(int i=0;i<optimalSeq.size();i++)
                for(int j=0;j<optimalSeq[i].size();j++)
                    left.removeOne(optimalSeq[i][j]);

            int leftSingleCount = Strategy(player, left).findCardsByCount(1).size();

            if (leftSingleCount < oriSingleCount)
            {
                return optimalSeq[0];
            }
        }
    }

    bool hasPlane, hasTriple, hasSeqPair;
    hasPlane = hasTriple = hasSeqPair = false;
    QVector<Card>  leftCards = cards;

    QVector<QVector<Card> > bombArray = Strategy(player, leftCards).findHand(CardGroups(Group_Bomb, Card_Begin, 0), false);
    //leftCards.Remove(bombArray);

    for(int i=0;i<bombArray.size();i++)
        for(int j=0;j<bombArray[i].size();j++)
            leftCards.removeOne(bombArray[i][j]);

    QVector<QVector<Card> > planeArray = Strategy(player, leftCards).findHand(CardGroups(Group_Plane, Card_Begin, 0), false);
    if (!planeArray.isEmpty())
    {
        hasPlane = true;
        for(int i=0;i<planeArray.size();i++)
            for(int j=0;j<planeArray[i].size();j++)
                leftCards.removeOne(planeArray[i][j]);

        //leftCards.Remove(planeArray);
    }

    QVector<QVector<Card> > tripleArray = Strategy(player, leftCards).findHand(CardGroups(Group_Triple, Card_Begin, 0), false);
    if (!tripleArray.isEmpty())
    {
        hasTriple = true;
        for(int i=0;i<tripleArray.size();i++)
            for(int j=0;j<tripleArray[i].size();j++)
                leftCards.removeOne(tripleArray[i][j]);

        //        leftCards.Remove(tripleArray);
    }

    QVector<QVector<Card> > seqPairArray = Strategy(player, leftCards).findHand(CardGroups(Group_Seq_Pair, Card_Begin, 0), false);
    if (!seqPairArray.isEmpty())
    {
        hasSeqPair = true;
        for(int i=0;i<seqPairArray.size();i++)
            for(int j=0;j<seqPairArray[i].size();j++)
                leftCards.removeOne(seqPairArray[i][j]);
        //leftCards.Remove(seqPairArray);
    }

    if (hasPlane)
    {
        bool twoPairFound = false;
        QVector<QVector<Card> > pairArray;
        for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
        {
            QVector<Card>  pair = Strategy(player, leftCards).findSamePointCards(point, 2);
            if (!pair.isEmpty())
            {
                pairArray << pair;
                if (pairArray.size() == 2)
                {
                    twoPairFound = true;
                    break;
                }
            }
        }

        if (twoPairFound)
        {
            QVector<Card>  playCards = planeArray[0];
            for(int i=0;i<pairArray.size();i++)
                for(int j=0;j<pairArray[i].size();j++)
                    playCards.append(pairArray[i][j]);
            //            playCards.Add(pairArray);

            return playCards;
        }
        else
        {
            bool twoSingleFound = false;
            QVector<QVector<Card> > singleArray;
            for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
            {
                if (countOfPoint(leftCards,point)==1) //(leftCards.PointCount(point) == 1)
                {
                    QVector<Card>  single = Strategy(player, leftCards).findSamePointCards(point, 1);
                    if (!single.isEmpty())
                    {
                        singleArray << single;
                        if (singleArray.size() == 2)
                        {
                            twoSingleFound = true;
                            break;
                        }
                    }
                }
            }

            if (twoSingleFound)
            {
                QVector<Card>  playCards = planeArray[0];
                for(int i=0;i<singleArray.size();i++)
                    for(int j=0;j<singleArray[i].size();j++)
                        playCards.append(singleArray[i][j]);
                // playCards.Add(singleArray);

                return playCards;
            }
            else
            {
                return planeArray[0];
            }
        }
    }

    if (hasTriple)
    {
        if (CardGroups(tripleArray[0]).getBasePoint() < Card_A)
        {
            for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
            {
                int pointCount = countOfPoint(leftCards,point);//leftCards.PointCount(point);
                if (pointCount == 1)
                {
                    QVector<Card>  single = Strategy(player, leftCards).findSamePointCards(point, 1);
                    if (!single.isEmpty())
                    {
                        QVector<Card>  playCards = tripleArray[0];
                        //playCards.Add(single);

                        for(int i=0;i<single.size();i++)
                            playCards.append(single[i]);

                        return playCards;
                    }
                }
                else if (pointCount == 2)
                {
                    QVector<Card>  pair = Strategy(player, leftCards).findSamePointCards(point, 2);
                    if (!pair.isEmpty())
                    {
                        QVector<Card>  playCards = tripleArray[0];
                        //                        playCards.Add(pair);

                        for(int i=0;i<pair.size();i++)
                            playCards.append(pair[i]);
                        return playCards;
                    }
                }

            }

            return tripleArray[0];		// 找不到合适的带牌，直接出3个
        }
    }

    if (hasSeqPair)		// 打出最长的连对
    {
        QVector<Card>  maxSeqPair;
        for (int i = 0; i < seqPairArray.size(); i++)
        {
            if (seqPairArray[i].size() > maxSeqPair.size())
            {
                maxSeqPair = seqPairArray[i];
            }
        }

        return maxSeqPair;
    }

    Player* nextPlayer = player->getNextPlayer();

    if (player->getIsLandLord() != nextPlayer->getIsLandLord() &&
            nextPlayer->getHandCards().size() == 1)
    {
        for (CardPoint point = CardPoint(Card_End - 1); point >= Card_3; point = CardPoint(point - 1))
        {
            int pointCount = countOfPoint(leftCards,point);//leftCards.PointCount(point);
            if (pointCount == 1)
            {
                QVector<Card>  single = Strategy(player, leftCards).findSamePointCards(point, 1);
                return single;
            }
            else if (pointCount == 2)
            {
                QVector<Card>  pair = Strategy(player, leftCards).findSamePointCards(point, 2);
                return pair;
            }
        }
    }
    else
    {
        for (CardPoint point = Card_3; point < Card_End; point = CardPoint(point + 1))
        {
            int pointCount = countOfPoint(leftCards,point);//leftCards.PointCount(point);
            if (pointCount == 1)
            {
                QVector<Card>  single = Strategy(player, leftCards).findSamePointCards(point, 1);
                return single;
            }
            else if (pointCount == 2)
            {
                QVector<Card>  pair = Strategy(player, leftCards).findSamePointCards(point, 2);
                return pair;
            }
        }
    }

    return QVector<Card> ();
}

QVector<Card> Strategy::playBeatHand(CardGroups hand)
{
    return QVector<Card>();
}

bool Strategy::whetherToBeat(const QVector<Card>& myCards)
{
    return true;
}
