#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#pragma once
#include "Player.h"
#include "Stadium.h"
#include "Team.h"
#include "Minute.h"
#include "Referees.h"
#include "Weather.h"
#include "Administrative_functions.h"
#include "PenaltyShootOut.h"
using namespace std;

class Match {
    protected:
        bool active;
        Team* home_t;
        Team* away_t;
        Stadium* stadium;
        Referees* referees;
        Weather* weather;
        vector<Minute> Half1;
        int mins_half1;
        vector<Minute> Half2;
        int mins_half2;
        vector<Minute> ExtraTime1;
        int mins_extratime1;
        vector<Minute> ExtraTime2;
        int mins_extratime2;
        exp_Events* expected_events;
        PenaltyShootOut* ShootOut;
        bool kick_off1;
    
    public:
        void prepareMatch(Team*, Team*, Stadium*, Referees*, Weather*);
        inline bool CoinToss() { this->kick_off1 = rand() % 2; return this->kick_off1; };
        void preview();
        bool editMatch(Countries);

        void KickOff(int);
        void finalWhistle(int);
        void printTeamStatistics(const Team&, const Team&);
        void match();
};