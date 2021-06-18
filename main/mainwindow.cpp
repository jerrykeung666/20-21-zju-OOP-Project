#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pushbutton.h"
#include "settingwindow.h"

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

    // set window size
    setFixedSize(1280,800);

    // set window title
    setWindowTitle("Landlord: Welcome!");

    // set icon
    setWindowIcon(QIcon("../picture/icon.jfif"));

    // set next window: setting window
    settingWindow *setting_window = new settingWindow();
    /*connect(setting_window, &settingWindow::goBack, [=](){
        setting_window->hide();
        this->show();
    });*/

    // set game mode 1
    pushbutton *mode1_pb = new pushbutton("../picture/gamemode1.png", "Game Mode 1");
    mode1_pb->setParent(this);
    mode1_pb->move(this->width()*0.5-mode1_pb->width()*0.5, this->height()*0.25);
    connect(mode1_pb, &pushbutton::clicked, mode1_pb,[=](){
        qDebug() << "Enter mode: Game Mode 1";
        mode1_pb->zoom_in();
        mode1_pb->zoom_out();
        QTimer::singleShot(500, this, [=](){
            this->hide();
            setting_window->show();
        });
    });

    // set mode 2
    pushbutton *mode2_pb = new pushbutton("../picture/gamemode2.png", "Game Mode 2");
    mode2_pb->setParent(this);
    mode2_pb->move(this->width()*0.5-mode2_pb->width()*0.5, this->height()*0.4);
    connect(mode2_pb, &pushbutton::clicked, mode2_pb, [=](){
        qDebug() << "Enter mode: Game Mode 2";
        mode2_pb->zoom_in();
        mode2_pb->zoom_out();
        QTimer::singleShot(500, this, [=](){
            this->hide();
            setting_window->show();
        });
    });

    // set mode exit
    pushbutton *modeexit_pb = new pushbutton("../picture/quit.png", "Game Mode Exit");
    modeexit_pb->setParent(this);
    modeexit_pb->move(this->width()*0.5-modeexit_pb->width()*0.5, this->height()*0.55);

    connect(modeexit_pb, &pushbutton::clicked, modeexit_pb, [=](){
        qDebug() << "Enter mode: Game Mode Exit";
        modeexit_pb->zoom_in();
        modeexit_pb->zoom_out();

        // Time delay & msgBox
        QTimer::singleShot(200, this, [=](){//to be updated: code reuse
            QMessageBox msgBox;
            int ret;

            msgBox.setWindowTitle("Exit Confirmation");
            msgBox.setText("Do you want to exit the game?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);
            ret = msgBox.exec();

            switch(ret){
                case QMessageBox::Yes:
                    qDebug() << "Quit";
                    close();
                    break;
                case QMessageBox::No:
                    qDebug() << "Not yet";
                    break;
                default:
                    break;
            }
        });

    });
}


void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/background.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}


MainWindow::~MainWindow()
{
    delete ui;
}

