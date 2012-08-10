#ifndef STEPONE_H
#define STEPONE_H

#include <QtGui>
#include "player.h"

class MainController;
class StepOne : public QDialog
{
    Q_OBJECT
public:
    StepOne(MainController*);
    Player* getPlayer(bool);
    int getMatchNo();
    QString* getReferee();
signals:
    void nextStep(StepOne*);
public slots:
    void advance();
private:
    QSpinBox *gameNo;
    QSpinBox *spot[2];
    QLineEdit *tag[3];
    QLineEdit *name[3];
    QPushButton *next;
    QPushButton *cancel;

};

#endif // STEPONE_H
