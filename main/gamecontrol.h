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
    Player* GetCurrentPlayer();
    Player* GetPlayerA();
    Player* GetPlayerB();
    Player* GetPlayerC();
    CardGroups GetCurrentCombo();
    Player* GetEffectivePlayer();
    CardGroups* GetLandlordCards();

    void initCards(); //发牌

    void Init(); //初始化玩家



signals:
    void CallGamewindowShowCards();   //发牌结束后通知gamewindow显示卡牌
    void CallGamewindowShowButtons(); //处理叫分后通知gamewindow

public slots:
    void updateBetPoints(); //处理叫地主分数

protected:
    struct BetRecord
    {
        Player* player;
        int bet;
    };

protected:
    Player* current_player;   //当前玩家
    Player* playerA;
    Player* playerB;
    Player* playerC;            //参与者A、B、C
    CardGroups current_combo; //有效牌
    Player* effective_player; //有效玩家
    CardGroups landlordCards;//三张地主牌

    int betCalledNum;         //地主优势叫分
    QVector<BetRecord> betlist;

};

#endif // GAMECONTROL_H
