#include <iostream>
#include <string>
#include "Referee.h"
#pragma once
using namespace std;

class Referees {
    protected:
        Referee mainRef;
        Referee ass1Ref;
        Referee ass2Ref;
        Referee sideRef;
        Referee var1Ref;
        Referee var2Ref;

    public:
        Referees();
        Referees(Referee, Referee, Referee, Referee, Referee, Referee);

        void printReferees() const;

        inline Referee getMain() const { return this->mainRef; };
        inline Referee getAss1() const { return this->ass1Ref; };
        inline Referee getAss2() const { return this->ass2Ref; };
        inline Referee getSide() const { return this->sideRef; };
        inline Referee getVAR1() const { return this->var1Ref; };
        inline Referee getVAR2() const { return this->var2Ref; };

        inline void setMain(Referee new_ref) { this->mainRef = new_ref; };
        inline void setAss1(Referee new_ref) { this->ass1Ref = new_ref; };
        inline void setAss2(Referee new_ref) { this->ass2Ref = new_ref; };
        inline void setSide(Referee new_ref) { this->sideRef = new_ref; };
        inline void setVAR1(Referee new_ref) { this->var1Ref = new_ref; };
        inline void setVAR2(Referee new_ref) { this->var2Ref = new_ref; };

        friend bool validNationality(Country*, const int&, const int&);

        int readReferees(Countries, const int&, const int&);
        int autoReferees(Countries, const int&, const int&);
        int findReferees(Countries, Country*, Country*);
        int decideCountries(Countries, const int&, const int&, Country&, Country&) const;

        int getReferees(Countries, const int&, const int&);
        bool editReferees(Countries, const char);
};