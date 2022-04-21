#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "Referee.h"
#include "Administrative_functions.h"
using namespace std;

Referee::Referee()
{
    rat = 0;
    nat = NULL;
    main = false;
    ass = false;
    var = false;
}

Referee::Referee(string name, const int &rat, Country *nat, const int &roles)
{
    this->name = name;
    this->rat = rat;
    this->nat = nat;
    int r = roles % 1000;
    main = r / 100;
    ass = (r / 10) % 10;
    var = r % 10;
}

Referee::Referee(const Referee &ref)
{
    this->name = ref.name;
    this->rat = ref.rat;
    this->nat = ref.nat;
    this->main = ref.main;
    this->ass = ref.ass;
    this->var = ref.var;
}

Referee& Referee::operator=(const Referee &ref)
{
    this->name = ref.name;
    this->rat = ref.rat;
    this->nat = ref.nat;
    this->main = ref.main;
    this->ass = ref.ass;
    this->var = ref.var;

    return *this;
}

ostream& operator<<(ostream &devo, const Referee &ref)
{
    devo << ref.main << ref.ass << ref.var << " - " << ref.name << " (" << ref.nat->getCode() << ") - " << ref.rat << endl;

    return devo;
}

Referee::~Referee() {}

string Referee::getName() const
{
    return this->name;
}

bool operator==(const Referee& ref1, const Referee& ref2)
{
    return (ref1.name == ref2.name && ref1.rat == ref2.rat && *(ref1.nat) == *(ref2.nat) && ref1.main == ref2.main && ref1.ass == ref2.ass && ref1.var == ref2.var);
}

bool operator!=(const Referee& ref1, const Referee& ref2)
{
    return !(ref1 == ref2);
}

bool operator>(const Referee& ref1, const Referee& ref2)
{
    return ref1.rat > ref2.rat;
}

bool operator<(const Referee& ref1, const Referee& ref2)
{
    return ref1.rat < ref2.rat;
}

bool operator>=(const Referee& ref1, const Referee& ref2)
{
    return ref1.rat >= ref2.rat;
}

bool operator<=(const Referee& ref1, const Referee& ref2)
{
    return ref1.rat <= ref2.rat;
}

int Referee::getRating() const
{
    return this->rat;
}

Country* Referee::getNationality() const
{
    return this->nat;
}

bool Referee::isMain() const
{
    return this->main;
}

bool Referee::isAss() const
{
    return this->ass;
}

bool Referee::isVAR() const
{
    return this->var;
}

int Referee::setReferee(Countries countries, string line)
{
    // Roles
    this->main = line[0] - 48;
    this->ass = line[1] - 48;
    this->var = line[2] - 48;
    line = line.substr(4); // update

    // Nationality
    string nationality = line.substr(0, 3);
    this->nat = countries.getCountryAdd(stoi(nationality));
    if(this->nat == NULL)
    {
        return 1;
    }
    line = line.substr(4); // update

    // Rating
    string rating = line.substr(0, line.find(' '));
    this->rat = stoi(rating);
    line = line.substr(line.find(' ') + 1); // update

    // Name
    this->name = line;

    return 0;
}

int Referee::setReferee(string name, Country* nationality, const int& roles, int rating)
{
    if(nationality == NULL)
    {
        return 1;
    }

    this->name = name;
    this->nat = nationality;
    this->main = roles / 100;
    this->ass = (roles / 10) % 10;
    this->var = roles % 10;

    return 0;
}

Referee* getReferees(Countries countries, int &count)
{
    fstream referees;
    referees.open("referees.txt", ios::in);
    Referee *refs = NULL;
    if(referees.is_open())
    {
        string line;
        while(getline(referees, line))
        {
            refs = Resize(refs, count, count + 1);
            refs[count].setReferee(countries, line.c_str());
            count++;
        }
        referees.close();
        return refs;
    }
    else
    {
        return NULL;
    }
    return NULL;
}

Referee getReferee(Referee *referees, const int &count, string name)
{
    for(int i=0; i<count; i++)
    {
        if(referees[i].name == name)
        {
            return referees[i];
        }
    }
    Referee ref_err;
    return ref_err;
}

Referee* getRefereeadd(Referee *referees, const int &count, string name)
{
    for(int i=0; i<count; i++)
    {
        if(referees[i].name == name)
        {
            return &(referees[i]);
        }
    }
    return NULL;
}

bool Referee::err() const
{
    return (this == NULL || (this->name.length() == 0 && this->rat == 0 && this->nat == NULL && this->main == false && this->ass == false && this->var == false));
}