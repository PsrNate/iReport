#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "match.h"

class ReportGenerator
{
public:
    ReportGenerator(Match*);
    QString* getReport();
    std::string getMods(Round *round);
    std::string getMod(bool, bool*, bool*, std::string);
private:
    Match *game;
};

#endif // REPORTGENERATOR_H
