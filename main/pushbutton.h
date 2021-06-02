#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QMainWindow>

class pushbutton : public QPushButton
{
    Q_OBJECT
public:
    pushbutton(QString inputpath);
    //~pushbutton();
    void zoom_in_out();

private:
    QString inputImgPath;

signals:

public slots:
    void on_pushbutton_clicked();
};

#endif // PUSHBUTTON_H
