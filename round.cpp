#include "round.h"

Round::Round(int r, QString *bm, bool m[6])
{
    rank = r;
    beatmap = bm;
    hr = m[0];
    sd = m[1];
    dt = m[2];
    nc = m[3];
    hd = m[4];
    fl = m[5];
    set = true;
}
Round::Round()
{
    set = false;
}

int Round::getRank()
{
    return rank;
}

Player* Round::getWinner()
{
    if (playerA->isFailed() && playerA->getPlayer() == getChosenBy())
        return playerB->getPlayer();
    else if (playerB->isFailed() && playerB->getPlayer() == getChosenBy())
        return playerA->getPlayer();
    else if (playerA->isFailed() != playerB->isFailed())
        return (playerA->isFailed() ? playerB->getPlayer() : playerA->getPlayer());
    else if ((playerA->getValue() == playerB->getValue()) && playerA->getPlayer() == getChosenBy())
        return playerB->getPlayer();
    else if ((playerA->getValue() == playerB->getValue()) && playerB->getPlayer() == getChosenBy())
        return playerA->getPlayer();
    else
        return (playerA->getValue() > playerB->getValue() ? playerA->getPlayer() : playerB->getPlayer());
}

Score* Round::getScoreA()
{
    return playerA;
}

Score* Round::getScoreB()
{
    return playerB;
}

void Round::setScoreA(Score *s)
{
    playerA = s;
}

void Round::setScoreB(Score *s)
{
    playerB = s;
}

QString* Round::getBeatmap()
{
    return beatmap;
}

Player* Round::getChosenBy()
{
    switch(rank)
    {
    case 1:
    case 2:
    case 6:
    case 7:
        return playerA->getPlayer();
        break;
    default:
        return playerB->getPlayer();
    }
}

bool Round::isSet()
{
    return set;
}

bool* Round::getMods()
{
    bool t[] = { hr, sd, dt, nc, hd, fl };
    return t;
}
