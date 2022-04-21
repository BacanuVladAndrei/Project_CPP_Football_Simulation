#include <iostream>
#include <string>
#include <cstring>
#include "Penalty.h"
#include "Administrative_functions.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

Penalty::Penalty()
{
    this->team = 0;
    this->scored = 0;
    this->taker = NULL;
    this->guilty = NULL;
    this->shot_direction = 0;
    this->goalkeeper_move = 0;
    this->awarded_for = 0;
}

Penalty::Penalty(bool team, int half, int min, bool scored, Player* taker, Player* guilty, int shot_direction, int goalkeeper_move, int awarded_for) : Event::Event(half, min, team)
{
    this->team = team;
    this->scored = scored;
    this->taker = taker;
    this->guilty = guilty;
    this->shot_direction = shot_direction;
    this->goalkeeper_move = goalkeeper_move;
    this->awarded_for = awarded_for;
}

void Penalty::Taker(vector<Player*> players)
{
    int min_rat = 100;
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i]->getRat() < min_rat)
        {
            min_rat = players[i]->getRat();
        }
    }

    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->penaltyTakerChance(min_rat);
    }

    this->taker = players[wrand(chances, players.size())];
}

void Penalty::Guilty(vector<Player*> players)
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
        chances[i] = players[i]->penaltyGuiltyChance(max_rat);
    }

    this->guilty = players[wrand(chances, players.size())];
}

void Penalty::Score()
{
    int a = rand() % 100;
    this->scored = (a < 75 + this->taker->getRat() / 10);
}

void Penalty::ShotDirection()
{
    if(this->scored)
    {
        int chances[] = { 10, 6, 10, 9, 2, 9, 12, 3, 12 };
        this->shot_direction = 1 + wrand(chances, 9);
    }
    else
    {
        int chances[] = { 10, 6, 10, 9, 2, 9, 12, 3, 12, 11, 36, 19 };
        this->shot_direction = 1 + wrand(chances, 12);
    }
}

void Penalty::GoalkeeperMove()
{
    if(this->scored)
    {
        int chances[] = { 10, 1, 10, 9, 1, 9, 12, 1, 12 };
        this->goalkeeper_move = 1 + wrand(chances, 9);
    }
    else
    {
        if(this->shot_direction < 10)
        {
            this->goalkeeper_move = this->shot_direction;
        }
        else
        {
            int chances[] = { 10, 1, 10, 9, 1, 9, 12, 1, 12 };
            this->goalkeeper_move = 1 + wrand(chances, 9);
        }
    }   
}

void Penalty::Awarded(bool dep)
{
    if(dep)
    {
        this->awarded_for = 0;
        return;
    }
    if(this->guilty->getPos() == 'G')
    {
        this->awarded_for = 2;
    }
    else
    {
        int chances[] = { 1, 4 };
        this->awarded_for = 1 + wrand(chances, 2);
    }
}

void Penalty::print()
{
    switch(this->awarded_for) {
        case '1':
        {
            cout << this->guilty->getFirstName().at(0) << ". " << this->guilty->getFamilyName() << " had to be more careful there! He touched the ball with his hand! This can't escape the referee..." << endl;
            sleep(3);
            break;
        }
        case '2':
        {
            cout << this->guilty->getFirstName().at(0) << ". " << this->guilty->getFamilyName() << " fouls his opponent inside the box! A cristal clear penalty is awarded!" << endl;
            sleep(3);
            break;
        }
        default:
        {
            break;
        }
    }

    string a[] = { " steps up to the ball...", " will have no mercy...", " takes the responsibility..." };
    cout << this->taker->getFirstName().at(0) << ". " << this->taker->getFamilyName() << a[rand() % 3] << endl;
    sleep(5);

    if(this->scored)
    {
        string b[] = { "He almost ripped the net off!", "The keeper stood no chance!", "Devastating shot!", "Fine finishing there!" };
        cout << "GOAL! " << b[rand() % 4] << endl;
    }
    else
    {
        switch(this->shot_direction){
            case 10:
            {
                cout << "Miss! It goes off the woorwork!" << endl;
                break;
            }
            case 11:
            {
                cout << "Miss! It files over the crossbar!" << endl;
                break;
            }
            case 12:
            {
                cout << "Miss! It went near the post!" << endl;
                break;
            }
            default:
            {
                string c[] = { "The keeper guessed his intentions and intervened promptly!", "He didn't do enough to fool the keeper!" };
                cout << "Miss! " << c[rand() % 3] << endl;
            }
        }
    }
}

bool Penalty::TakePenalty(Player* executor, vector<Player*> taker_players, vector<Player*> guilty_players)
{
    if(executor == NULL)
    {
        this->Taker(taker_players);
        this->Guilty(guilty_players);
        this->Score();
        this->ShotDirection();
        this->GoalkeeperMove();
    }
    else
    {
        this->taker = executor;
        this->guilty = NULL;
        this->Score();
        this->ShotDirection();
        this->GoalkeeperMove();
    }

    return this->scored;
    // this->print();
}