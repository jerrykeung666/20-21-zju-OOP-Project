#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamewindow.h"
#include "gamecontrol.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Rewrite Event
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    GameWindow *gameWindow;


// Updated
public slots:
    //void enableMainWindow(settingWindow* ptr);
    //void disableMainWindow(settingWindow* ptr);
};

#endif // MAINWINDOW_H
