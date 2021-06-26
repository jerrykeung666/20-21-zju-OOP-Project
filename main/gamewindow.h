#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPalette>
#include "mypushbutton.h"
#include "gamecontrol.h"
#include "card.h"
#include "cardwidget.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

//    void HidePlayerLastCards(Player* player);
    void UpdatePlayerCards(Player* player);


private:
    virtual void paintEvent(QPaintEvent *);
//    virtual void resizeEvent(QResizeEvent* event);
    void initCardWidgetMap();
    void initButtons();
    void initPlayerContext();
    void initLandLordCards();
    void initInfoLabel();
    void initSignalsAndSlots();
    void insertCardWidget(const Card &card, QString &path);
    void addLandLordCard(const Card &card);
    void showLandLordCard();
    void showMyCard(Player* myPlayer);
    void showOtherPlayerCard(Player* otherPlayer, const QString status);
    void showRemLandLordCard(QString status);
    void call4Landlord();
    void showMySelectedCard(Player* player);
    void startGame();
    void showPlayCard();
    void showOtherPlayerPlayCard(Player* otherPlayer, CardGroups cards, const QString status);

signals:

public slots:
    void onStartBtnClicked();
    void onBetNoBtnClicked();
    void onBet1BtnClicked();
    void onBet2BtnClicked();
    void onBet3BtnClicked();
    void onBetPointsCall(Player* player);
    void cardSelected(Qt::MouseButton mouseButton);
    void playCards();
    void passCards();
    void otherPlayerShowCards(Player* player, CardGroups cards);
    void myPlayerShowButton(Player* player);
    void showEndStatus(Player* player);

protected:
    enum CardsAlign
    {
        Horizontal,
        Vertical
    };

    struct PlayerContext
    {
        QRect cardsRect;
        QRect playHandRect;
        CardsAlign cardsAlign;
        bool isFrontSide;
        QVector<Card> lastCards;
        QLabel* info;
        QLabel* rolePic;
    };

private:
    GameControl *gameControl;
    QPixmap cardBack;  // 背面图像
    QMap<Card, CardWidget*> cardWidgetMap;
    QVector<CardWidget*> restThreeCards;
    QMap<Player*, PlayerContext> playerContextMap;
    QPoint baseCardPos;
    QFrame* userTool;
    QSize cardSize;

    QLabel* myBetInfo;
    QLabel* leftBetInfo;
    QLabel* rightBetInfo;
    QLabel* passInfo;
    QLabel* playInfo;
    QLabel* rightPassInfo;
    QLabel* leftPassInfo;
    QLabel* myStatusInfo;
    QLabel* leftStatusInfo;
    QLabel* rightStatusInfo;

    MyPushButton* startBtn;
    MyPushButton* betNoBtn;
    MyPushButton* bet1Btn;
    MyPushButton* bet2Btn;
    MyPushButton* bet3Btn;
    MyPushButton* passBtn;
    MyPushButton* playBtn;

    static const QSize gameWindowSize;

    static const int cardWidthSpace;
    static const int cardHeightSpace;
    static const int cardRemSpace;

    static const int myCardWidthStartPos;
    static const int myCardHeightStartPos;
    static const int leftCardWidthStartPos;
    static const int leftCardHeightStartPos;
    static const int rightCardWidthStartPos;
    static const int rightCardHeightStartPos;
    static const int remCardWidthStartPos;
    static const int remCardHeightStartPos;

    // button param
    static const int betBtnWidthStartPos;
    static const int betBtnHeightStartPos;
    static const int betBtnWidthSpace;

    // bet info
    static const int fontSize;
    static const QPoint myBetInfoPos;
    static const QPoint leftPlayerBetInfoPos;
    static const QPoint rightPlayerBetInfoPos;

    static const int cardSelectedShift;

    // play info
    static const QPoint passBtnStartPos;
    static const QPoint playBtnStartPos;
    static const QPoint myCardZone;
    static const int myCardZoneWidthSpace;
    static const QPoint rightCardZone;
    static const int rightCardZoneHeightSpace;
    static const QPoint leftCardZone;
    static const int leftCardZoneHeightSpace;

    // status info
    static const QPoint myStatusPos;
    static const QPoint leftStatusPos;
    static const QPoint rightStatusPos;
};

#endif // GAMEWINDOW_H
