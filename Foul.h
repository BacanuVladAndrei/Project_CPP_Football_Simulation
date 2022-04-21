#include <iostream>
#include <string>
#include <fstream>
#pragma once
#include "Event.h"
using namespace std;

class Foul : public Event {
    protected:
        Player* against;
        Player* guilty;
        bool yellow_card;
        bool red_card;
        bool free_kick;

    public:
        Foul();
        Foul(int, int, bool, Player*, Player*, bool, bool, bool);

        void printList();
        bool getYellowCard() { return this->yellow_card; };
        bool getRedCard() { return this->red_card; };

        friend int foulsTeam(int, double);
        friend int expectedFouls(const Team&, const Team&);

        bool updatePlayer();
        void updatePossession(double& pos) { pos -= 10; };

        void Guilty(vector<Player*>);
        void Against(vector<Player*>);
        void YellowCard();
        void RedCard();
        bool Who(const Team&, const Team&) { return rand() % 2; }; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        friend Foul* Fouled(Team&, Team&, int, int, int, int, int);
};

bool itHappens(int, int, int);