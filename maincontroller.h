#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "match.h"
#include "stepone.h"

class StepTwo;
class MainWindow;

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController();
    
signals:
    
public slots:
    void newGame();
    void addOpponents(StepOne*);
    void addRound(StepTwo*);
    void makeReport();
private:
    Match *game;
    MainWindow *mw;
};

#endif // MAINCONTROLLER_H
