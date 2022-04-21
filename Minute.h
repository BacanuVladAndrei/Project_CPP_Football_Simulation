#include <iostream>
#include <string>
#include <fstream>
#pragma once
#include "Player.h"
#include "Penalty.h"
#include "Event.h"
using namespace std;

class Minute {
    protected:
        int Min;
        int half;
        Event **events;
        int count_ev;
        double possession_home;
        double possession_away;
        
    public:
        Minute();
        void setMinute(int, int);
        Minute(int, int, Event*, int);
        
        int minute(Team&, Team&, exp_Events*, int, int, int&, int);
        Event** addEvent(Event*);

        void calculatePossession(const Team&, const Team&);
        friend int passPlayer(vector<Player*>);
};



// Background: fouls, corners, offsides, passes, possession 
// Foreground: goals, shots, fouls, goalkeeper saves, corners