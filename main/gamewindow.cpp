#include "gamewindow.h"

#include <QPainter>
#include <QDebug>

const QSize GameWindow::gameWindowSize = QSize(1200, 800);

const int GameWindow::cardWidthSpace = 35;
const int GameWindow::cardHeightSpace = 20; //TODO
const int GameWindow::cardRemSpace = 180; //TODO

const int GameWindow::myCardWidthStartPos = 250; //TODO
const int GameWindow::myCardHeightStartPos = 650; //TODO
const int GameWindow::leftCardWidthStartPos = 10; //TODO
const int GameWindow::leftCardHeightStartPos = 100; //TODO
const int GameWindow::rightCardWidthStartPos = 1075; //TODO
const int GameWindow::rightCardHeightStartPos = 100; //TODO
const int GameWindow::remCardWidthStartPos = 350;//TODO
const int GameWindow::remCardHeightStartPos = 20;//TODO

const int GameWindow::betBtnWidthStartPos = 320; //TODO
const int GameWindow::betBtnHeightStartPos = 600; //TODO
const int GameWindow::betBtnWidthSpace = 140; //TODO


GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{

    setFixedSize(gameWindowSize);
    setWindowTitle("Landlord: Welcome!");
    setWindowIcon(QIcon("../picture/icon.jfif"));

    gameControl = new GameControl(this);
    gameControl->init();
    gameControl->initCards();

    cardSize = QSize(80, 105);
    initCardWidgetMap();
    initButtons();
    initPlayerContext();
    initLandLordCards();


    qDebug() << "初始化牌";
}

void GameWindow::insertCardWidget(const Card &card, QString &path)
{
    CardWidget *cardWidget = new CardWidget(this);
    QPixmap pix = QPixmap(path);
    cardWidget->hide();
    cardWidget->setCard(card);
    cardWidget->setPix(pix);
    cardWidgetMap.insert(card, cardWidget);
}

void GameWindow::addLandLordCard(const Card &card)
{
    CardWidget *cw = cardWidgetMap[card];

    CardWidget *cardWidget = new CardWidget(this);
    QPixmap pix = QPixmap(cw->getPix());
    cardWidget->hide();
    cardWidget->setCard(card);
    cardWidget->setPix(pix);
    restThreeCards.push_back(cardWidget);
}

/*
void GameWindow::initCardWidgetMap()
{
    QString prefix = ":/PokerImage/";
    QString suitMap[] = {"poker_t_1_v_", "poker_t_2_v_", "poker_t_3_v_", "poker_t_4_v_"};
    for (int st = Suit_Begin + 1; st < Suit_End; ++st) {
        for (int pt = Card_Begin + 1; pt < Card_SJ; ++pt) {
            Card card((CardPoint)pt, (CardSuit)st);
            QString cardPath = prefix + suitMap[st-1] + QString((pt-1)%13) + ".png";
            insertCardWidget(card, cardPath);
        }
    }

    Card card;
    QString cardPath;

    cardPath = prefix + "smalljoker.png";
    card.point = Card_SJ;
    insertCardWidget(card, cardPath);

    card.point = Card_BJ;
    cardPath = prefix + "bigjoker.png";
    insertCardWidget(card, cardPath);
}
*/

// JW version
void GameWindow::initCardWidgetMap()
{
    QString prefix = ":/PokerImage/";
    QString suitMap[] = {"poker_t_1_v_", "poker_t_2_v_", "poker_t_3_v_", "poker_t_4_v_"};
    for (int st = Suit_Begin + 1; st < Suit_End; ++st) {
        for (int pt = Card_Begin + 1; pt < Card_SJ; ++pt) {
            Card card((CardPoint)pt, (CardSuit)st);
            QString cardPath;
            if(pt == 13)
                cardPath = prefix + suitMap[st-1] + QString::number(1) + ".png";
            else
                cardPath = prefix + suitMap[st-1] + QString::number((pt+1)%14) + ".png";
            insertCardWidget(card, cardPath);
        }
    }

    Card card;
    QString cardPath;

    cardPath = prefix + "smalljoker.png";
    card.point = Card_SJ;
    insertCardWidget(card, cardPath);

    card.point = Card_BJ;
    cardPath = prefix + "bigjoker.png";
    insertCardWidget(card, cardPath);
}

void GameWindow::initButtons()
{
    startBtn = new MyPushButton("../picture/game_start.png", "开始游戏");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.5);
    connect(startBtn, &MyPushButton::clicked, this, &GameWindow::onStartBtnClicked);
}

void GameWindow::initPlayerContext()
{
    PlayerContext context;

    context.cardsAlign = Vertical;
    context.isFrontSide = false;
    playerContextMap.insert(gameControl->getPlayerC(), context);

    context.cardsAlign = Vertical;
    context.isFrontSide = false;
    playerContextMap.insert(gameControl->getPlayerB(), context);

    context.cardsAlign = Horizontal;
    context.isFrontSide = true;
    playerContextMap.insert(gameControl->getPlayerA(), context);

    for (auto &pcm : playerContextMap)
    {
        pcm.info = new QLabel(this);
        pcm.info->resize(100, 50);
        pcm.info->setObjectName("info");
        pcm.info->hide();
        pcm.rolePic = new QLabel(this);
        pcm.rolePic->resize(84, 120);
        pcm.rolePic->hide();
    }
}

void GameWindow::initLandLordCards()
{
    QVector<Card> cards = gameControl->getLandLordCards();
    for (auto &card : cards) {
        addLandLordCard(card);
    }
}

void GameWindow::onStartBtnClicked()
{
    startBtn->hide();
    showLandLordCard();
    call4Landlord();

    qDebug() << "开始游戏";
}

void GameWindow::showLandLordCard(){
   // gameControl->getPlayerA();
    if(gameControl->getPlayerA()->getIsPerson()){
        showMyCard(gameControl->getPlayerA());
        showOtherPlayerCard(gameControl->getPlayerB(), "right");
        showOtherPlayerCard(gameControl->getPlayerC(), "left");
    }
    else if(gameControl->getPlayerB()->getIsPerson()){
        showMyCard(gameControl->getPlayerB());
        showOtherPlayerCard(gameControl->getPlayerC(), "right");
        showOtherPlayerCard(gameControl->getPlayerA(), "left");
    }
    else if(gameControl->getPlayerC()->getIsPerson()){
        showMyCard(gameControl->getPlayerC());
        showOtherPlayerCard(gameControl->getPlayerA(), "right");
        showOtherPlayerCard(gameControl->getPlayerB(), "left");
    }

    showRemLandLordCard();
}

void GameWindow::showOtherPlayerCard(Player* otherPlayer, const QString status){
    QVector<Card> myCards;
    QVector<CardWidget*> myWidget;
    myCards = otherPlayer->getHandCards();
    //qDebug() << myCards.size();
    for (int i=0; i < myCards.size(); i++) {
        myWidget.push_back(cardWidgetMap[myCards.at(i)]);
        myWidget.at(i)->raise();
        if(status == "left"){
            myWidget.at(i)->setFront(false);
            myWidget.at(i)->move(leftCardWidthStartPos, leftCardHeightStartPos + i*cardHeightSpace);
        }
        else{
            myWidget.at(i)->setFront(false);
            myWidget.at(i)->move(rightCardWidthStartPos, rightCardHeightStartPos + i*cardHeightSpace);
        }
        myWidget.at(i)->show();
        qDebug() << myWidget.at(i)->getIsFront();
        qDebug() << myWidget.size();
    }
}

void GameWindow::showMyCard(Player* myPlayer){
    QVector<Card> myCards;
    QVector<CardWidget*> myWidget;
    myCards = myPlayer->getHandCards();
    //qDebug() << myCards.size();
    for (int i=0; i < myCards.size(); i++) {
        myWidget.push_back(cardWidgetMap[myCards.at(i)]);
        myWidget.at(i)->raise();
        myWidget.at(i)->move(myCardWidthStartPos + i*cardWidthSpace, myCardHeightStartPos);
        myWidget.at(i)->show();
        qDebug() << myWidget.at(i)->getIsFront();
        qDebug() << myWidget.size();
    }
}

void GameWindow::showRemLandLordCard(){
    QVector<Card> remCards;
    QVector<CardWidget*> remWidget;
    remCards = gameControl->getLandLordCards();
    for (int i=0; i < remCards.size(); i++) {
        remWidget.push_back(cardWidgetMap[remCards.at(i)]);
        remWidget.at(i)->raise();
        remWidget.at(i)->setFront(false);
        remWidget.at(i)->move(remCardWidthStartPos + i*cardRemSpace, remCardHeightStartPos);
        remWidget.at(i)->show();
    }
}

void GameWindow::call4Landlord(){
    MyPushButton* betNoBtn = new MyPushButton("../picture/No.png", "No!");
    MyPushButton* bet1Btn = new MyPushButton("../picture/OnePoint.png", "1 Point!");
    MyPushButton* bet2Btn = new MyPushButton("../picture/TwoPoints.png", "2 Points!");
    MyPushButton* bet3Btn = new MyPushButton("../picture/ThreePoints.png", "3 Points!");

    betNoBtn->setParent(this);
    bet1Btn->setParent(this);
    bet2Btn->setParent(this);
    bet3Btn->setParent(this);

    betNoBtn->raise();
    bet1Btn->raise();
    bet2Btn->raise();
    bet3Btn->raise();

    betNoBtn->move(betBtnWidthStartPos, betBtnHeightStartPos);
    bet1Btn->move(betBtnWidthStartPos + betBtnWidthSpace, betBtnHeightStartPos);
    bet2Btn->move(betBtnWidthStartPos + 2*betBtnWidthSpace, betBtnHeightStartPos);
    bet3Btn->move(betBtnWidthStartPos + 3*betBtnWidthSpace, betBtnHeightStartPos);

    betNoBtn->show();
    bet1Btn->show();
    bet2Btn->show();
    bet3Btn->show();

    connect(betNoBtn, &MyPushButton::clicked, this, &GameWindow::onBetNoBtnClicked);
    connect(bet1Btn, &MyPushButton::clicked, this, &GameWindow::onBet1BtnClicked);
    connect(bet2Btn, &MyPushButton::clicked, this, &GameWindow::onBet2BtnClicked);
    connect(bet3Btn, &MyPushButton::clicked, this, &GameWindow::onBet3BtnClicked);
}

void GameWindow::onBetNoBtnClicked(){
    if(gameControl->getPlayerA()->getIsPerson()){
        gameControl->getPlayerA()->setBetPoints(0);
    }
    else if(gameControl->getPlayerB()->getIsPerson()){
        gameControl->getPlayerB()->setBetPoints(0);
    }
    else if(gameControl->getPlayerC()->getIsPerson()){
        gameControl->getPlayerC()->setBetPoints(0);
    }

//    QTimer::singleShot(500, this, [=](){

//    });
    this->update();

    betNoBtn->setVisible(false);
//    bet1Btn->setVisible(false);
//    bet2Btn->setVisible(false);
//    bet3Btn->setVisible(false);

    this->update();

    qDebug() << "No bet!";
}

void GameWindow::onBet1BtnClicked(){
    if(gameControl->getPlayerA()->getIsPerson()){
        gameControl->getPlayerA()->setBetPoints(1);
    }
    else if(gameControl->getPlayerB()->getIsPerson()){
        gameControl->getPlayerB()->setBetPoints(1);
    }
    else if(gameControl->getPlayerC()->getIsPerson()){
        gameControl->getPlayerC()->setBetPoints(1);
    }

    betNoBtn->hide();
    bet1Btn->hide();
    bet2Btn->hide();
    bet3Btn->hide();

    qDebug() << "1 Point!";
}

void GameWindow::onBet2BtnClicked(){
    if(gameControl->getPlayerA()->getIsPerson()){
        gameControl->getPlayerA()->setBetPoints(2);
    }
    else if(gameControl->getPlayerB()->getIsPerson()){
        gameControl->getPlayerB()->setBetPoints(2);
    }
    else if(gameControl->getPlayerC()->getIsPerson()){
        gameControl->getPlayerC()->setBetPoints(2);
    }

    betNoBtn->hide();
    bet1Btn->hide();
    bet2Btn->hide();
    bet3Btn->hide();

    qDebug() << "2 Points!";
}

void GameWindow::onBet3BtnClicked(){
    if(gameControl->getPlayerA()->getIsPerson()){
        gameControl->getPlayerA()->setBetPoints(3);
    }
    else if(gameControl->getPlayerB()->getIsPerson()){
        gameControl->getPlayerB()->setBetPoints(3);
    }
    else if(gameControl->getPlayerC()->getIsPerson()){
        gameControl->getPlayerC()->setBetPoints(3);
    }

    betNoBtn->hide();
    bet1Btn->hide();
    bet2Btn->hide();
    bet3Btn->hide();

    qDebug() << "3 Points!";
}

/*
void GameWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    baseCardPos = QPoint((width() - cardSize.width()) / 2, height() / 2 - 100);
    //m_baseCard->move(m_baseCardPos);


    //////////////////////////////////////////////////////////////////////////
    QMap<Player*, PlayerContext>::Iterator it;

    // 左机器人
    it = playerContextMap.find(gameControl->getPlayerC());
    it->cardsRect = QRect(10, 180, 100, height() - 200);
    it->playHandRect = QRect(180, 150, 100, 100);
    it->rolePic->move(it->cardsRect.left(), it->cardsRect.top() - 100);

    // 右机器人
    it = playerContextMap.find(gameControl->getPlayerB());
    it->cardsRect = QRect(rect().right() - 110, 180, 100, height() - 200);
    it->playHandRect = QRect(rect().right() - 280, 150, 100, 100);
    it->rolePic->move(it->cardsRect.left(), it->cardsRect.top() - 100);

    // 我
    it = playerContextMap.find(gameControl->getPlayerA());
    it->cardsRect = QRect(250, rect().bottom() - 120, width() - 500, 100);
    it->playHandRect = QRect(150, rect().bottom() - 280, width() - 300, 100);
    it->rolePic->move(it->cardsRect.right(), it->cardsRect.top() - 10);


    QRect rectUserTool(it->playHandRect.left(), it->playHandRect.bottom(),
        it->playHandRect.width(), it->cardsRect.top() - it->playHandRect.bottom());

    userTool->setGeometry(rectUserTool);


    for (it = playerContextMap.begin(); it != playerContextMap.end(); it++)
    {
        QRect playCardsRect = it->playHandRect;
        QLabel* infoLabel = it->info;

        QPoint pt( playCardsRect.left() + (playCardsRect.width() - infoLabel->width()) / 2,
            playCardsRect.top() + (playCardsRect.height() - infoLabel->height()) / 2 );
        infoLabel->move(pt);
    }

    // 显示剩下三张牌

    int base = (width() - 3 * cardSize.width() - 2 * 10) / 2;
    for (int i = 0; i < restThreeCards.size(); i++)
    {
        restThreeCards[i]->move(base + (cardSize.width() + 10) * i, 20);
    }

    //    UpdatePlayerCards(gameControl->getPlayerC());
//    UpdatePlayerCards(gameControl->getPlayerA());
    //UpdatePlayerCards(gameControl->getPlayerB());
}
*/


void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/game_scene.PNG");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

/*void GameWindow::HidePlayerLastCards(Player* player)
{
    QMap<Player*, PlayerContext>::Iterator it = playerContextMap.find(player);
    if (it != playerContextMap.end())
    {
        if (it->lastCards.empty())	// 上一次打的空牌，即pass
        {
            it->info->hide();
        }
        else
        {
            QVector<Card> lastCards = it->lastCards;
            QVector<Card>::ConstIterator itLast = lastCards.constBegin();
            for (; itLast != lastCards.constEnd(); itLast++)
            {
                cardWidgetMap[*itLast]->hide();
            }
        }
    }
}
*/
void GameWindow::UpdatePlayerCards(Player* player)
{
    QVector<Card> restCards = player->getHandCards();
    //CardList restCardList = restCards.ToCardList(Cards::Desc);

    const int cardSpacing = 20;		// 牌间隔

    // 显示剩下的牌
    QRect cardsRect = playerContextMap[player].cardsRect;
    QVector<Card>::iterator itRest = restCards.begin();
    for (int i = 0; itRest != restCards.end(); itRest++, i++)
    {
        CardWidget* cardPic = cardWidgetMap[*itRest];
        cardPic->setFront(playerContextMap[player].isFrontSide);
        cardPic->show();
        cardPic->raise();

        if (playerContextMap[player].cardsAlign == Horizontal)
        {
            int leftBase = cardsRect.left() + (cardsRect.width() - (restCards.size() - 1) * cardSpacing - cardPic->width()) / 2;
            int top = cardsRect.top() + (cardsRect.height() - cardPic->height()) / 2;
            if (cardPic->getIsSelected()) top -= 10;

            cardPic->move(leftBase + i * cardSpacing, top);
        }
        else
        {
            int left = cardsRect.left() + (cardsRect.width() - cardPic->width()) / 2;
            if (cardPic->getIsSelected()) left += 10;
            int topBase = cardsRect.top() + (cardsRect.height() - (restCards.size() - 1) * cardSpacing - cardPic->height()) / 2;
            cardPic->move(left, topBase + i * cardSpacing);
        }
    }

    // 显示上一次打出去的牌
    QRect playCardsRect = playerContextMap[player].playHandRect;
    if (!playerContextMap[player].lastCards.empty())		// 不是空牌
    {
        int playSpacing = 24;
        QVector<Card> lastCards = playerContextMap[player].lastCards;
        QVector<Card>::iterator itPlayed = lastCards.begin();
        for (int i = 0; itPlayed != lastCards.end(); itPlayed++, i++)
        {
            CardWidget* cardPic = cardWidgetMap[*itPlayed];
            cardPic->setFront(true);
            cardPic->raise();

            if (playerContextMap[player].cardsAlign == Horizontal)
            {
                int leftBase = playCardsRect.left () +
                    (playCardsRect.width() - (lastCards.size() - 1) * playSpacing - cardPic->width()) / 2;
                int top = playCardsRect.top() + (playCardsRect.height() - cardPic->height()) / 2;
                cardPic->move(leftBase + i * playSpacing, top);
            }
            else
            {
                int left = playCardsRect.left() + (playCardsRect.width() - cardPic->width()) / 2;
                int topBase = playCardsRect.top();
                cardPic->move(left, topBase + i * playSpacing);
            }
        }
    }
}
