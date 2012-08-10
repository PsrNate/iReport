#ifndef PLAYER_H
#define PLAYER_H
#include <QtGui>

class Player
{
public:
    Player(QString*, int, bool);
    QString* getName();
    QString* getSpot();
    int getNumeralSpot();
    QString* getFullName();
    QString* getHTML();
    QString* getShortHTML(bool);
    QString* getShortBBCode(bool);
private:
    QString *name;
    int spot;
    bool leads;
};

#endif // PLAYER_H
