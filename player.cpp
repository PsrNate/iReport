#include "player.h"
#include <sstream>

Player::Player(QString *n, int s, bool i)
{
    name = n;
    spot = s;
    leads = i;
}

QString* Player::getName()
{
    return name;
}

QString* Player::getSpot()
{
    std::ostringstream os;
    os << "No. " << spot;
    return new QString(os.str().c_str());
}

QString* Player::getFullName()
{
    std::ostringstream os;
    os << getName()->toStdString() << " (" << getSpot()->toStdString() << ")";
    return new QString(os.str().c_str());
}

QString* Player::getHTML()
{
    std::ostringstream os;
    std::string color = (leads ? "#A51C30" : "#003399");
    os << "<span style=\"color:" << color << ";\"><strong>" << getName()->toStdString() << "</strong> (" << getSpot()->toStdString() << ")</span>";
    return new QString(os.str().c_str());
}

QString* Player::getShortHTML(bool bold)
{
    std::ostringstream os;
    std::string color = (leads ? "#A51C30" : "#003399");
    if (bold)
        os << "<span style=\"color:" << color << ";font:bold;\">" << getName()->toStdString() << "</span>";
    else
        os << "<span style=\"color:" << color << ";\">" << getName()->toStdString() << "</span>";
    return new QString(os.str().c_str());
}

QString* Player::getShortBBCode(bool bold)
{
    std::ostringstream os;
    std::string color = (leads ? "#A51C30" : "#003399");
    if (bold)
        os << "[color=" << color << "][b]" << getName()->toStdString() << "[/b][/color]";
    else
        os << "[color=" << color << "]" << getName()->toStdString() << "[/color]";
    return new QString(os.str().c_str());
}

int Player::getNumeralSpot()
{
    return spot;
}
