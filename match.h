#ifndef MATCH_H
#define MATCH_H
#include "round.h"
#include "player.h"
#include "steptwo.h"
#include <QtGui>

class Match
{
public:
    Match(int);
    void setPlayerA(Player*);
    Player* getPlayerA();
    void setPlayerB(Player*);
    Player* getPlayerB();
    void setReferee(QString*);
    QString* getReferee();
    void addRound(Round*);
    Round** getRounds();
    Player* getChooser(int);
    bool isOver();
    int getMatchNo();
    int countLosses();
    Player* getWinner();
private:
    int matchNo;
    QString *referee;
    Player *playerA;
    Player *playerB;
    Round *rounds[7];
};

#endif // MATCH_H
