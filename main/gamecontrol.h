#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "player.h"
#include <QTimer>
#include <QVector>

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(QObject *parent = 0);

public:
    Player* getCurrentPlayer();
    Player* getPlayerA();
    Player* getPlayerB();
    Player* getPlayerC();
    CardGroups getCurrentCombo();
    Player* getEffectivePlayer();
    QVector<Card> getLandLordCards();

    void initCards(); //发牌

    void init(); //初始化玩家

private:
    void initAllCards();
    QVector<Card> getRandomCards(int start, int cardnum);



signals:
    void callGamewindowShowCards();   //发牌结束后通知gamewindow显示卡牌
    void callGamewindowShowButtons(); //处理叫分后通知gamewindow

public slots:
    void updateBetPoints(int bet); //处理叫地主分数
    //void handout(int bet); //处理出牌

protected:
    struct BetRecord
    {
        Player* player;
        int bet;
    };

protected:
    Player* currentPlayer;   //当前玩家
    Player* playerA;
    Player* playerB;
    Player* playerC;            //参与者A、B、C
    CardGroups currentCombo; //有效牌
    Player* effectivePlayer; //有效玩家
    QVector<Card> landLordCards;//三张地主牌

    int betCalledNum;         //地主优势叫分
    QVector<BetRecord> betList;

    QVector<Card> allCards;

};

#endif // GAMECONTROL_H
