#include <iostream>
#include <fstream>
#include <string>
#include "Administrative_functions.h"
#include "Passes.h"
using namespace std;

int expectedPasses()
{
    return 700 + rand() % 801;
}

int* calculatePassesEachMinute(int expected_half, int mins_per_half) // Call each half
{
    int* vector = new int[mins_per_half]();
    for(int i = 0; i < expected_half; i++)
    {
        vector[rand() % mins_per_half] ++;
    }

    return vector;
}

int passesThisMinute(int min, int* vec, int mins_per_half)
{
    return min > mins_per_half ? 0 : vec[min - 1];
}

void distributePasses(const int passes_min, const int possession_home, int& passes_home, const int possession_away, int& passes_away)
{
    if(possession_away + possession_home < 1)
    {
        return;
    }

    for(int i = 0; i < passes_min; i++)
    {
        if(rand() % (possession_away + possession_home) < possession_home)
        {
            passes_home ++;
        }
        else
        {
            passes_away ++;
        }
    }
}

int getPasser(const Team& team)
{
    int* chances = new int[team.getIn()];
    int ok = 0;
    for(int i = 0; i < team.getIn(); i++)
    {
        chances[i] = team.getPlayer(i)->passChance();
        if(chances[i])
            ok = 1;
    }

    if(!ok)
    {
        return -1;
    }

    return wrand(chances, team.getIn());
}

int distributePasses(Team& team, const int passes_nr)
{
    int passer = -1;
    int accurate = 0;
    for(int i = 0; i < passes_nr; i++)
    {
        passer = getPasser(team);
        if(passer > -1)
        {
            team.getPlayer(passer)->incrementPasses();
            if(team.getPlayer(passer)->accuratePass())
            {
                team.getPlayer(passer)->incrementAccuratePasses();
                accurate ++;
            }
        }
    }
    return accurate;
}