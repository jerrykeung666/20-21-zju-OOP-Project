#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QMainWindow>

class pushbutton : public QPushButton
{
    Q_OBJECT
public:
    pushbutton(QString inputpath);
    void zoom_in_out();

private:
    QString inputImgPath;

//private slots:
    //void on_pushbutton_clicked();
};

#endif // PUSHBUTTON_H
