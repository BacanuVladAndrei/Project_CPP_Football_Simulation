#include <iostream>
#include <iomanip>
#include <fstream>
#include "Betting_Application.h"
#include "Administrative_functions.h"
using namespace std;

Bet_1X2::Bet_1X2()
{
    this->home_wins = false;
    this->draw = false;
    this->away_wins = false;
}

Bet_1X2::Bet_1X2(bool home_wins, bool draw, bool away_wins)
{
    this->home_wins = home_wins;
    this->away_wins = away_wins;
    this->draw = draw;
}

void Bet_1X2::read()
{
    cout << "Bet: ";
    char opt1 = option("1Xx2", NULL);
    this->draw = (opt1 == 'X' || opt1 == 'x');
    this->home_wins = (opt1 == '1');
    this->away_wins = (opt1 == '2');

    char opt2 = option("1Xx2\n", NULL);
    if(opt2 == '1')
    {
        this->home_wins = 1;
    }
    else
    {
        if(opt2 == '2')
        {
            this->away_wins = 1;
        }
        else
        {
            if(opt2 == 'X' || opt2 == 'x')
            {
                this->draw = 1;
            }
        }
    }
}

void Bet_1X2::print(bool disp_status)
{
    cout << "Description: ";
    if(this->home_wins && !this->away_wins && !this->draw)
    {
        cout << "Home wins" << endl;
    }
    if(this->home_wins && this->away_wins && !this->draw)
    {
        cout << "Home or away wins" << endl;
    }
    if(this->home_wins && !this->away_wins && this->draw)
    {
        cout << "Home wins or draw" << endl;
    }
    if(!this->home_wins && this->away_wins && !this->draw)
    {
        cout << "Away wins" << endl;
    }
    if(!this->home_wins && this->away_wins && this->draw)
    {
        cout << "Away wins or draw" << endl;
    }
    if(!this->home_wins && !this->away_wins && this->draw)
    {
        cout << "Draw" << endl;
    }
    if(disp_status)
    {
        this->Bet::print();
    }
    else
    {
        cout << "Odd: " << this->o << endl;
    }
}

void Bet_1X2::write(fstream& stro, bool disp_status)
{
    stro << "Description: ";
    if(this->home_wins && !this->away_wins && !this->draw)
    {
        stro << "Home wins" << endl;
    }
    if(this->home_wins && this->away_wins && !this->draw)
    {
        stro << "Home or away wins" << endl;
    }
    if(this->home_wins && !this->away_wins && this->draw)
    {
        stro << "Home wins or draw" << endl;
    }
    if(!this->home_wins && this->away_wins && !this->draw)
    {
        stro << "Away wins" << endl;
    }
    if(!this->home_wins && this->away_wins && this->draw)
    {
        stro << "Away wins or draw" << endl;
    }
    if(!this->home_wins && !this->away_wins && this->draw)
    {
        stro << "Draw" << endl;
    }
    if(disp_status)
    {
        this->Bet::write(stro);
    }
    else
    {
        stro << "Odd: " << this->o << endl;
    }
}

bool Bet_1X2::Check(const Team& home, const Team& away)
{
    if(home.getGoals() == away.getGoals())
    {
        this->status = this->draw;
    }
    else
    {
        if(home.getGoals() > away.getGoals())
        {
            this->status = this->home_wins;
        }
        else
        {
            this->status = this->away_wins;
        }
    }
    return this->status;
}