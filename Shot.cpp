#include <iostream>
#include <string>
#include <fstream>
#include "Shot.h"
using namespace std;

bool itHappens(int, int, int);

Shot::Shot()
{
    this->taker = NULL;
    this->on_target = 0;
}

Shot::Shot(int half, int min, bool team, Player* taker, bool on_target, bool inside_the_box, bool powerful) : Event::Event(half, min, team)
{
    this->taker = taker;
    this->on_target = on_target;
    this->inside_the_box = inside_the_box;
    this->powerful = powerful;
}

int shotsTeam()
{
    int a = rand() % 268;

    if(a < 2)
    {
        return 1;
    }
    else
        if(a < 5)
        {
            return 2;
        }
        else
            if(a < 9)
            {
                return 3;
            }
            else
                if(a < 15)
                {
                    return 4;
                }
                else
                    if(a < 24)
                    {
                        return 5;
                    }
                    else
                        if(a < 35)
                        {
                            return 6;
                        }
                        else
                            if(a < 50)
                            {
                                return 7;
                            }
                            else
                                if(a < 70)
                                {
                                    return 8;
                                }
                                else
                                    if(a < 95)
                                    {
                                        return 9;
                                    }
                                    else
                                        if(a < 125)
                                        {
                                            return 10;
                                        }
                                        else
                                            if(a < 165)
                                            {
                                                return 11;
                                            }
                                            else
                                                if(a < 200)
                                                {
                                                    return 12;
                                                }
                                                else
                                                    if(a < 230)
                                                    {
                                                        return 13;
                                                    }
                                                    else
                                                        if(a < 250)
                                                        {
                                                            return 14;
                                                        }
                                                        else
                                                            if(a < 260)
                                                            {
                                                                return 15;
                                                            }
                                                            else
                                                                if(a < 265)
                                                                {
                                                                    return 16;
                                                                }
                                                                else
                                                                {
                                                                    return 17;
                                                                }
}

int expectedShots(const Team& home, const Team& away)
{
    return shotsTeam() + shotsTeam() + (home.getMood() + away.getMood()) / 2;
}

bool Shot::power()
{
    // 462 - placed
    // 353 - powerful
    this->powerful = (rand() % 815 < 353);
    return this->powerful;
}

bool Shot::position()
{
    // 496 - in box
    // 191 - out box
    this->inside_the_box = (rand() % 687 < 496);
    return this->inside_the_box;
}

void Shot::set(int half, int min, bool team, Player* taker, bool on_target, bool inside_the_box, bool powerful)
{
    this->half = half;
    this->min = min;
    this->team = team;
    this->taker = taker;
    this->on_target = on_target;
    this->inside_the_box = inside_the_box;
    this->powerful = powerful;
}

void Shot::Taker(vector<Player*> players)
{
    int min_rat = 100;
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i]->getRat() < min_rat)
        {
            min_rat = players[i]->getRat();
        }
    }

    int chances_sum = 0;
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->shotTakerChance(min_rat);
        chances_sum += chances[i];
    }

    if(chances_sum == 0)
    {
        return;
    }

    int lim = rand() % chances_sum;
    chances_sum = 0;
    for(int i = 0; i < players.size(); i++)
    {
        chances_sum +=chances[i];
        if(lim < chances_sum)
        {
            this->taker = players[i];
        }
    }

    return;
}

bool Shot::Who(const Team& home, const Team& away)
{
    int ch_home = 11 + (home.getRatingFinal() - away.getRatingFinal()) / 2 + home.getMood() / 2;
    int ch_away = 11 + (away.getRatingFinal() - home.getRatingFinal()) / 2 + away.getMood() / 2;

    return (rand() % (ch_home + ch_away) < ch_away);
}

Shot* Shoot(Goal* scored, Team& home, Team& away, int expected, int shots_home, int shots_away, int min, int half, int mins_in_half)
{
    if(scored != NULL)
    {
        Shot* shot = new Shot;
        shot->set(half, min, scored->getTeam(), scored->getScorer(), 1, 0, 0);
        shot->power();
        shot->position();
        return shot;
    }
    else
    {
        int mins_left;
        if(half == 1)
        {
            mins_left = mins_in_half - min + 45;
        }
        else
            if(half == 3)
            {
                mins_left = mins_in_half - min + 15;
            }
            else
            {
                mins_left = mins_in_half - min;
            }
        if(itHappens(expected, shots_home + shots_away, mins_left))
        {
            Shot* shot = new Shot;
            bool team = shot->Who(home, away);
            shot->set(half, min, team, NULL, rand() % 20 < 6, 0, 0);
            if(team)
            {
                shot->Taker(away.getPlayers());
            }
            else
            {
                shot->Taker(home.getPlayers());
            }
            shot->power();
            shot->position();
            
            return shot;
        }
        else
        {
            return NULL;
        }
    }
}

bool Shot::updatePlayer()
{
    if(this->taker != NULL)
    {
        this->taker->incrementShots();
        if(this->on_target)
        {
            this->taker->incrementShotsOnTarget();
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

void Shot::printList()
{
    cout << "Shot: " << this->taker->getFirstName().at(0) << ". " << this->taker->getFamilyName() << " ";
    this->printMinute();
    cout << "'" << endl;
}

bool Shot::getOnTarget()
{
    return this->on_target;
}