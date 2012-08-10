#include "steptwo.h"
#include "maincontroller.h"
#include "match.h"
#include <sstream>
#include <vector>

StepTwo::StepTwo(Match *g, int r, MainController *controller) : QDialog()
{
    roundNo = r;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    std::ostringstream os;
    os << "Manche no. " << roundNo;
    setWindowTitle(os.str().c_str());
    os.str("");
    os << "Choisie par : " << g->getChooser(r)->getShortHTML(true)->toStdString();
    chooserName = new QLabel(os.str().c_str());
    mainLayout->addWidget(new QLabel(os.str().c_str()), 0, Qt::AlignLeft);

    QGridLayout *beatmapLayout = new QGridLayout;
    beatmapLayout->addWidget(new QLabel("Artiste"), 0, 0);
    beatmapLayout->addWidget(new QLabel("Titre"), 0, 1);
    beatmapLayout->addWidget(new QLabel("Difficulté"), 0, 2);
    bmArtist = new QLineEdit;
    beatmapLayout->addWidget(bmArtist, 1, 0);
    bmName = new QLineEdit;
    beatmapLayout->addWidget(bmName, 1, 1);
    bmDifficulty = new QLineEdit;
    beatmapLayout->addWidget(bmDifficulty, 1, 2);
    mainLayout->addLayout(beatmapLayout);

    QGridLayout *modsLayout = new QGridLayout;
    hr = new QCheckBox("HardRock");
    modsLayout->addWidget(hr, 0, 0);
    dt = new QCheckBox("DoubleTime");
    modsLayout->addWidget(dt, 0, 1);
    nc = new QCheckBox("Nightcore");
    modsLayout->addWidget(nc, 0, 2);
    sd = new QCheckBox("SuddenDeath");
    modsLayout->addWidget(sd, 1, 0);
    hd = new QCheckBox("Hidden");
    modsLayout->addWidget(hd, 1, 1);
    fl = new QCheckBox("FlashLight");
    modsLayout->addWidget(fl, 1, 2);
    mainLayout->addLayout(modsLayout);

    connect(nc, SIGNAL(toggled(bool)), this, SLOT(setDoubleTime(bool)));

    QGridLayout *scoreLayout = new QGridLayout;
    scoreLayout->addWidget(new QLabel("Score"), 0, 1);
    scoreLayout->addWidget(new QLabel("Précision"), 0, 2);
    scoreLayout->addWidget(new QLabel("Combo max"), 0, 3);
    scoreLayout->addWidget(new QLabel(g->getPlayerA()->getShortHTML(true)->toStdString().c_str()), 1, 0);
    scoreLayout->addWidget(new QLabel(g->getPlayerB()->getShortHTML(true)->toStdString().c_str()), 2, 0);
    for (int i = 0; i < 2; i++)
    {
        score[i] = new QSpinBox;
        score[i]->setRange(0, 999999999);
        scoreLayout->addWidget(score[i], i+1, 1);
        accuracy[i] = new QDoubleSpinBox;
        accuracy[i]->setSuffix("%");
        accuracy[i]->setRange(0.0, 100.0);
        accuracy[i]->setDecimals(2);
        scoreLayout->addWidget(accuracy[i], i+1, 2);
        combo[i] = new QSpinBox;
        combo[i]->setRange(0, 9999);
        scoreLayout->addWidget(combo[i], i+1, 3);
        fail[i] = new QCheckBox("Fail");
        scoreLayout->addWidget(fail[i], i+1, 4);
    }
    mainLayout->addLayout(scoreLayout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    next = new QPushButton("Suivant");
    buttonsLayout->addWidget(next);
    connect(next, SIGNAL(pressed()), this, SLOT(advance()));
    connect(this, SIGNAL(nextStep(StepTwo*)), controller, SLOT(addRound(StepTwo*)));
    cancel = new QPushButton("Annuler");
    buttonsLayout->addWidget(cancel);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void StepTwo::setDoubleTime(bool nc)
{
    if (nc)
        dt->setChecked(true);
}
void StepTwo::setNightCore(bool dt)
{
    if (!dt)
        nc->setChecked(false);
}

void StepTwo::advance()
{
    emit nextStep(this);
}

Score* StepTwo::getScore(Match* g, bool a)
{
    Player *p = (a ? g->getPlayerA() : g->getPlayerB());
    int i = (a ? 0 : 1);
    return new Score(p, score[i]->value(), accuracy[i]->value(), combo[i]->value(), fail[i]->isChecked());
}

QString* StepTwo::getBeatmap()
{
    if (bmArtist->text().isEmpty())
        throw std::string("Il manque l'artiste de la beatmap !");
    if (bmName->text().isEmpty())
        throw std::string("Il manque le titre de la beatmap !");
    if (bmDifficulty->text().isEmpty())
        throw std::string("Il manque la difficulté de la beatmap !");

    std::ostringstream os;
    os << bmArtist->text().toStdString() << " - " << bmName->text().toStdString() << " [" << bmDifficulty->text().toStdString() << "]";
    return new QString(os.str().c_str());
}

bool* StepTwo::getMods()
{
    bool mods[6];
    mods[0] = hr->isChecked();
    mods[1] = sd->isChecked();
    mods[2] = dt->isChecked();
    mods[3] = nc->isChecked();
    mods[4] = hd->isChecked();
    mods[5] = fl->isChecked();
    return mods;
}

int StepTwo::getRoundNo()
{
    return roundNo;
}

