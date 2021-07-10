#include "gamewindow.h"
#include "cardgroups.h"

#include <algorithm>
#include <QPainter>
#include <QDebug>
#include <QPalette>
#include <QMessageBox>

const QSize GameWindow::gameWindowSize = QSize(1200, 800);

const int GameWindow::cardWidthSpace = 35;
const int GameWindow::cardHeightSpace = 20; //TODO
const int GameWindow::cardRemSpace = 180; //TODO

const int GameWindow::myCardWidthStartPos = 600; //TODO
const int GameWindow::myCardHeightStartPos = 650; //TODO
const int GameWindow::leftCardWidthStartPos = 10; //TODO
const int GameWindow::leftCardHeightStartPos = 100; //TODO
const int GameWindow::rightCardWidthStartPos = 1075; //TODO
const int GameWindow::rightCardHeightStartPos = 100; //TODO
const int GameWindow::remCardWidthStartPos = 350;//TODO
const int GameWindow::remCardHeightStartPos = 20;//TODO

const int GameWindow::betBtnWidthStartPos = 320; //TODO
const int GameWindow::betBtnHeightStartPos = 575; //TODO
const int GameWindow::betBtnWidthSpace = 140; //TODO

const int GameWindow::fontSize = 20;
const QPoint GameWindow::myBetInfoPos = QPoint(500, 375);
const QPoint GameWindow::leftPlayerBetInfoPos = QPoint(135, 50);
const QPoint GameWindow::rightPlayerBetInfoPos = QPoint(975, 50);

const int GameWindow::cardSelectedShift = 35;

const QPoint GameWindow::passBtnStartPos = QPoint(350, 575);
const QPoint GameWindow::playBtnStartPos = QPoint(700, 575);
const QPoint GameWindow::myCardZone = QPoint(600, 480);
const int GameWindow::myCardZoneWidthSpace = 40;
const QPoint GameWindow::rightCardZone = QPoint(925, 150);
const int GameWindow::rightCardZoneHeightSpace = 40;
const QPoint GameWindow::leftCardZone = QPoint(130, 150);
const int GameWindow::leftCardZoneHeightSpace = 40;

const QPoint GameWindow::myStatusPos = QPoint(925, 500);
const QPoint GameWindow::rightStatusPos = QPoint(925, 50);
const QPoint GameWindow::leftStatusPos = QPoint(130, 50);

const QPoint GameWindow::myLandLordPos = QPoint(50, 500);



GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{

    setFixedSize(gameWindowSize);
    setWindowTitle("Landlord: Welcome!");
    setWindowIcon(QIcon("../picture/icon.jfif"));

    gameControl = new GameControl(this);
    gameControl->init();

    cardSize = QSize(80, 105);
    initCardWidgetMap();
    initButtons();
    initPlayerContext();
    initInfoLabel();
    initSignalsAndSlots();

    qDebug() << "初始化牌";
}

void GameWindow::init(){
    gameControl->initCards();
    initLandLordCards();
}

void GameWindow::insertCardWidget(const Card &card, QString &path)
{
    CardWidget *cardWidget = new CardWidget(this);
    QPixmap pix = QPixmap(path);

    cardWidget->hide();
    cardWidget->setCard(card);
    cardWidget->setPix(pix);

    cardWidgetMap.insert(card, cardWidget);

    connect(cardWidget, &CardWidget::notifySelected, this, &GameWindow::cardSelected);
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

void GameWindow::initInfoLabel(){
    QPalette palette = this->palette();
    palette.setColor(QPalette::WindowText, Qt::red);

    QFont font("Microsoft YaHei", fontSize, QFont::Bold);

    myBetInfo = new QLabel();
    myBetInfo->setParent(this);
    myBetInfo->setPalette(palette);
    myBetInfo->setFont(font);
    myBetInfo->raise();
    myBetInfo->move(myBetInfoPos);
    myBetInfo->hide();

    rightBetInfo = new QLabel();
    rightBetInfo->setParent(this);
    rightBetInfo->setPalette(palette);
    rightBetInfo->setFont(font);
    rightBetInfo->raise();
    rightBetInfo->move(rightPlayerBetInfoPos);
    rightBetInfo->hide();

    leftBetInfo = new QLabel();
    leftBetInfo->setParent(this);
    leftBetInfo->setPalette(palette);
    leftBetInfo->setFont(font);
    leftBetInfo->raise();
    leftBetInfo->move(leftPlayerBetInfoPos);
    leftBetInfo->hide();

    passInfo = new QLabel();
    passInfo->setParent(this);
    passInfo->setPalette(palette);
    passInfo->setFont(font);
    passInfo->raise();
    passInfo->move(myBetInfoPos);
    passInfo->hide();

    playInfo = new QLabel();
    playInfo->setParent(this);
    playInfo->setPalette(palette);
    playInfo->setFont(font);
    playInfo->raise();
    playInfo->move(myBetInfoPos);
    playInfo->hide();

    leftPassInfo = new QLabel();
    leftPassInfo->setParent(this);
    leftPassInfo->setPalette(palette);
    leftPassInfo->setFont(font);
    leftPassInfo->raise();
    leftPassInfo->move(leftPlayerBetInfoPos);
    leftPassInfo->hide();

    rightPassInfo = new QLabel();
    rightPassInfo->setParent(this);
    rightPassInfo->setPalette(palette);
    rightPassInfo->setFont(font);
    rightPassInfo->raise();
    rightPassInfo->move(rightPlayerBetInfoPos);
    rightPassInfo->hide();

    myStatusInfo = new QLabel();
    myStatusInfo->setParent(this);
    myStatusInfo->setPalette(palette);
    myStatusInfo->setFont(font);
    myStatusInfo->raise();
    myStatusInfo->move(myStatusPos);
    myStatusInfo->hide();

    leftStatusInfo = new QLabel();
    leftStatusInfo->setParent(this);
    leftStatusInfo->setPalette(palette);
    leftStatusInfo->setFont(font);
    leftStatusInfo->raise();
    leftStatusInfo->move(leftStatusPos);
    leftStatusInfo->hide();

    rightStatusInfo = new QLabel();
    rightStatusInfo->setParent(this);
    rightStatusInfo->setPalette(palette);
    rightStatusInfo->setFont(font);
    rightStatusInfo->raise();
    rightStatusInfo->move(rightStatusPos);
    rightStatusInfo->hide();


    QFont font2("Microsoft YaHei", 10, QFont::Bold);
    myLandLordInfo = new QLabel();
    myLandLordInfo->setParent(this);
    myLandLordInfo->setPalette(palette);
    myLandLordInfo->setFont(font2);
    myLandLordInfo->lower();
    myLandLordInfo->move(myLandLordPos);
    myLandLordInfo->setText("LandLord:\n everyone");
    myLandLordInfo->show();
}

void GameWindow::initButtons()
{
    startBtn = new MyPushButton("../picture/game_start.png", "开始游戏");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.5);


    betNoBtn = new MyPushButton("../picture/No.png", "No!");
    bet1Btn = new MyPushButton("../picture/OnePoint.png", "1 Point!");
    bet2Btn = new MyPushButton("../picture/TwoPoints.png", "2 Points!");
    bet3Btn = new MyPushButton("../picture/ThreePoints.png", "3 Points!");

    betNoBtn->setParent(this);
    bet1Btn->setParent(this);
    bet2Btn->setParent(this);
    bet3Btn->setParent(this);

    betNoBtn->move(betBtnWidthStartPos, betBtnHeightStartPos);
    bet1Btn->move(betBtnWidthStartPos + betBtnWidthSpace, betBtnHeightStartPos);
    bet2Btn->move(betBtnWidthStartPos + 2*betBtnWidthSpace, betBtnHeightStartPos);
    bet3Btn->move(betBtnWidthStartPos + 3*betBtnWidthSpace, betBtnHeightStartPos);

    betNoBtn->hide();
    bet1Btn->hide();
    bet2Btn->hide();
    bet3Btn->hide();


    passBtn = new MyPushButton("../picture/Pass.png", "Pass!");
    playBtn = new MyPushButton("../picture/Play.png", "Play!");

    passBtn->setParent(this);
    playBtn->setParent(this);

    passBtn->move(passBtnStartPos);
    playBtn->move(playBtnStartPos);

    passBtn->hide();
    playBtn->hide();
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

void GameWindow::initSignalsAndSlots(){
    connect(startBtn, &MyPushButton::clicked, this, &GameWindow::onStartBtnClicked);

    connect(betNoBtn, &MyPushButton::clicked, this, &GameWindow::onBetNoBtnClicked);
    connect(bet1Btn, &MyPushButton::clicked, this, &GameWindow::onBet1BtnClicked);
    connect(bet2Btn, &MyPushButton::clicked, this, &GameWindow::onBet2BtnClicked);
    connect(bet3Btn, &MyPushButton::clicked, this, &GameWindow::onBet3BtnClicked);

    connect(passBtn, &MyPushButton::clicked, this, &GameWindow::passCards);
    connect(playBtn, &MyPushButton::clicked, this, &GameWindow::playCards);

    //

    connect(gameControl, &GameControl::callGamewindowShowBets, this, &GameWindow::onBetPointsCall);
    connect(gameControl, &GameControl::callGamewindowShowLandlord, this, [=](){
        if (gameControl->getgamemodel() == 1){
            if (gameControl->getPlayerA()->getIsLandLord()){
                myLandLordInfo->setText("LandLord:\n me");
            }else if (gameControl->getPlayerB()->getIsLandLord()){
                myLandLordInfo->setText("LandLord:\n right");
            }else{
                myLandLordInfo->setText("LandLord:\n left");
            }
            myLandLordInfo->show();
        }
        showRemLandLordCard("show");
    });

    connect(gameControl, &GameControl::NotifyPlayerPlayHand, this, &GameWindow::otherPlayerShowCards);
    connect(gameControl, &GameControl::NotifyPlayerbutton, this, &GameWindow::myPlayerShowButton);

    connect(gameControl, &GameControl::NotifyPlayerStatus, this, &GameWindow::showEndStatus);
}

void GameWindow::onStartBtnClicked()
{
    startBtn->hide();
    showLandLordCard();
    if (gameControl->getgamemodel() == 1){
        call4Landlord();
    }
    else{
        startGame();
    }


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

    showRemLandLordCard("hidden");
}

void GameWindow::showOtherPlayerCard(Player* otherPlayer, const QString status){
    QVector<Card> myCards;
    QVector<CardWidget*> myWidget;
    myCards = otherPlayer->getHandCards();
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
        //qDebug() << myWidget.at(i)->getIsFront();
        //qDebug() << myWidget.size();
    }
}

void GameWindow::showMyCard(Player* myPlayer){
    QVector<Card> myCards;
    QVector<CardWidget*> myWidget;
    myCards = myPlayer->getHandCards();

    int len = myCards.size();
    for (int i=0; i < len; i++) {
        myWidget.push_back(cardWidgetMap[myCards.at(i)]);
        myWidget.at(i)->setOwner(myPlayer);
        myWidget.at(i)->raise();
        myWidget.at(i)->move(myCardWidthStartPos + (i-len/2-1)*cardWidthSpace, myCardHeightStartPos);
        myWidget.at(i)->show();
    }
}

void GameWindow::showRemLandLordCard(QString status){
    for (int i=0; i < restThreeCards.size(); i++) {
        restThreeCards.at(i)->raise();

        if (status == "hidden")
            restThreeCards.at(i)->setFront(false);
        else{
            restThreeCards.at(i)->setFront(true);
            if(gameControl->getPlayerA()->getIsLandLord())
                showMyCard(gameControl->getPlayerA());
            else if(gameControl->getPlayerB()->getIsLandLord())
                showOtherPlayerCard(gameControl->getPlayerB(), "right");
            else if(gameControl->getPlayerC()->getIsLandLord())
                showOtherPlayerCard(gameControl->getPlayerC(), "left");
        }

        restThreeCards.at(i)->move(remCardWidthStartPos + i*cardRemSpace, remCardHeightStartPos);
        restThreeCards.at(i)->show();
    }

    if (status == "show"){
        QTimer::singleShot(1200, this, [=](){
            myBetInfo->hide();
            rightBetInfo->hide();
            leftBetInfo->hide();
            startGame();
        });
    }
}

void GameWindow::call4Landlord(){
    betNoBtn->show();
    bet1Btn->show();
    bet2Btn->show();
    bet3Btn->show();
}

void GameWindow::startGame(){//TODO
    //qDebug() << (gameControl->getCurrentPlayer() == gameControl->getPlayerA());
    //if(gameControl->getCurrentPlayer() == gameControl->getPlayerA()){
        passBtn->show();
        playBtn->show();
    //}
}

void GameWindow::onBetNoBtnClicked(){
    qDebug() << "my no bet";
    if(gameControl->getPlayerA()->getIsPerson()){
        gameControl->getPlayerA()->setBetPoints(0);
    }
    else if(gameControl->getPlayerB()->getIsPerson()){
        gameControl->getPlayerB()->setBetPoints(0);
    }
    else if(gameControl->getPlayerC()->getIsPerson()){
        gameControl->getPlayerC()->setBetPoints(0);
    }

    QTimer::singleShot(10, this, [=](){
        betNoBtn->hide();
        bet1Btn->hide();
        bet2Btn->hide();
        bet3Btn->hide();
        gameControl->updateBetPoints(0);
    });

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

    QTimer::singleShot(10, this, [=](){
        betNoBtn->hide();
        bet1Btn->hide();
        bet2Btn->hide();
        bet3Btn->hide();
        gameControl->updateBetPoints(1);
    });

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

    QTimer::singleShot(10, this, [=](){
        betNoBtn->hide();
        bet1Btn->hide();
        bet2Btn->hide();
        bet3Btn->hide();
        gameControl->updateBetPoints(2);
    });

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

    QTimer::singleShot(10, this, [=](){
        betNoBtn->hide();
        bet1Btn->hide();
        bet2Btn->hide();
        bet3Btn->hide();
        gameControl->updateBetPoints(3);
    });

    qDebug() << "3 Points!";
}

void GameWindow::cardSelected(Qt::MouseButton mouseButton){
    CardWidget* cardWidget = (CardWidget*)sender();
    Player* player = cardWidget->getOwner();

    if(mouseButton == Qt::LeftButton){
        cardWidget->setIsSelected(!cardWidget->getIsSelected()); // switch statu
        if(player == gameControl->getPlayerA())
            showMySelectedCard(player);
//        int i;
//        for(i=0; i < player->getSelectCards().size(); i++){
//            if(player->getSelectCards().at(i) == cardWidget->getCard())
//                break;
//        }

//        if(i < player->getSelectCards().size())
//            player->getSelectCards().remove(i);
//        else if(i == player->getSelectCards().size())
//            player->getSelectCards().push_back(cardWidget->getCard());
    }
}

void GameWindow::showMySelectedCard(Player* player){//TODO
    CardWidget* selectedWidget;

    for(int i=0; i < player->getHandCards().size(); i++){
        selectedWidget = cardWidgetMap[player->getHandCards().at(i)];
        if(selectedWidget->getIsSelected())
            selectedWidget->move(selectedWidget->x(), myCardHeightStartPos - cardSelectedShift);
        else
            selectedWidget->move(selectedWidget->x(), myCardHeightStartPos);
    }
}


void GameWindow::onBetPointsCall(Player* player){
    if(player->getIsPerson()){
        int betPoints = player->getBetPoints();

        if (betPoints == 0)
            myBetInfo->setText("No!");
        else if(betPoints == 1)
            myBetInfo->setText("1 Point!");
        else
            myBetInfo->setText(QString::number(betPoints) + " Points!");

        myBetInfo->show();
    }
    else{
        if(gameControl->getPlayerB() == player){
            int betPoints = player->getBetPoints();

            if (betPoints == 0)
                rightBetInfo->setText("No!");
            else if(betPoints == 1)
                rightBetInfo->setText("1 Point!");
            else
                rightBetInfo->setText(QString::number(betPoints) + " Points!");

            rightBetInfo->show();
        }
        else{
            int betPoints = player->getBetPoints();

            if (betPoints == 0)
                leftBetInfo->setText("No!");
            else if(betPoints == 1)
                leftBetInfo->setText("1 Point!");
            else
                leftBetInfo->setText(QString::number(betPoints) + " Points!");

            leftBetInfo->show();
        }
    }

    qDebug() << "betInfo";
}


void GameWindow::playCards(){
    QVector<Card> selectedCards;
    QVector<Card> handCards;
    QVector<int> idx;
    CardWidget* cardWidget;

    handCards = gameControl->getCurrentPlayer()->getHandCards();
    qDebug() << handCards.size();
    for(int i=0; i < handCards.size(); i++){
        cardWidget = cardWidgetMap[handCards.at(i)];
        if(cardWidget->getIsSelected()){
            selectedCards.push_back(handCards.at(i));
            idx.push_back(i);
        }
    }

    for(int i=0; i < idx.size(); i++){
        handCards.remove(idx.at(i) - i);
    }

    gameControl->getCurrentPlayer()->resetSelectCards(selectedCards);
    //playerA->selectedCard()->checkali(gmctl->punchcard)
    // wait bool: successful -> animation, failed -> error msgbox/qlabel
    // slots: robot display

    CardGroups cg = CardGroups(selectedCards);

    qDebug() << gameControl->getCurrentCombo().getCards().size();
    if(gameControl->getCurrentPlayer()->getSelectCards().canBeat(gameControl->getCurrentCombo())
            || gameControl->getCurrentPlayer() == gameControl->getEffectivePlayer()){ //pending: canBeat! You win in the last cycle!
        qDebug() << gameControl->getCurrentCombo().getCards().size();
        gameControl->getCurrentPlayer()->resetHandCards(handCards);
        showPlayCard();
        gameControl->onPlayerHand(gameControl->getCurrentPlayer(), cg);
    }
    else{
        selectedCards.clear();
        gameControl->getCurrentPlayer()->resetSelectCards(selectedCards);
        playInfo->setText("Combo Invalid!");
        playInfo->show();
        showPlayCard();
        QTimer::singleShot(600, this, [=](){
            playInfo->hide();
        });
    }
}


void GameWindow::showPlayCard(){
    qDebug() << "++++++++++++++++++++++++";
    qDebug() << gameControl->getPlayerA()->getHandCards().size();
    if(gameControl->getCurrentPlayer() == gameControl->getPlayerA()){
        // check whether is empty
        if(gameControl->getPlayerA()->getSelectCards().getCards().isEmpty()){
            QVector<Card> handCards;
            CardWidget* cardWidget;

            handCards = gameControl->getCurrentPlayer()->getHandCards();
            for(int i=0; i < handCards.size(); i++){
                cardWidget = cardWidgetMap[handCards.at(i)];
                cardWidget->setIsSelected(false);
            }

            showMyCard(gameControl->getPlayerA());
            return;
        }
        else
            showMyCard(gameControl->getPlayerA());
    }
    else if(gameControl->getCurrentPlayer() == gameControl->getPlayerB())
        showOtherPlayerCard(gameControl->getCurrentPlayer(), "right");
    else
        showOtherPlayerCard(gameControl->getCurrentPlayer(), "left");

    // show selected cards
    Card selectCard;
    CardWidget* cardWidget;
    int len = gameControl->getCurrentPlayer()->getSelectCards().getCards().size();
    for(int i=0; i < len; i++){
        selectCard = gameControl->getCurrentPlayer()->getSelectCards().getCards().at(i);
        cardWidget = cardWidgetMap[selectCard];
        cardWidget->raise();
        cardWidget->move(myCardZone.x() + (i-len/2-1)*myCardZoneWidthSpace, myCardZone.y());
        cardWidget->show();
    }

    passBtn->hide();
    playBtn->hide();
}


void GameWindow::passCards(){
    QVector<Card> handCards;
    CardWidget* cardWidget;

    handCards = gameControl->getCurrentPlayer()->getHandCards();
    for(int i=0; i < handCards.size(); i++){
        cardWidget = cardWidgetMap[handCards.at(i)];
        cardWidget->setIsSelected(false);
    }

    if(gameControl->getCurrentPlayer() == gameControl->getPlayerA())
        showMyCard(gameControl->getPlayerA());
    else if(gameControl->getCurrentPlayer() == gameControl->getPlayerB())
        showOtherPlayerCard(gameControl->getCurrentPlayer(), "right");
    else
        showOtherPlayerCard(gameControl->getCurrentPlayer(), "left");

    CardGroups cg;
    gameControl->onPlayerHand(gameControl->getCurrentPlayer(),cg);

    passInfo->setText("PASS!");
    passInfo->show();

    passBtn->hide();
    playBtn->hide();

//    QTimer::singleShot(600, this, [=](){
//        passInfo->hide();
//    });
}


void GameWindow::otherPlayerShowCards(Player* player, CardGroups cards){
    if(player == gameControl->getPlayerB()){
        showOtherPlayerCard(player, "right");
        showOtherPlayerPlayCard(player, cards, "right");
    }
    else if(player == gameControl->getPlayerC()){
        showOtherPlayerCard(player, "left");
        showOtherPlayerPlayCard(player, cards, "left");
    }
}


void GameWindow::showOtherPlayerPlayCard(Player* otherPlayer, CardGroups cards, const QString status){
    if(status == "right"){
        if(cards.getCards().size() == 0){
            rightPassInfo->setText("Pass!");
            rightPassInfo->show();
        }
        else{
            Card card;
            CardWidget* cardWidget;
            for(int i=0; i < cards.getCards().size(); i++){
                card = cards.getCards().at(i);
                cardWidget = cardWidgetMap[card];
                cardWidget->setFront(true);
                cardWidget->raise();
                cardWidget->move(rightCardZone.x(), rightCardZone.y() + i*rightCardZoneHeightSpace);
                cardWidget->show();
            }
        }
    }
    else{
        if(cards.getCards().size() == 0){
            leftPassInfo->setText("Pass!");
            leftPassInfo->show();
        }
        else{
            Card card;
            CardWidget* cardWidget;

            for(int i=0; i < cards.getCards().size(); i++){
                card = cards.getCards().at(i);
                cardWidget = cardWidgetMap[card];
                cardWidget->setFront(true);
                cardWidget->raise();
                cardWidget->move(leftCardZone.x(), leftCardZone.y() + i*leftCardZoneHeightSpace);
                cardWidget->show();
            }
        }
    }
}


void GameWindow::myPlayerShowButton(Player* player){
    qDebug() << "hide card";
    //QTimer::singleShot(1000, this, [=](){
        if(player == gameControl->getPlayerA()){
            if (gameControl->getEffectivePlayer() != player)
                passBtn->show();
            playBtn->show();
        }

        CardGroups cardGroup = player->lastCards; //pending
        if(cardGroup.getCards().size() == 0){
            if(player == gameControl->getPlayerB())
                rightPassInfo->hide();
            else if(player == gameControl->getPlayerC()){
                leftPassInfo->hide();
            }
            else{
                passInfo->hide();
            }
        }
        else{

            Card card;
            CardWidget* cardWidget;
            for(int i=0; i < cardGroup.getCards().size(); i++){
                card = cardGroup.getCards().at(i);
                cardWidget = cardWidgetMap[card];
                cardWidget->hide();
            }

        }
    //});
}


void GameWindow::showEndStatus(Player* player){
    playInfo->hide();
    leftPassInfo->hide();
    rightPassInfo->hide();

    myStatusInfo->setText("Lose!");
    leftStatusInfo->setText("Lose!");
    rightStatusInfo->setText("Lose!");

    if(player == gameControl->getPlayerA())
        myStatusInfo->setText("Win!");
    else if(player == gameControl->getPlayerB())
        rightStatusInfo->setText("Win!");
    else
        leftStatusInfo->setText("Win!");

    myStatusInfo->show();
    leftStatusInfo->show();
    rightStatusInfo->show();

    QTimer::singleShot(100, this, [=](){
        if(player == gameControl->getPlayerA())
            QMessageBox::information(this, tr("Result"), QString("You Win!"));
        else
            QMessageBox::information(this, tr("Result"), QString("You Lose!"));
    });

    //startBtn->show();
}


void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/game_scene.PNG");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

GameControl* GameWindow::getgameControl(){
    return this->gameControl;
}

