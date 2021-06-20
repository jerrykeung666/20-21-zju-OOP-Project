#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "card.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void setPlayerID(int ID);
    int getPlayerID() const;

    void setHandCards(const QVector<Card>& cards);
    QVector<Card> getHandCards() const;

    void setBetPoints(int bet);
    int getBetPoints() const;

    void setIsLandLord(bool isLandLord);
    bool getIsLandLord();

    void setIsPerson(bool isPerson);
    bool getIsPerson();

    void setNextPlayer(Player *next);
    Player* getNextPlayer();

    int getCardsNumber() const;
    void addLandLordCards(const QVector<Card>& cards);
    bool isWin();

private:
    void sortHandCards();

protected:
    bool isLandLord = false;  // farmer or landlord
    bool isPerson = false;    // person or robot
    int betPoints = 0;        // the bet the player called
    int playerID;
    QVector<Card> handCards;  //
    Player *nextPlayer;
};

#endif // PLAYER_H
