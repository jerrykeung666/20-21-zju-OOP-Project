#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QTimer>
#include <QPushButton>

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

private:
    // window properties
    // TODO
    static const QPointF passButtonPos;
    static const QPointF playButtonPos;
    static const QPointF betNoButtonPos;
    static const QPointF bet1ButtonPos;
    static const QPointF bet2ButtonPos;
    static const QPointF bet3ButtonPos;
    //static const

    // buttons when playing games
    QPushButton* passButton;
    QPushButton* playButton;
    QPushButton* betNoButton;
    QPushButton* bet1Button;
    QPushButton* bet2Button;
    QPushButton* bet3Button;

public slots:
    // slots for user play respose
    // TODO
    void userPass();
    void userPlay();

    // slots for user call response
    // TODO
    void userBetNo();
    void userBet1();
    void userBet2();
    void userBet3();

signals:

};

#endif // GAMEWINDOW_H
