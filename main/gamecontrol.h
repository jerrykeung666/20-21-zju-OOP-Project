#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "player.h"
#include <QTimer>
#include <QVector>
#include "user.h"
#include "robot.h"


class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(QObject *parent = 0);

public:
    Player* getCurrentPlayer();
    User* getPlayerA();
    Robot* getPlayerB();
    Robot* getPlayerC();
    CardGroups getCurrentCombo();
    Player* getEffectivePlayer();
    QVector<Card> getLandLordCards();

    void updateBetPoints(int bet); //处理叫地主分数

    void initCards(); //发牌

    void init(); //初始化玩家

    void setgamemodel(int gamemodel);
    int getgamemodel();

private:
    void initAllCards();
    QVector<Card> getRandomCards(int start, int cardnum);



signals:
    void callGamewindowShowCards();   //发牌结束后通知gamewindow显示卡牌
    void callGamewindowShowBets(Player* player);    //叫分结束后通知gamewindow显示叫分

    void callGamewindowShowLandlord(); //处理叫分后通知gamewindow

    void NotifyPlayerPlayHand(Player* player,CardGroups &cards);
    void NotifyPlayerbutton(Player* player);
    void NotifyPlayerStatus(Player* player);

public slots:
    void onPlayerHand(Player* player, CardGroups &cards); //处理叫地主分数
    void onPlayerHandRobot(Player* player); //处理叫地主分数
   // void updateBetPoints(int bet); //处理叫地主分数
    //void handout(int bet); //处理出牌

protected:
    struct BetRecord
    {
        Player* player;
        int bet;
    };

protected:
    Player* currentPlayer;   //当前玩家
    User* playerA;
    Robot* playerB;
    Robot* playerC;            //参与者A、B、C
    CardGroups currentCombo; //有效牌
    Player* effectivePlayer; //有效玩家
    QVector<Card> landLordCards;//三张地主牌

    Player* punchPlayer;
    QVector<Card> punchCards;

    int betCalledNum;         //地主优势叫分
    QVector<BetRecord> betList;

    QVector<Card> allCards;

    int gamemodel;
};

#endif // GAMECONTROL_H
