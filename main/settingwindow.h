#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>

class settingWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit settingWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

private:
    QString yourName;

signals:
    void goBack();

public slots:
    void emit_goback();
};

#endif // SETTINGWINDOW_H
