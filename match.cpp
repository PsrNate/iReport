#include "match.h"
#include "steptwo.h"
#include "round.h"
#include <stddef.h>
#include <sstream>

Match::Match(int i)
{
    matchNo = i;
    for (int j = 0 ; j < 7 ; j++)
    {
        rounds[j] = new Round();
    }

}

void Match::setPlayerA(Player *p)
{
    playerA = p;
}
Player* Match::getPlayerA()
{
    return playerA;
}

void Match::setPlayerB(Player *p)
{
    playerB = p;
}
Player* Match::getPlayerB()
{
    return playerB;
}
void Match::setReferee(QString *r)
{
    referee = r;
}
QString* Match::getReferee()
{
    return referee;
}
void Match::addRound(Round *r)
{
    rounds[r->getRank()-1] = r;
}

Round** Match::getRounds()
{
    return rounds;
}

Player* Match::getChooser(int roundNumber)
{
    switch(roundNumber)
    {
    case 1:
    case 2:
    case 6:
    case 7:
        return getPlayerA();
        break;
    default:
        return getPlayerB();
    }
}

bool Match::isOver()
{
    int a = 0, b = 0, i = 0;

    while (rounds[i]->isSet())
    {
        if (rounds[i]->getWinner()->getNumeralSpot() == playerA->getNumeralSpot())
            a++;
        else
            b++;
        i++;
        if (rounds[i]->getRank() == 7)
            return true;
    }
    return a == 4 || b == 4;
}

int Match::getMatchNo()
{
    return matchNo;
}

int Match::countLosses()
{
    int a = 0, b = 0, i = 0;

    while (rounds[i]->isSet())
    {
        if (rounds[i]->getWinner()->getNumeralSpot() == playerA->getNumeralSpot())
            a++;
        else
            b++;
        i++;
        if (rounds[i]->getRank() == 7)
            return 3;
    }
    return (a == 4 ? b : a);
}

Player* Match::getWinner()
{
    int a = 0, b = 0, i = 0;

    while (rounds[i]->isSet())
    {
        if (rounds[i]->getWinner()->getNumeralSpot() == playerA->getNumeralSpot())
            a++;
        else
            b++;
        i++;
    }
    return (a == 4 ? playerA : playerB);
}
