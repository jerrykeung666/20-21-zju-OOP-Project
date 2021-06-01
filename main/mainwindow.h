#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
};
<<<<<<< HEAD

=======
>>>>>>> ce37b4cee117b75d7dbe9cc8958b980a83a00a10
#endif // MAINWINDOW_H
