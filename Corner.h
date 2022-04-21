#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#pragma once
#include "Event.h"
#include "Team.h"
#include "Player.h"
using namespace std;

class Corner : public Event {
    protected:
        Player* taker;
        Player* touch;

    public:
        Corner();
        Corner(int, int, bool, Player*, Player*);

        void printList();

        friend int match_corners_calc(int, int);
        friend int expectedCorners(const Team&, const Team&);

        bool updatePlayer() { return 0; };
        void updatePossession(double& pos) { pos += 5; };

        void Taker(vector<Player*>);
        void Touch(vector<Player*>);
        bool Who(const Team&, const Team&);

        friend Corner* CornerKick(Team&, Team&, int, int, int, int, int);
};

bool itHappens(int, int, int);