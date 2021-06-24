#include <QDebug>
#include <QPushButton>
#include <QMessageBox>

#include "gamewindow.h"

const QSize GameWindow::msgBoxSize = QSize(250, 40);
const QSize GameWindow::buttonSize = QSize(80, 40);

//const QPointF GameWindow::leftMsgBoxPos = QPointF(200, 50);
//const QPointF GameWindow::rightMsgBoxPos = QPointF(200, 50);
//const QPointF GameWindow::myMsgBoxPos = QPointF(200, 50);

//const QPointF GameWindow::betNoButtonPos = QPointF(200, 50);
//const QPointF GameWindow::bet1ButtonPos = QPointF(200, 50);
//const QPointF GameWindow::bet2ButtonPos;
//const QPointF GameWindow::bet3ButtonPos;
const QPointF GameWindow::passButtonPos = QPointF(200, 50); // TO BE CHANGED

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{

}

