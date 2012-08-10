#ifndef SCORE_H
#define SCORE_H

#include "player.h"

class Score
{
public:
    Score(Player*, int, double, int, bool);
    bool isFailed();
    int getValue();
    Player* getPlayer();
    double getAccuracy();
    int getCombo();
private:
    Player *player;
    int value;
    double accuracy;
    int combo;
    bool fail;
};

#endif // SCORE_H
