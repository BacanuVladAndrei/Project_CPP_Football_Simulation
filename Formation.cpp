#include <iostream>
#include "Formation.h"
using namespace std;

Formation::Formation()
{
    this->def = 0;
    this->mid = 0;
    this->fwd = 0;
}

Formation::Formation(const int d, const int m, const int f)
{
    this->def = d;
    this->mid = m;
    this->fwd = f;
}

void Formation::set(const int d, const int m, const int f)
{
    this->def = d;
    this->mid = m;
    this->fwd = f;
}

int Formation::getD() const
{
    return this->def;
}

int Formation::getM() const
{
    return this->mid;
}

int Formation::getF() const
{
    return this->fwd;
}

bool Formation::check(int def_lwr, int def_upr, int mid_lwr, int mid_upr, int fwd_lwr, int fwd_upr) const
{
    if(def_lwr < 0)
    {
        def_lwr = 0;
    }
    if(mid_lwr < 0)
    {
        mid_lwr = 0;
    }
    if(fwd_lwr < 0)
    {
        fwd_lwr = 0;
    }

    if(def_lwr > def_upr)
    {
        def_upr = def_lwr;
    }
    if(mid_lwr > mid_upr)
    {
        mid_upr = mid_lwr;
    }
    if(fwd_lwr > fwd_upr)
    {
        fwd_upr = fwd_lwr;
    }

    if(this->def < def_lwr || this->def > def_upr)
    {
        return 0;
    }
    if(this->mid < mid_lwr || this->mid > mid_upr)
    {
        return 0;
    }
    if(this->fwd < fwd_lwr || this->fwd > fwd_upr)
    {
        return 0;
    }

    if(this->def + this->mid + this->fwd != 10)
    {
        return 0;
    }

    return 1;
}

istream& operator>>(istream& devi, Formation& form)
{
    cout << "D: ";
    devi >> form.def;
    getchar();
    cout << "M: ";
    devi >> form.mid;
    getchar();
    cout << "F: ";
    devi >> form.fwd;
    getchar();

    return devi;
}

void Formation::computeFormation(vector<Player*> players, int count)
{
    this->def = 0;
    this->mid = 0;
    this->fwd = 0;

    for(int i = 0; i < count; i++)
    {
        switch(players[i]->getPos()){
            case 'D':
            {
                this->def++;
                break;
            }
            case 'M':
            {
                this->mid++;
                break;
            }
            case 'F':
            {
                this->fwd++;
                break;
            }
            default:
                break;
        }
    }
}

ostream& operator<<(ostream& devo, const Formation& form)
{
    devo << form.def << "-" << form.mid << "-" << form.fwd;

    return devo;
}

bool Formation::err()
{
    return (this == NULL || (!this->def && !this->mid && !this->fwd));
}

void Formation::incrementPosition(char pos, int inc)
{
    switch(pos) {
        case 'D':
            this->def += inc;
            break;
        case 'M':
            this->mid += inc;
            break;
        case 'F':
            this->fwd += inc;
            break;
        default:
            break;
    }
}