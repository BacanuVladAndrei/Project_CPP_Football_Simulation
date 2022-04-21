#include <iostream>
#include <string>
#include <fstream>
#include "Foul.h"
#include "Administrative_functions.h"
using namespace std;

Foul::Foul()
{
    this->against = NULL;
    this->guilty = NULL;
    this->yellow_card = 0;
    this->red_card = 0;
    this->free_kick = 0;
}

Foul::Foul(int half, int min, bool team, Player* against, Player* guilty, bool yellow_card, bool red_card, bool free_kick) : Event::Event(half, min, team)
{
    this->against = against;
    this->guilty = guilty;
    this->yellow_card = yellow_card;
    this->red_card = red_card;
    this->free_kick = free_kick;
}

int foulsTeam(int agg, double rat)
{
    int a = rand() % 100;
    int fouls;
    if(a < 5)
    {
        fouls = 10;
    }
    else
        if(a < 15)
        {
            fouls = 11;
        }
        else
            if(a < 30)
            {
                fouls = 12;
            }
            else
                if(a < 50)
                {
                    fouls = 13;
                }
                else
                    if(a < 70)
                    {
                        fouls = 14;
                    }
                    else
                        if(a < 85)
                        {
                            fouls = 15;
                        }
                        else
                            if(a < 95)
                            {
                                fouls = 16;
                            }
                            else
                            {
                                fouls = 17;
                            }
    fouls = fouls + 2 * agg / 3;
    fouls = fouls - rat / 10 + 5;
    return fouls;
}

int expectedFouls(const Team& home, const Team& away)
{
    return foulsTeam(home.getAgg(), home.getRatingFinal()) + foulsTeam(away.getAgg(), away.getRatingFinal());
}

bool Foul::updatePlayer()
{
    if(this->against != NULL)
    {
        this->against->incrementFoulsSuffered();
    }
    else
    {
        return 1;
    }
    if(this->guilty != NULL)
    {
        this->guilty->incrementFoulsCommitted();
        if(this->yellow_card)
        {
            this->guilty->incrementYellowCard();
        }
        if(this->red_card)
        {
            this->guilty->incrementRedCard();
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

void Foul::Guilty(vector<Player*> players)
{
    int max_rat = 0;
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i]->getRat() > max_rat)
        {
            max_rat = players[i]->getRat();
        }
    }

    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->foulChance(max_rat);
    }

    this->guilty = players[wrand(chances, players.size())];
}

void Foul::Against(vector<Player*> players)
{
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->foulAgainstChance(this->guilty->getPos());
    }

    this->against = players[wrand(chances, players.size())];
}

void Foul::YellowCard()
{
    this->yellow_card = this->team ? (rand() % 79613 < 10000) : (rand() % 106408 < 10000);
}

void Foul::RedCard()
{
    if(this->yellow_card)
    {
        this->red_card = 0;
    }
    else
    {
        this->red_card = this->team ? (rand() % 112687 < 1000) : (rand() % 180722 < 1000);
    }
}

Foul* Fouled(Team& home, Team& away, int expected, int so_far, int min, int half, int mins_half)
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
        Foul* foul = new Foul;
        foul->min = min;
        foul->half = half;
        foul->team = foul->Who(home, away);
        if(foul->team)
        {
            foul->Guilty(away.getPlayers());
            foul->Against(home.getPlayers());
        }
        else
        {
            foul->Guilty(home.getPlayers());
            foul->Against(away.getPlayers());
        }
        foul->YellowCard();
        foul->RedCard();
        foul->free_kick = 0;

        return foul;
    }
    else
    {
        return NULL;
    }
}

void Foul::printList()
{
    cout << "Foul: " << this->guilty->getFirstName().at(0) << ". " << this->guilty->getFamilyName() << " / " << this->against->getFirstName().at(0) << ". " << this->against->getFamilyName() << " ";
    if(this->yellow_card && this->red_card)
    {
        cout << "(YC, RC) ";
    }
    else
    {
        if(this->yellow_card)
        {
            cout << "(YC) ";
        }
        else
        {
            if(this->red_card)
            {
                cout << "(RC) ";
            }
        }
    }
    this->printMinute();
    cout << "'" << endl;
}