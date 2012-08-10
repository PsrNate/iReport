#include "reportgenerator.h"
#include "match.h"
#include <sstream>

ReportGenerator::ReportGenerator(Match *g)
{
    game = g;
}

QString* ReportGenerator::getReport()
{
    std::ostringstream os;
    std::string ac("#A51C30");
    std:: string bc("#003399");

    // En-tête
    os << "[b][i][u]Match no. " << game->getMatchNo() << "[/u][/i][/b] : ";

    os << "[color=" << ac << "][b]" << game->getPlayerA()->getName()->toStdString() << "[/b] ";
    os << "(" << game->getPlayerA()->getSpot()->toStdString() << ")[/color]";
    os << " vs ";
    os << "[color=" << bc << "][b]" << game->getPlayerB()->getName()->toStdString() << "[/b] ";
    os << "(" << game->getPlayerB()->getSpot()->toStdString() << ")[/color]" << "\n";
    os << "[b][i][u]Arbitré par[/u][/i][/b] : " << game->getReferee()->toStdString();

    os << "\n\n";

    // Rounds
    Round **rounds = game->getRounds();
    QLocale locale(QLocale::French, QLocale::France);
    for (int i = 0 ; i < 7 ; i++)
    {
        if (!rounds[i]->isSet())
            break;

        os << "[b][i][u]Manche no. " << rounds[i]->getRank() << "[/u][/i][/b] : ";
        os << rounds[i]->getBeatmap()->toStdString() << "\n";
        os << "[b][i][u]Choisie par[/u][/i][/b] : " << rounds[i]->getChosenBy()->getShortBBCode(true)->toStdString() << "\n";
        os << "[b][i][u]Remportée par[/u][/i][/b] : " << rounds[i]->getWinner()->getShortBBCode(true)->toStdString() << "\n";
        os << "[b][i][u]Mods[/u][/i][/b] : " << getMods(rounds[i]) << "\n";

        os << "\n";

        os << "[table][row][header]Nom[/header][header]Score[/header][header]Précision[/header][header]Combo Max[/header][/row]";
        if (rounds[i]->getWinner()->getNumeralSpot() == game->getPlayerA()->getNumeralSpot())
        {
            os << "[row][cell][b][color=" << ac << "]" << game->getPlayerA()->getName()->toStdString() << "[/color][/b][/cell]";
            os << "[cell][b][color=" << ac << "]" << locale.toString(rounds[i]->getScoreA()->getValue()).toStdString();
            if (rounds[i]->getScoreA()->isFailed())
                os << "[/color][color=red] [FAIL]";
            os << "[/color][/b][/cell]";
            os << "[cell][b][color=" << ac << "]" << rounds[i]->getScoreA()->getAccuracy() << "%[/color][/b][/cell]";
            os << "[cell][b][color=" << ac << "]" << rounds[i]->getScoreA()->getCombo() << "[/color][/b][/cell][/row]";

            os << "[row][cell][color=" << bc << "]" << game->getPlayerB()->getName()->toStdString() << "[/color][/cell]";
            os << "[cell][color=" << bc << "]" << locale.toString(rounds[i]->getScoreB()->getValue()).toStdString();
            if (rounds[i]->getScoreB()->isFailed())
                os << "[/color][color=red][b] [FAIL][/b]";
            os << "[/color][/cell]";
            os << "[cell][color=" << bc << "]" << rounds[i]->getScoreB()->getAccuracy() << "%[/color][/cell]";
            os << "[cell][color=" << bc << "]" << rounds[i]->getScoreB()->getCombo() << "[/color][/cell][/row]";
        }
        else
        {
            os << "[row][cell][b][color=" << bc << "]" << game->getPlayerB()->getName()->toStdString() << "[/color][/b][/cell]";
            os << "[cell][b][color=" << bc << "]" << locale.toString(rounds[i]->getScoreB()->getValue()).toStdString();
            if (rounds[i]->getScoreB()->isFailed())
                os << "[/color][color=red] [FAIL]";
            os << "[/color][/b][/cell]";
            os << "[cell][b][color=" << bc << "]" << rounds[i]->getScoreB()->getAccuracy() << "%[/color][/b][/cell]";
            os << "[cell][b][color=" << bc << "]" << rounds[i]->getScoreB()->getCombo() << "[/color][/b][/cell][/row]";

            os << "[row][cell][color=" << ac << "]" << game->getPlayerA()->getName()->toStdString() << "[/color][/cell]";
            os << "[cell][color=" << ac << "]" << locale.toString(rounds[i]->getScoreA()->getValue()).toStdString();
            if (rounds[i]->getScoreB()->isFailed())
                os << "[/color][color=red][b] [FAIL][/b]";
            os << "[/color][/cell]";
            os << "[cell][color=" << ac << "]" << rounds[i]->getScoreA()->getAccuracy() << "%[/color][/cell]";
            os << "[cell][color=" << ac << "]" << rounds[i]->getScoreA()->getCombo() << "[/color][/cell][/row]";
        }
        os << "[/table]" << "\n" << "\n";
    }

    // Résultat
    if (game->getWinner()->getNumeralSpot() == game->getPlayerA()->getNumeralSpot())
    {
        os << "[b][color=" << ac << "]" << game->getPlayerA()->getName()->toStdString() << " 4[/b][/color]";
        os << " - ";
        os << "[color=" << bc << "]" << game->countLosses() << " " << game->getPlayerB()->getName()->toStdString() << "[/color]";
    }
    else
    {
        os << "[color=" << ac << "]" << game->getPlayerA()->getName()->toStdString() << " " << game->countLosses() << "[/color]";
        os << " - ";
        os << "[b][color=" << bc << "]4 " << game->getPlayerB()->getName()->toStdString() << "[/color][/b]";
    }
    return new QString(os.str().c_str());
}

std::string ReportGenerator::getMods(Round *r)
{
    std::ostringstream os;
    bool* m = r->getMods();
    bool trigger = false;
    bool first = true;

    os << getMod(m[0], &trigger, &first, "Hard Rock");
    os << getMod(m[1], &trigger, &first, "Sudden Death");
    os << getMod(m[2], &trigger, &first, "Double Time");
    os << getMod(m[3], &trigger, &first, "Nightcore");
    os << getMod(m[4], &trigger, &first, "Hidden");
    os << getMod(m[4], &trigger, &first, "Flashlight");

    return trigger ? os.str() : std::string("Aucun");
}

std::string ReportGenerator::getMod(bool mod, bool *trigger, bool *first, std::string name)
{
    if (!mod)
        return std::string("");
    else
    {
        *trigger = false;
        if (*first)
        {
            *first = false;
            return name;
        }
        else
            return std::string(", ") + name;
    }
}
