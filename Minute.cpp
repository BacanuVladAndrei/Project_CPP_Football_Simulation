#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include "Team.h"
#include "Minute.h"
#include "Event.h"
#include "Goal.h"
#include "Shot.h"
#include "Foul.h"
#include "Offside.h"
#include "Corner.h"
#include "GoalkeeperSave.h"
#include "Administrative_functions.h"
#include "Passes.h"
using namespace std;

bool itHappens(int, int, int);
Goal* Score(vector<Player*>, double, int, vector<Player*>, double, int, int, int, int, int, int, int, int&);
Shot* Shoot(Goal*, Team&, Team&, int, int, int, int, int, int);
GoalkeeperSave* Save(Shot*, Goal*, Team&, Team&, int, int);
Foul* Fouled(Team&, Team&, int, int, int, int, int);
Offside* OffSide(Team&, Team&, int, int, int, int, int);
Corner* CornerKick(Team&, Team&, int, int, int, int, int);

Minute::Minute()
{
    this->half = 0;
    this->Min = 0;
    this->events = NULL;
    this->count_ev = 0;
    this->possession_away = 0.0;
    this->possession_home = 0.0;
}

void Minute::setMinute(int half, int min)
{
    this->half = half;
    this->Min = min;
}

int Minute::minute(Team& home, Team& away, exp_Events* expected, int mins_left, int mins_per_half, int& cooldown, int passes_min)
{
    // Goals
    Goal* goal = Score(home.getPlayers(), home.getRatingFinal(), home.getMood(), away.getPlayers(), away.getRatingFinal(), away.getMood(), expected->exp_Goals, home.getGoals(), away.getGoals(), this->half, this->Min, mins_per_half, cooldown);
    if(goal != NULL)
    {
        this->events = this->addEvent(goal);
        goal->updatePlayer();
        if(goal->getTeam())
        {
            home.getPlayer(0)->incrementGoalsReceived();
            away.incrementGoals();
        }
        else
        {
            away.getPlayer(0)->incrementGoalsReceived();
            home.incrementGoals();
        }
        goal->printList();
    }

    // Shots
    Shot* shot = Shoot(goal, home, away, expected->exp_Shots, home.getShots(), away.getShots(), this->Min, this->half, mins_per_half);
    if(shot != NULL)
    {
        this->events = this->addEvent(shot);
        shot->updatePlayer();
        shot->printList();
        if(shot->getTeam())
        {
            away.incrementShots();
            if(shot->getOnTarget())
            {
                away.incrementShotsOnTarget();
            }
        }
        else
        {
            home.incrementShots();
            if(shot->getOnTarget())
            {
                home.incrementShotsOnTarget();
            }
        }
    }

    // Goalkeeper Saves
    GoalkeeperSave* save = Save(shot, goal, home, away, this->Min, this->half);
    if(save != NULL)
    {
        this->events = this->addEvent(save);
        save->updatePlayer();
        save->printList();
        if(save->getTeam())
        {
            away.incrementGoalkeeperSaves();
        }
        else
        {
            home.incrementGoalkeeperSaves();
        }
    }

    // Fouls
    Foul* foul = Fouled(home, away, expected->exp_Fouls, home.getFouls() + away.getFouls(), this->Min, this->half, mins_per_half);
    if(foul != NULL)
    {
        this->events = this->addEvent(foul);
        foul->updatePlayer();
        foul->printList();
        if(foul->getTeam())
        {
            away.incrementFouls();
            if(foul->getYellowCard())
            {
                away.incrementYellowCards();
            }
            if(foul->getRedCard())
            {
                away.incrementRedCards();
            }
        }
        else
        {
            home.incrementFouls();
            if(foul->getYellowCard())
            {
                home.incrementYellowCards();
            }
            if(foul->getRedCard())
            {
                home.incrementRedCards();
            }
        }
    }

    // Offsides
    Offside* offside = OffSide(home, away, expected->exp_Offsides, home.getOffsides() + away.getOffsides(), this->Min, this->half, mins_per_half);
    if(offside != NULL)
    {
        this->events = this->addEvent(offside);
        offside->updatePlayer();
        offside->printList();
        if(offside->getTeam())
        {
            away.incrementOffsides();
        }
        else
        {
            home.incrementOffsides();
        }
    }

    // Corners
    Corner* corner = CornerKick(home, away, expected->exp_Corners, home.getCorners() + away.getCorners(), this->Min, this->half, mins_per_half);
    if(corner != NULL)
    {
        this->events = this->addEvent(corner);
        corner->updatePlayer();
        corner->printList();
        if(corner->getTeam())
        {
            away.incrementCorners();
        }
        else
        {
            home.incrementCorners();
        }
    }

    // Possession
    this->calculatePossession(home, away);
    home.setPossession((home.getPossession() * (this->Min - 1) + this->possession_home) / (this->Min));
    away.setPossession((away.getPossession() * (this->Min - 1) + this->possession_away) / (this->Min));

    home.incrementMinutesPlayed();
    away.incrementMinutesPlayed();

    // Passes
    int passes_home = 0;
    int passes_away = 0;
    distributePasses(passes_min, this->possession_home, passes_home, this->possession_away, passes_away); // Between teams
    home.incrementPasses(passes_home);
    away.incrementPasses(passes_away);
    home.incrementAccuratePasses(distributePasses(home, passes_home)); // Among home players
    away.incrementAccuratePasses(distributePasses(away, passes_away)); // Among away players

    // Substitutions
    int nr = 0;
    int* v = home.Substitutions(this->half, this->Min, away.getGoals(), nr);
    home.printSubstitutions(v, nr, this->half, this->Min);
    delete[] v;
    nr = 0;
    v = away.Substitutions(this->half, this->Min, home.getGoals(), nr);
    away.printSubstitutions(v, nr, this->half, this->Min);
    delete[] v;

    return 0;
}

Event** Minute::addEvent(Event* event)
{
    this->events = Resize<Event*>(this->events, this->count_ev, this->count_ev + 1);
    this->events[this->count_ev] = event;
    this->count_ev ++;
    
    return this->events;
}

void Minute::calculatePossession(const Team& home, const Team& away)
{
    this->possession_away = 0.0;
    this->possession_home = 0.0;
    for(int i = 0; i < this->count_ev; i++)
    {
        if(this->events[i]->getTeam())
        {
            this->events[i]->updatePossession(this->possession_away);
        }
        else
        {
            this->events[i]->updatePossession(this->possession_home);
        }
    }

    double remainder = 60 - this->possession_home - this->possession_away;
    double score_h = (home.getRatingFinal() - 20) * (home.getRatingFinal() - 20) + 150 * home.getFormation().getM() + rand() % 100;
    double score_a = (away.getRatingFinal() - 20) * (away.getRatingFinal() - 20) + 150 * away.getFormation().getM() + rand() % 100;
    this->possession_home += score_h * remainder / (score_h + score_a);
    this->possession_away += remainder - score_h * remainder / (score_h + score_a);

    this->possession_home = 5 * this->possession_home / 3;
    this->possession_away = 5 * this->possession_away / 3;
}