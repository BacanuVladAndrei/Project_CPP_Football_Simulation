#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "Corner.h"
#include "Administrative_functions.h"
using namespace std;

Corner::Corner()
{
    this->taker = NULL;
    this->touch = NULL;
}

Corner::Corner(int half, int min, bool team, Player* taker, Player* touch) : Event::Event(half, min, team)
{
    this->taker = taker;
    this->touch = touch;
}

int match_corners_calc(int home_m, int away_m)
{
    int nr;
    int a = rand() % 40;
    if(a < 2)
        nr = 7;
    else
        if(a < 5)
            nr = 8;
        else
            if(a < 10)
                nr = 9;
            else
                if(a < 20)
                    nr = 10;
                else
                    if(a < 30)
                        nr = 11;
                    else
                        if(a < 35)
                            nr = 12;
                        else
                            if(a < 38)
                                nr = 13;
                            else
                                nr = 14;
    nr = nr + (home_m + away_m) / 5;

    return nr;
}

int expectedCorners(const Team& home, const Team& away)
{
    return match_corners_calc(home.getMood(), away.getMood());
}

void Corner::Taker(vector<Player*> players)
{
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->cornerTakerChance();
    }

    this->taker = players[wrand(chances, players.size())];
}

void Corner::Touch(vector<Player*> players)
{
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->cornerTouchChance();
    }

    this->touch = players[wrand(chances, players.size())];
}

bool Corner::Who(const Team& home, const Team& away)
{
    int ch_h = (home.getRatingFinal() / 3 + 5 * home.getMood()) * (home.getRatingFinal() / 3 + 5 * home.getMood());
    int ch_a = (away.getRatingFinal() / 3 + 5 * away.getMood()) * (away.getRatingFinal() / 3 + 5 * away.getMood());
    if(ch_h < 1)
        ch_h = 1;
    if(ch_a < 1)
        ch_a = 1;

    return (rand() % (ch_h + ch_a) < ch_a);
}

Corner* CornerKick(Team& home, Team& away, int expected, int so_far, int min, int half, int mins_half)
{
    int mins_left;
    if(half == 1)
    {
        mins_left = mins_half - min + 45;
    }
    else
        if(half == 3)
        {
            mins_left = mins_half - min + 15;
        }
        else
        {
            mins_left = mins_half - min;
        }

    if(itHappens(expected, so_far, mins_left))
    {
        Corner* corner = new Corner;
        corner->min = min;
        corner->half = half;
        corner->team = corner->Who(home, away);
        if(corner->team)
        {
            corner->Taker(away.getPlayers());
            corner->Touch(home.getPlayers());
        }
        else
        {
            corner->Taker(home.getPlayers());
            corner->Touch(away.getPlayers());
        }
        
        return corner;
    }
    else
    {
        return NULL;
    }
}

void Corner::printList()
{
    cout << "Corner: " << this->touch->getFirstName().at(0) << ". " << this->touch->getFamilyName() << " -> " << this->taker->getFirstName().at(0) << ". " << this->taker->getFamilyName() << " ";
    this->printMinute();
    cout << "'" << endl;
}