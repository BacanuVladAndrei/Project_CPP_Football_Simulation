#include <iostream>
#pragma once
#include "Player.h"
using namespace std;

class Formation{
    protected:
        int def;
        int mid;
        int fwd;
    
    public:
        Formation();
        Formation(const int, const int, const int);
        ~Formation() {};

        void set(const int, const int, const int);
        int getD() const;
        int getM() const;
        int getF() const;
        bool check(int, int, int, int, int, int) const;
        bool err();
        void computeFormation(vector<Player*>, int);
        void incrementPosition(char, int = 1);
        
        friend istream& operator>>(istream&, Formation&);
        friend ostream& operator<<(ostream&, const Formation&);
};