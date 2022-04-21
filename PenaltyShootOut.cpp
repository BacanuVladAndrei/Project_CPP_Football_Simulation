#include <iostream>
#include <string>
#include <cstring>
#include "PenaltyShootOut.h"
#include "Administrative_functions.h"
using namespace std;

PenaltyShootOut::PenaltyShootOut()
{
    this->home_t = NULL;
    this->order_home = NULL;
    this->home = NULL;
    this->pen_home = 0;
    this->away_t = NULL;
    this->order_away = NULL;
    this->away = NULL;
    this->pen_away = 0;
}

PenaltyShootOut::PenaltyShootOut(Team* home_t, int* order_home, Team* away_t, int* order_away)
{
    this->home_t = home_t;
    this->order_home = order_home;
    this->home = new Penalty[5];
    this->pen_home = 0;
    this->away_t = away_t;
    this->order_away = order_away;
    this->away = new Penalty[5];
    this->pen_away = 0;
}

PenaltyShootOut::~PenaltyShootOut()
{
    if(this->order_home != NULL)
    {
        delete[] this->order_home;
    }
    if(this->home != NULL)
    {
        delete[] this->home;
    }
    if(this->order_away != NULL)
    {
        delete[] this->order_away;
    }
    if(this->away != NULL)
    {
        delete[] this->away;
    }
}

bool PenaltyShootOut::alreadyChoosed(bool team, int choice)
{
    if(team)
    {
        for(int i = 0; i < this->away_t->getIn(); i++)
        {
            if(this->order_away[i] == choice)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        for(int i = 0; i < this->home_t->getIn(); i++)
        {
            if(this->order_home[i] == choice)
            {
                return true;
            }
        }
        return false;
    }
}

void PenaltyShootOut::setTeams(Team* home_team, Team* away_team)
{
    this->home_t = home_team;
    this->away_t = away_team;
}

void PenaltyShootOut::readOrder(bool team)
{
    if(team)
    {
        int executors = 0;
        cout << "Available " << this->away_t->getName() << " players:" << endl;
        for(int i = 0; i < this->away_t->getIn(); i++)
        {
            if(this->away_t->getPlayer(i)->getStatus() == 1 || this->away_t->getPlayer(i)->getStatus() == 2)
            {
                cout << i + 1 << ". " << this->away_t->getPlayer(i)->getFirstName() << " " << this->away_t->getPlayer(i)->getFamilyName() << endl;
                executors++;
            }
        }
        this->order_away = new int[executors]();
        cout << endl << "Introduce executors' numbers in order: ";
        for(int i = 0; i < executors; i++)
        {
            do{
                cout << "Executor " << i + 1 << ": ";
                this->order_away[i] = get_int_secure(1, this->away_t->getIn(), "Not a player!\nExecutor: ", "Invalid number!\nExecutor: ");
                this->order_away[i] --;
                if(this->alreadyChoosed(1, this->order_away[i]))
                {
                    cout << "This executor has already been chosen!" << endl;
                }
                if(this->away_t->getPlayer(i)->getStatus() == 3)
                {
                    cout << "This player has been sent off!" << endl;
                }
            }while(this->alreadyChoosed(1, this->order_away[i]) || this->away_t->getPlayer(i)->getStatus() == 3);
        }
    }
    else
    {
        int executors = 0;
        cout << "Available " << this->home_t->getName() << " players:" << endl;
        for(int i = 0; i < this->home_t->getIn(); i++)
        {
            if(this->home_t->getPlayer(i)->getStatus() == 1 || this->home_t->getPlayer(i)->getStatus() == 2)
            {
                cout << i + 1 << ". " << this->home_t->getPlayer(i)->getFirstName() << " " << this->home_t->getPlayer(i)->getFamilyName() << endl;
                executors++;
            }
        }
        this->order_home = new int[executors]();
        cout << endl << "Introduce executors' numbers in order: ";
        for(int i = 0; i < executors; i++)
        {
            do{
                cout << "Executor " << i + 1 << ": ";
                this->order_home[i] = get_int_secure(1, this->home_t->getIn(), "Not a player!\nExecutor: ", "Invalid number!\nExecutor: ");
                this->order_home[i] --;
                if(this->alreadyChoosed(0, this->order_home[i]))
                {
                    cout << "This executor has already been chosen!" << endl;
                }
                if(this->home_t->getPlayer(i)->getStatus() == 3)
                {
                    cout << "This player has been sent off!" << endl;
                }
            }while(this->alreadyChoosed(0, this->order_home[i]) || this->home_t->getPlayer(i)->getStatus() == 3);
        }
    }
}

bool PenaltyShootOut::insurmountable(int exec_home, int exec_away)
{
	return (exec_home - this->pen_home > 5 - (this->pen_away) || exec_away - this->pen_away > 5 - (this->pen_home));
}

void PenaltyShootOut::ShootOut()
{
    cout << "Shoot out begins..." << endl << endl;
    
    if(this->home == NULL)
    {
        this->home = new Penalty[5];
    }
    if(this->away == NULL)
    {
        this->away = new Penalty[5];
    }
    bool scored = 0;
    for(int i = 0; i < 5; i++)
    {
        getche();
        if(!insurmountable(i, i))
        {
            scored = this->home[i].TakePenalty(this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()]), this->away_t->getPlayers(), this->home_t->getPlayers());
            if(scored)
            {
                cout << this->home_t->getName() << " " << i + 1 << ": GOAL - " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFirstName() << " " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFamilyName() << endl;
                this->pen_home ++;
            }
            else
            {
                cout << this->home_t->getName() << " " << i + 1 << ": Miss - " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFirstName() << " " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFamilyName() << endl;
            }
        }
        else
        {
            break;
        }
        getche();
        if(!insurmountable(i + 1, i))
        {
            scored = this->away[i].TakePenalty(this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()]), this->home_t->getPlayers(), this->away_t->getPlayers());
            if(scored)
            {
                cout << this->away_t->getName() << " " << i + 1 << ": GOAL - " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFirstName() << " " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFamilyName() << endl;
                this->pen_away ++;
            }
            else
            {
                cout << this->away_t->getName() << " " << i + 1 << ": Miss - " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFirstName() << " " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFamilyName() << endl;
            }
        }
        else
        {
            break;
        }
    }
    int i = 5;
    while(this->pen_home == this->pen_away)
    {
        this->home = Resize<Penalty>(this->home, i, i + 1);
        this->away = Resize<Penalty>(this->away, i, i + 1);
        getche();
        scored = this->home[i].TakePenalty(this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()]),  this->home_t->getPlayers(), this->away_t->getPlayers());
        if(scored)
        {
            cout << this->home_t->getName() << " " << i + 1 << ": GOAL - " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFirstName() << " " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFamilyName() << endl;
            this->pen_home ++;
        }
        else
        {
            cout << this->home_t->getName() << " " << i + 1 << ": Miss - " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFirstName() << " " << this->home_t->getPlayer(this->order_home[i % this->home_t->getIn()])->getFamilyName() << endl;
        }
        getche();
        scored = this->away[i].TakePenalty(this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()]),  this->away_t->getPlayers(), this->home_t->getPlayers());
        if(scored)
        {
            cout << this->away_t->getName() << " " << i + 1 << ": GOAL - " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFirstName() << " " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFamilyName() << endl;
            this->pen_away ++;
        }
        else
        {
            cout << this->away_t->getName() << " " << i + 1 << ": Miss - " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFirstName() << " " << this->away_t->getPlayer(this->order_away[i % this->away_t->getIn()])->getFamilyName() << endl;
        }
        i ++;
    }
    cout << endl << "Outcome: " << this->home_t->getName() << " " << this->pen_home << " - " << this->pen_away << " " << this->away_t->getName() << endl;
}