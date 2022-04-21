#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "Offside.h"
#include "Administrative_functions.h"
using namespace std;

Offside::Offside()
{
    this->off_side = NULL;
}

Offside::Offside(int half, int min, bool team, Player* off_side) : Event::Event(half, min, team)
{
    this->off_side = off_side;
}

int offsides_per_game(int mood_h, int mood_a)
{
    int a = rand() % 36;
    int off;
    if(a < 3)
    {
        off = 0;
    }
    else
        if(a < 7)
        {
            off = 1;
        }
        else
            if(a < 13)
            {
                off = 2;
            }
            else
                if(a < 20)
                {
                    off = 3;
                }
                else
                    if(a < 30)
                    {
                        off = 4;
                    }
                    else
                        if(a < 33)
                        {
                            off = 5;
                        }
                        else
                            if(a < 35)
                            {
                                off = 6;
                            }
                            else
                            {
                                off = 7;
                            }
    off = off + (mood_h + mood_a) / 5;

    return off;
}

int min_offsides_team(int home_rat, int away_rat)
{
    int diff = fabs(home_rat - away_rat);
    int min;
    if(diff < 10)
    {
        min = 4;
    }
    else
        if(diff<20)
        {
            min = 3;
        }
        else
            if(diff < 30)
            {
                min = 2;
            }
            else
                if(diff < 40)
                {
                    min = 1;
                }
                else
                {
                    min = 0;
                }
    return min;
}

int expectedOffsides(const Team& home, const Team& away)
{
    return offsides_per_game(home.getMood(), away.getMood());
}

bool Offside::updatePlayer()
{
    if(this->off_side != NULL)
    {
        this->off_side->incrementOffsides();
        return 0;
    }
    else
    {
        return 1;
    }
}

void Offside::Off_side(vector<Player*> players)
{
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->offsideChance();
    }

    this->off_side = players[wrand(chances, players.size())];
}

bool Offside::Who(const Team& home, const Team& away)
{
    int ch_a = (int)away.getRatingFinal() / 5 + 5 * away.getMood();
    return rand() % ((int)home.getRatingFinal() / 5 + 5 * home.getMood() + ch_a) < ch_a;
}

Offside* OffSide(Team& home, Team& away, int expected, int so_far, int min, int half, int mins_half)
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
        Offside* offside = new Offside;
        offside->min = min;
        offside->half = half;
        offside->team = offside->Who(home, away);
        if(offside->team)
        {
            offside->Off_side(away.getPlayers());
        }
        else
        {
            offside->Off_side(home.getPlayers());
        }
        return offside;
    }
    else
    {
        return NULL;
    }
}

void Offside::printList()
{
    cout << "Offside: " << this->off_side->getFirstName().at(0) << ". " << this->off_side->getFamilyName() << " ";
    this->printMinute();
    cout << "'" << endl;
}