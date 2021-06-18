#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamewindow.h"

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

// Updated
public slots:
    //void enableMainWindow(settingWindow* ptr);
    //void disableMainWindow(settingWindow* ptr);
};

#endif // MAINWINDOW_H
