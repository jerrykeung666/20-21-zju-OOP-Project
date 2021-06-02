#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pushbutton.h"

#include <QPainter>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set window size
    setFixedSize(1280,800);

    // set window title
    setWindowTitle("Landlord");

    // set game mode 1, mode 2 and exit
    pushbutton *mode1_pb = new pushbutton("../picture/gamemode1.png");
    mode1_pb->setParent(this);
    mode1_pb->move(this->width()*0.5-mode1_pb->width()*0.5, this->height()*0.25);
    connect(mode1_pb, &pushbutton::clicked, mode1_pb, &pushbutton::on_pushbutton_clicked);

    pushbutton *mode2_pb = new pushbutton("../picture/gamemode2.png");
    mode2_pb->setParent(this);
    mode2_pb->move(this->width()*0.5-mode2_pb->width()*0.5, this->height()*0.35);
    connect(mode2_pb, &pushbutton::clicked, mode2_pb, &pushbutton::on_pushbutton_clicked);

    pushbutton *modeexit_pb = new pushbutton("../picture/quit.png");
    modeexit_pb->setParent(this);
    modeexit_pb->move(this->width()*0.5-modeexit_pb->width()*0.5, this->height()*0.45);
    connect(modeexit_pb, &pushbutton::clicked, modeexit_pb, &pushbutton::on_pushbutton_clicked);
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

