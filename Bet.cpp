#include <iostream>
#include <iomanip>
#include <fstream>
#include "Betting_Application.h"
using namespace std;

Bet::Bet()
{
    this->status = false;
}

Bet::Bet(const Odd& o, bool status)
{
    this->o = o;
    this->status = status;
}

Bet::Bet(double o, bool status)
{
    this->o.set(o);
    this->status = status;
}

Bet::Bet(const Bet& bet)
{
    this->o = bet.o;
    this->status = bet.status;
}

Bet& Bet::operator=(const Bet& bet)
{
    this->o = bet.o;
    this->status = bet.status;
    return *this;
}

Odd Bet::getOdd() const
{
    return this->o;
}

void Bet::setOdd(const Odd& odd)
{
    this->o = odd;
}

bool Bet::getStatus() const
{
    return this->status;
}

void Bet::setStatus(bool new_status)
{
    this->status = new_status;
}

ostream& operator<<(ostream& devo, const Bet& bet)
{
    devo << "Odd: " << bet.o << endl;
    devo << "Status: " << (bet.status ? "Winner" : "Loser") << endl;
    return devo;
}

fstream& operator<<(fstream& stro, const Bet& bet)
{
    stro << "Odd: " << bet.o << endl;
    stro << "Status: " << (bet.status ? "Winner" : "Loser") << endl;
    return stro;
}

