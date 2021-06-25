#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector>
#include <QDebug>

#include "card.h"
#include "cardgroups.h"


class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void setPlayerID(int ID);
    int getPlayerID() const;

    void setHandCards(const QVector<Card> &cards);
    QVector<Card> getHandCards() const;

    void setSelectCards(const QVector<Card> &cards);
    QVector<Card> getSelectCards() const;

    void setBetPoints(int bet);
    int getBetPoints() const;

    void setIsLandLord(bool isLandLord);
    bool getIsLandLord();

    void setIsPerson(bool isPerson);
    bool getIsPerson();

    void setNextPlayer(Player *next);
    Player* getNextPlayer();

    int getCardsNumber() const;   // 得到当前牌的数量
    void addLandLordCards(const QVector<Card> &cards); // 添加地主牌
    bool isWin();  // 是否赢
    bool checkCardValid(CardGroups &currentCombo);


    void showCards();
    void clear();

protected:
    void sortHandCards();     // 默认升序，先按点数，点数相同则按花色排序

protected:
    bool isLandLord = false;  // 玩家是否为地主
    bool isPerson = false;    // 玩家是人还是机器人
    int betPoints = 0;        // 玩家叫的分
    int playerID;             // 玩家序号
    QVector<Card> handCards;  // 玩家手上的牌
    CardGroups selectCards;   // 选中的牌
    Player *nextPlayer;       // 下一个玩家
};

#endif // PLAYER_H
