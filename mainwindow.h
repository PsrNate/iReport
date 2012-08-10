#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "maincontroller.h"
#include "round.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(MainController*);
    void addRound(Round*);
    void finish();
signals:
    
public slots:
    void refreshOpponents(Match*);
private:
    QLabel *gameStatus;
    QLabel *roundWonBy[7];
    QLineEdit *roundBeatmap[7];
    QLabel *roundChosenBy[7];
    QPushButton *newGame;
    QPushButton *getReport;
    QPushButton *reset;
    
};

#endif // MAINWINDOW_H
