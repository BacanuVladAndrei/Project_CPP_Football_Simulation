#include <iostream>
#include <string>
#include <fstream>
#include "Team.h"
#pragma once
using namespace std;

class Team;

int expectedCorners(const Team&, const Team&);
int expectedGoals(const Team&, const Team&);
int expectedFouls(const Team&, const Team&);
int expectedOffsides(const Team&, const Team&);
int expectedShots(const Team&, const Team&);

#ifndef EXP_EVENTS_H
#define EXP_EVENTS_H

struct exp_Events {
    int exp_Goals;
    int exp_Shots;
    int exp_Fouls;
    int exp_Offsides;
    int exp_Corners;
    int exp_Goalkeeper_Saves;
    int exp_Passes;
};

#endif

class Event {
    protected:
        int half;
        int min;
        bool team;

    public:
        Event();
        Event(int, int, bool);

        void printMinute();
        virtual void printList() {};

        virtual bool updatePlayer() { return 0; };
        virtual void updatePossession(double& pos) {};

        int getHalf() const { return this->half; };
        int getMin() const { return this->min; };
        bool getTeam() const { return this->team; };

        Event** queueEvent(Event**, int&);
        bool operator<(const Event&);
        virtual bool Who(const Team&, const Team&);
        
        friend void transferEvent(Event***, int&, Event***, int&);
        friend bool itHappens(int, int, int);
};

