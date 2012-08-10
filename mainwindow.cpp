#include "mainwindow.h"
#include "stepone.h"
#include "maincontroller.h"
#include <sstream>

MainWindow::MainWindow(MainController *controller) : QWidget()
{
    setWindowTitle("iReport SSE");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    gameStatus = new QLabel("Match en attente d'initialisation");
    mainLayout->addWidget(gameStatus, 0, Qt::AlignRight);
    //QHBoxLayout *rounds[7];
    QGridLayout *rounds = new QGridLayout;
    QLabel *roundNo = new QLabel("No.");
    QLabel *chosenBy = new QLabel("Choisie par");
    QLabel *beatmap = new QLabel("Beatmap");
    QLabel *wonBy = new QLabel("Remportée par");

    rounds->addWidget(roundNo, 0, 0);
    rounds->addWidget(chosenBy, 0, 1);
    rounds->addWidget(beatmap, 0, 2);
    rounds->addWidget(wonBy, 0, 3);

    for (int i = 0 ; i < 7 ; i++)
    {
        std::ostringstream os;
        os << "<strong>" << i + 1 << "</strong> :";
        QLabel *roundNumber = new QLabel(os.str().c_str());
        roundChosenBy[i] = new QLabel("<span style=\"font:bold;color:grey;\">N/A</span>");
        roundBeatmap[i] = new QLineEdit;
        roundBeatmap[i]->setReadOnly(true);
        roundBeatmap[i]->setEnabled(false);
        roundWonBy[i] = new QLabel("<span style=\"font:bold;color:grey;\">N/A</span>");

        rounds->addWidget(roundNumber, i+1, 0);
        rounds->addWidget(roundChosenBy[i], i+1, 1);
        rounds->addWidget(roundBeatmap[i], i+1, 2);
        rounds->addWidget(roundWonBy[i], i+1, 3);
    }
    mainLayout->addLayout(rounds);
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    newGame = new QPushButton("Nouveau match");
    connect(newGame, SIGNAL(pressed()), controller, SLOT(newGame()));
    getReport = new QPushButton("Générer le rapport");
    connect(getReport, SIGNAL(pressed()), controller, SLOT(makeReport()));
    getReport->setEnabled(false);
    reset = new QPushButton("Réinitialiser");
    reset->setEnabled(false);
    buttonsLayout->addWidget(getReport);
    buttonsLayout->addWidget(newGame);
    buttonsLayout->addWidget(reset);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

}

void MainWindow::refreshOpponents(Match *m)
{
    std::ostringstream os;
    os << "iReport SSE : " << m->getPlayerA()->getFullName()->toStdString() << " vs " << m->getPlayerB()->getFullName()->toStdString();
    setWindowTitle(os.str().c_str());
    os.str("");
    os << m->getPlayerA()->getHTML()->toStdString() << " vs " << m->getPlayerB()->getHTML()->toStdString();
    gameStatus->setText(QString(os.str().c_str()));
}

void MainWindow::addRound(Round *r)
{
    int i = r->getRank() - 1;
    roundChosenBy[i]->setText(r->getChosenBy()->getShortHTML(true)->toStdString().c_str());
    roundBeatmap[i]->setEnabled(true);
    roundBeatmap[i]->setText(r->getBeatmap()->toStdString().c_str());
    roundWonBy[i]->setText(r->getWinner()->getShortHTML(true)->toStdString().c_str());
}

void MainWindow::finish()
{
    newGame->setEnabled(false);
    getReport->setEnabled(true);
    reset->setEnabled(true);
}
