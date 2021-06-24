#include "gamewindow.h"

#include <QPainter>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1200,800);
    setWindowTitle("Landlord: Welcome!");
    setWindowIcon(QIcon("../picture/icon.jfif"));
}


void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/game_scene.PNG");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
