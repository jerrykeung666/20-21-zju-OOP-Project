#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include "gamewindow.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1000, 650);
    setWindowTitle("Landlord: Welcome!");
    setWindowIcon(QIcon("../picture/icon.jfif"));

    // set next window: game window
    gameWindow = new GameWindow(this);
//    connect(gameWindow, &GameWindow::goBack, [=](){
//        gameWindow->hide();
//        this->show();
//    });

    // set game mode 1
    MyPushButton *mode1Btn = new MyPushButton("../picture/mode1.png", "Game Mode 1");
    mode1Btn->setParent(this);
    mode1Btn->move(this->width()*0.7-mode1Btn->width()*0.5, this->height()*0.3);
    connect(mode1Btn, &MyPushButton::clicked, mode1Btn,[=](){
        qDebug() << "Enter mode: Game Mode 1";
        mode1Btn->zoomIn();
        mode1Btn->zoomOut();
        this->hide();
        gameWindow->show();
    });

//    // set mode 2
    MyPushButton *mode2Btn = new MyPushButton("../picture/mode2.png", "Game Mode 2");
    mode2Btn->setParent(this);
    mode2Btn->move(this->width()*0.7-mode2Btn->width()*0.5, this->height()*0.5);
    connect(mode2Btn, &MyPushButton::clicked, mode2Btn, [=](){
        qDebug() << "Enter mode: Game Mode 2";
        mode2Btn->zoomIn();
        mode2Btn->zoomOut();
//        QTimer::singleShot(500, this, [=](){
//            this->hide();
//            //game_window->show();
//        });
    });

    // set mode exit
    MyPushButton *exitBtn = new MyPushButton("../picture/mode3.png", "Game Mode Exit");
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.7-exitBtn->width()*0.5, this->height()*0.7);
    connect(exitBtn, &MyPushButton::clicked, exitBtn, [=](){
        qDebug() << "Enter mode: Game Mode Exit";
        exitBtn->zoomIn();
        exitBtn->zoomOut();

        // Time delay & msgBox
        QTimer::singleShot(200, this, [=](){
            this->close();
        });
    });
}


void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/start.PNG");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}


MainWindow::~MainWindow()
{
    delete ui;
}

