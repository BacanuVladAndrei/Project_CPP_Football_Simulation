#include <iostream>
#include <string>
#include <cstring>
#include "Penalty.h"
#pragma once
using namespace std;

class PenaltyShootOut {
    protected:
        Team* home_t;
        int* order_home;
        Penalty* home;
        int pen_home;
        Team* away_t;
        int* order_away;
        Penalty* away;
        int pen_away;
    public:
        PenaltyShootOut();
        PenaltyShootOut(Team*, int*, Team*, int*);
        ~PenaltyShootOut();

        void setTeams(Team*, Team*);
        void readOrder(bool);
        bool alreadyChoosed(bool, int);
        bool insurmountable(int, int);
        void ShootOut();
};