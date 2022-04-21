#include <iostream>
#include <string>
#include <cstring>
#pragma once
#include "Event.h"
#include "Player.h"
using namespace std;

class Penalty : public Event {
    protected:
        bool scored;
        Player* taker;
        Player* guilty;
        int shot_direction;
        int goalkeeper_move;
        int awarded_for;

    public:
        Penalty();
        Penalty(bool, int, int, bool, Player*, Player*, int, int, int);
        ~Penalty() {};

        Player* getTaker() const { return this->taker; };

        void Taker(vector<Player*>);
        void Guilty(vector<Player*>);
        void Score();
        void Awarded(bool);
        void ShotDirection();
        void GoalkeeperMove();

        bool TakePenalty(Player*, vector<Player*>, vector<Player*>);
        void print();
};