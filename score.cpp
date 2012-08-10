#include "score.h"

Score::Score(Player *p, int s, double a, int c, bool f)
{
    player = p;
    value = s;
    accuracy = a;
    combo = c;
    fail = f;
}

bool Score::isFailed()
{
    return fail;
}

int Score::getValue()
{
    return value;
}

Player* Score::getPlayer()
{
    return player;
}

int Score::getCombo()
{
    return combo;
}

double Score::getAccuracy()
{
    return accuracy;
}
