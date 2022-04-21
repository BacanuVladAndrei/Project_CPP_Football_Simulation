#include <iostream>
#include <string>
#include <fstream>
#pragma once
#include "Player.h"
#include "Event.h"
#include "Goal.h"
using namespace std;

class Shot : public Event {
    protected:
        Player* taker;
        bool on_target;
        bool inside_the_box;
        bool powerful;

    public:
        Shot();
        Shot(int, int, bool, Player*, bool, bool, bool);

        void printList();

        bool power(); // returns 1 if the shot was powerful, 0 if it wasn't
        bool position(); // returns 1 if the shot was taken from inside the box, 0 if it was taken from outside
        bool getOnTarget();

        friend int shotsTeam();
        friend int expectedShots(const Team&, const Team&);

        bool updatePlayer();
        void updatePossession(double& pos) { pos += 10; };

        void Taker(vector<Player*>);
        void set(int, int, bool, Player*, bool, bool, bool);
        bool Who(const Team&, const Team&);

        friend Shot* Shoot(Goal*, Team&, Team&, int, int, int, int, int, int);
};