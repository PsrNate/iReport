#ifndef ROUND_H
#define ROUND_H
#include <QtGui>
#include "player.h"
#include "score.h"

class Round
{
public:
    Round(int, QString*, bool[6]);
    Round();
    int getRank();
    Player* getChosenBy();
    Player* getWinner();
    void setScoreA(Score*);
    void setScoreB(Score*);
    Score* getScoreA();
    Score* getScoreB();
    QString* getBeatmap();
    bool isSet();
    bool* getMods();
private:
    bool set;
    int rank;
    QString *beatmap;
    Score *playerA;
    Score *playerB;
    bool hr;
    bool sd;
    bool dt;
    bool nc;
    bool hd;
    bool fl;

};

#endif // ROUND_H
