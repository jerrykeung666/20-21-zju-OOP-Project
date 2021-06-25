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
    void insertCardWidget(const Card &card, QString &path);
    void addLandLordCard(const Card &card);
    void showLandLordCard();
    void showMyCard(Player* myPlayer);
    void showOtherPlayerCard(Player* otherPlayer, const QString status);
    void showRemLandLordCard(QString status);
    void call4Landlord();
    void cardSelected(Qt::MouseButton mouseButton);

signals:

public slots:
    void onStartBtnClicked();
    void onBetNoBtnClicked();
    void onBet1BtnClicked();
    void onBet2BtnClicked();
    void onBet3BtnClicked();

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

    MyPushButton* startBtn;
    MyPushButton* betNoBtn;
    MyPushButton* bet1Btn;
    MyPushButton* bet2Btn;
    MyPushButton* bet3Btn;

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
    static const QPoint myBetInfo;
    static const QPoint leftPlayerBetInfo;
    static const QPoint rightPlayerBetInfo;
};

#endif // GAMEWINDOW_H
