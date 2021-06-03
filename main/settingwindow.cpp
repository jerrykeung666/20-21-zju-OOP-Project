#include "settingwindow.h"

#include <QPainter>
#include <QPropertyAnimation>

settingWindow::settingWindow(QWidget *parent) : QMainWindow(parent)
{
    // set window size
    setFixedSize(1280,800);

    // set window title
    setWindowTitle("Landlord: Getting Started!");

    // set label & button for agree & refuse (last page or quit?)

}


void settingWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("../picture/background.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}


void settingWindow::emit_goback(){
    emit goBack();
}
