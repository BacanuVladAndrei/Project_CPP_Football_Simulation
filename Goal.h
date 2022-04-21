#include <iostream>
#include <string>
#include <fstream>
#pragma once
#include "Event.h"
#include "Player.h"
using namespace std;

class Penalty;

class Goal : public Event {
    protected:
        Player *scorer;
        Player *assist;

    public:
        Goal();
        Goal(Player*, Player*, int, int);
        Goal(const Goal&);
        Goal& operator=(const Goal&);
        Goal& operator=(const Penalty&);
        ~Goal() {};

        void printList();

        Player* getScorer() const;
        Player* getAssist() const;
        bool getTeam() const { return this->team; };
        int getHalf() const;
        int getMin() const;

        void setScorer(Player*);
        void setAssist(Player*);
        void setHalf(int);
        void setMin(int);

        bool updatePlayer();
        void updatePossession(double& pos) { pos += 15; };

        void write(fstream&) const;

        friend int expectedGoals(const Team&, const Team&);

        //                 homepl    hnr  home_r  h_m  awaypl    anr  away_r  a_m  tg   glsh  glsa  half min  m/h  cldn
        friend Goal* Score(vector<Player*>, double, int, vector<Player*>, double, int, int, int, int, int, int, int, int&);
        friend int minScoreChance(int, int); // returns the chance of goal in a certain minute
        friend bool scoreMin(int, int, int, int, int&, double, double, int, int); // returns 1 if in a certain minute any team scores, 0 if not
        friend bool scoreTeam(double, double, int, int); // returns 0 if home team scored, 1 if away team scored
        friend Player* playerScores(vector<Player*>);
        friend Player* playerAssist(vector<Player*>, Player*);
};