#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
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

signals:

public slots:
    void onStartBtnClicked();

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

    static const int cardSpace;
};

#endif // GAMEWINDOW_H
