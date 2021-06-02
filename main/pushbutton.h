#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QMainWindow>

class pushbutton : public QPushButton
{
    Q_OBJECT
public:
    pushbutton(QString inputpath, QString modeinfo);
    void zoom_in();
    void zoom_out();

private:
    QString inputImgPath;
    QString buttonModeInfo;

signals:

public slots:
    void on_pushbutton_clicked();
};

#endif // PUSHBUTTON_H
