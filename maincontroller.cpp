#include "maincontroller.h"
#include "stepone.h"
#include "steptwo.h"
#include "mainwindow.h"
#include "reportgenerator.h"
#include "resultwindow.h"

MainController::MainController() : QObject()
{
    mw = new MainWindow(this);
    mw->show();
}

void MainController::newGame()
{
    // Step one
    StepOne window(this);
    window.exec();
}

void MainController::addOpponents(StepOne *window)
{
    try
    {
        game = new Match(window->getMatchNo());
        // Convert using constructor
        game->setPlayerA(window->getPlayer(true));
        game->setPlayerB(window->getPlayer(false));
        game->setReferee(window->getReferee());
        mw->refreshOpponents(game);
        window->close();
        StepTwo swindow(game, 1, this);
        swindow.exec();

    }
    catch(std::string ex)
    {
        QMessageBox::critical(window, "Erreur : information manquante", QString(ex.c_str()));
    }
}

void MainController::addRound(StepTwo *window)
{
    try
    {
        Round *r = new Round(window->getRoundNo(), window->getBeatmap(), window->getMods());
        game->addRound(r);
        r->setScoreA(window->getScore(game, true));
        r->setScoreB(window->getScore(game, false));
        mw->addRound(r);
        if(game->isOver())
        {
            window->close();
            mw->finish();
        }
        else
        {
            window->close();
            StepTwo swindow(game, r->getRank()+1, this);
            swindow.exec();
        }
    }
    catch(std::string ex)
    {
        QMessageBox::critical(window, "Erreur : information manquante", QString(ex.c_str()));
    }
}

void MainController::makeReport()
{
    ReportGenerator rg(game);
    ResultWindow rw(rg.getReport());
    rw.exec();
}
