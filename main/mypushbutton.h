#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(const QString &inputpath, const QString &modeinfo);
    void zoomIn();
    void zoomOut();

private:
    QString inputImgPath;
    QString buttonModeInfo;
signals:

};

#endif // MYPUSHBUTTON_H
