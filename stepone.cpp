#include "stepone.h"
#include "maincontroller.h"
#include "player.h"
#include <math.h>
#include <sstream>

StepOne::StepOne(MainController *controller) : QDialog()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(new QLabel("Match no. : "), 0, 0);
    gameNo = new QSpinBox;
    gameNo->setMinimum(1);
    mainLayout->addWidget(gameNo, 0, 1);
    mainLayout->addWidget(new QLabel("<span style=\"color:grey;font:italic\">(Se référer au bracket)</span>"), 0, 2);
    mainLayout->addWidget(new QLabel("Tag <span style=\"font:italic;color:grey;\">(Facultatif)</span>"), 1, 1);
    mainLayout->addWidget(new QLabel("Nom"), 1, 2);
    mainLayout->addWidget(new QLabel("Spot"), 1, 3);
    mainLayout->addWidget(new QLabel("Joueurs : "), 2, 0);
    mainLayout->addWidget(new QLabel("Arbitre :"), 4, 0);
    for (int i = 0 ; i < 3 ; i++)
    {
        tag[i] = new QLineEdit;
        mainLayout->addWidget(tag[i], i+2, 1);
        name[i] = new QLineEdit;
        mainLayout->addWidget(name[i], i+2, 2);
        if (i < 2)
        {
            spot[i] = new QSpinBox;
            spot[i]->setPrefix("No. ");
            spot[i]->setMinimum(1);
            mainLayout->addWidget(spot[i], i+2, 3);
        }
    }
    next = new QPushButton("Suivant");
    connect(next, SIGNAL(pressed()), this, SLOT(advance()));
    connect(this, SIGNAL(nextStep(StepOne*)), controller, SLOT(addOpponents(StepOne*)));
    cancel = new QPushButton("Annuler");
    mainLayout->addWidget(next, 5, 2);
    mainLayout->addWidget(cancel, 5, 3);
    setLayout(mainLayout);
}

void StepOne::advance()
{
    emit nextStep(this);
}

Player* StepOne::getPlayer(bool a)
{
    if (spot[0]->value() == spot[1]->value())
    {
        throw std::string("Les spots des deux joueurs ne peuvent pas être égaux !");
    }
    else if (name[0]->text().isEmpty() || name[1]->text().isEmpty())
    {
        throw std::string("Les noms des joueurs ne sont pas renseignés !");
    }

    int i = (a == (spot[0]->value() - spot[1]->value() > 0)) ? 1 : 0;

    QString *n;
    if (tag[i]->text() == "")
        n = new QString(name[i]->text());
    else
        n = new QString("[" + tag[i]->text() + "]_" + name[i]->text());

    return new Player(n, spot[i]->value(), a);
}

int StepOne::getMatchNo()
{
    return gameNo->value();
}

QString* StepOne::getReferee()
{
    if (name[2]->text().isEmpty())
        throw std::string("Le nom de l'arbitre n'est pas renseigné !");
    if (tag[2]->text().isEmpty())
        return new QString(name[2]->text());
    else
        return new QString("[" + tag[2]->text() + "]_" + name[2]->text());
}
