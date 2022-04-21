#include <iostream>
#include <string>
#include "Country.h"
#pragma once
using namespace std;

class Referee {
    protected:
        string name;
        int rat;
        Country *nat; //se primeste adresa, nu se aloca dinamic
        bool main;
        bool ass;
        bool var;

    public:
        Referee();
        Referee(string, const int&, Country*, const int&);
        Referee(const Referee&);
        Referee& operator=(const Referee&);
        friend ostream& operator<<(ostream&, const Referee&);
        ~Referee();

        // Logical Operators
        friend bool operator==(const Referee&, const Referee&);
        friend bool operator!=(const Referee&, const Referee&);
        friend bool operator>(const Referee&, const Referee&);
        friend bool operator<(const Referee&, const Referee&);
        friend bool operator>=(const Referee&, const Referee&);
        friend bool operator<=(const Referee&, const Referee&);

        string getName() const;
        int getRating() const;
        Country* getNationality() const;
        bool isMain() const;
        bool isAss() const;
        bool isVAR() const;
        int setReferee(Countries, string);
        int setReferee(string, Country*, const int&, int = 1);
        bool err() const;

        friend Referee* getReferees(Countries, int&);
        friend Referee getReferee(Referee*, const int&, string);
        friend Referee* getRefereeadd(Referee*, const int&, string);
};