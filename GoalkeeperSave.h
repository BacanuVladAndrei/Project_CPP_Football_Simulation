#include <iostream>
#include <string>
#include <fstream>
#pragma once
#include "Event.h"
#include "Player.h"
#include "Shot.h"
#include "Goal.h"
using namespace std;

class GoalkeeperSave : public Event {
    protected:
        Player* goalkeeper;

    public:
        GoalkeeperSave() { this->goalkeeper = NULL; };
        GoalkeeperSave(int, int, bool, Player*); 

        void printList();

        bool updatePlayer();
        void updatePossession(double& pos) { pos += 5; };

        void Keeper(vector<Player*>);

        friend GoalkeeperSave* Save(Shot*, Goal*, Team&, Team&, int, int);
};