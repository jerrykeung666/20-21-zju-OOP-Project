#include "gamewindow.h"

#include <QPainter>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1200,800);
    setWindowTitle("Landlord: Welcome!");
    setWindowIcon(QIcon("../picture/icon.jfif"));

    MyPushButton *startBtn = new MyPushButton("../picture/game_start.png", "开始游戏");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.5);
    connect(startBtn, &MyPushButton::clicked, startBtn,[=](){
        qDebug() << "开始游戏";
        startBtn->zoomIn();
        startBtn->zoomOut();
    });

    gameControl = new GameControl(this);
    gameControl->init();
    gameControl->initCards();
    qDebug() << "初始化牌";
}


void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/game_scene.PNG");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
