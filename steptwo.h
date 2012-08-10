#ifndef STEPTWO_H
#define STEPTWO_H

#include <QtGui>
#include <vector>
#include "score.h"
#include "round.h"

class Match;
class MainController;

class StepTwo : public QDialog
{
    Q_OBJECT
public:
    StepTwo(Match*, int, MainController*);
    Score* getScore(Match*, bool);
    QString* getBeatmap();
    bool* getMods();
    int getRoundNo();
signals:
    void nextStep(StepTwo*);
public slots:
    void setDoubleTime(bool);
    void setNightCore(bool);
    void advance();
private:
    int roundNo;
    QLabel *chooserName;
    QLineEdit *bmArtist;
    QLineEdit *bmName;
    QLineEdit *bmDifficulty;
    QCheckBox *hr;
    QCheckBox *dt;
    QCheckBox *nc;
    QCheckBox *sd;
    QCheckBox *hd;
    QCheckBox *fl;
    QSpinBox *score[2];
    QDoubleSpinBox *accuracy[2];
    QSpinBox *combo[2];
    QCheckBox *fail[2];
    QPushButton *next;
    QPushButton *cancel;
};

#endif // STEPTWO_H
