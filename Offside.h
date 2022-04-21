#include <iostream>
#include <string>
#include <fstream>
#pragma once
#include "Event.h"
#include "Player.h"
#include "Event.h"
using namespace std;

class Offside : public Event {
    protected:
        Player* off_side;

    public:
        Offside();
        Offside(int, int, bool, Player*);

        void printList();

        friend int offsides_per_game(int, int);
        friend int min_offsides_team(int, int);
        friend int expectedOffsides(const Team&, const Team&);

        bool updatePlayer();
        void updatePossession(double& pos) { pos -= 5; };

        void Off_side(vector<Player*>);
        bool Who(const Team&, const Team&);

        friend Offside* OffSide(Team&, Team&, int, int, int, int, int);
};

bool itHappens(int, int, int);