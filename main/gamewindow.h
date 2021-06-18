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
    // buttons when playing games
    QPushButton* passButton;
    QPushButton* playButton;
    QPushButton* betNoButton;
    QPushButton* bet1Button;
    QPushButton* bet2Button;
    QPushButton* bet3Button;

public slots:

signals:

};

#endif // GAMEWINDOW_H
