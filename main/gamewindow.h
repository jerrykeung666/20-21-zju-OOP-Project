#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "gamecontrol.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

private:
    MyPushButton* startBtn;

    GameControl *gameControl;
signals:

};

#endif // GAMEWINDOW_H
