#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "GoalkeeperSave.h"
#include "Administrative_functions.h"
using namespace std;

bool GoalkeeperSave::updatePlayer()
{
    if(this->goalkeeper != NULL)
    {
        this->goalkeeper->incrementSaves();
        return 0;
    }
    else
    {
        return 1;
    }
}

void GoalkeeperSave::Keeper(vector<Player*> players)
{
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i]->getPos() == 'G')
        {
            this->goalkeeper = players[i];
            return;
        }
    }
    this->goalkeeper = NULL;
    return;
}

GoalkeeperSave* Save(Shot* shot, Goal* goal, Team& home, Team& away, int min, int half)
{
    if((shot != NULL) && (goal == NULL))
    {
        if((rand() % 5 < 4) && shot->getOnTarget())
        {
            GoalkeeperSave* save = new GoalkeeperSave;
            save->min = min;
            save->half = half;
            save->team = !(shot->getTeam());
            if(save->team)
            {
                save->Keeper(away.getPlayers());
            }
            else
            {
                save->Keeper(home.getPlayers());
            }

            return save;
        }
        return NULL;
    }
    else
    {
        return NULL;
    }
}

void GoalkeeperSave::printList()
{
    cout << "Save: " << this->goalkeeper->getFirstName().at(0) << ". " << this->goalkeeper->getFamilyName() << " ";
    this->printMinute();
    cout << "'" << endl;
}