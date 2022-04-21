#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Player.h"
#include "Formation.h"
#include "Country.h"
#include "Technical_parameters.h"
#pragma once
using namespace std;

#ifndef GOALSCORER_H
#define GOALSCORER_H

struct Goalscorer {
    Goalscorer *next;
};

#endif

#ifndef RATING_H
#define RATING_H

struct Rating {
    double final; // depending on technical parameters
    double total; // (def + mid + off) / 3;
    double def; // (5 * g + 10 * d + 3 * m + 1 * f) / 19;
    double mid; // (3 * d + 10 * m + 3 * f) / 16;
    double off; // (1 * d + 3 * m + 10 * f) / 14;
};

#endif

#ifndef TEAMSTATS_H
#define TEAMSTATS_H

struct TeamStats {
    int goals;
    double possession;
    int shots;
    int shots_on_target;
    double shot_accuracy;
    double shot_efficiency;
    int goalkeeper_saves;
    int offsides;
    int corners;
    int passes;
    int accurate_passes;
    double pass_accuracy;
    int fouls;
    int yellow_cards;
    int red_cards;
};

#endif

class Team {
    protected:
        bool type; // 0 for home team, 1 for away team
        string name;
        Rating rating; // compute on the basis of players
        Technical technical_parameters; // entered
        vector<Player*> players; // entered
        vector<Player*> substitutes; // entered
        int subs_left; // 3 
        int in; // 11
        int out; // subs nr
        Formation formation; // compute on the basis of players
        Country* nationality; // entered
        TeamStats statistics;
        Goalscorer* goalscorers; // NULL

    public:
        Team();
        void initStatistics();
        Team(bool, string, int, int, int, int, vector<Player*>, vector<Player*>, int, Country*);
        Team(const Team&);
        Team& operator=(const Team&);
        ~Team();
        
        inline void setName(const string& new_name) { this->name = new_name; };

        inline bool getType() const { return this->type; };
        inline string getName() const { return this->name; };
        inline double getRatingFinal() const { return this->rating.final; };
        inline double getRatingTotal() const { return this->rating.total; };
        inline double getRatingDef() const { return this->rating.def; };
        inline double getRatingMid() const { return this->rating.mid; };
        inline double getRatingOff() const { return this->rating.off; };
        inline int getMorale() const { return this->technical_parameters.morale; };
        inline int getSupp() const { return this->technical_parameters.supp; };
        inline int getMood() const { return this->technical_parameters.mood; };
        inline int getAgg() const { return this->technical_parameters.agg; };
        inline vector<int> getMoraleVector() const { return this->technical_parameters.morale_vector; };
        inline vector<int> getAggVector() const { return this->technical_parameters.aggressiveness_vector; };
        inline vector<Player*>& getPlayers() { return this->players; };
        inline Player* getPlayer(int i) const { return this->players[i]; };
        inline vector<Player*>& getSubstitutes() { return this->substitutes; };
        inline Player* getSubstitute(int i) const { return this->substitutes[i]; };
        inline int getSubsLeft() const { return this->subs_left; };
        inline int getIn() const { return this->in; };
        inline int getOut() const { return this->out; };
        inline Formation getFormation() const { return this->formation; };
        inline Country* getNationality() const { return this->nationality; };
        inline Goalscorer* getGoalscorers() const { return this->goalscorers; };
        int getPlayerIndex(Player*, bool) const;
        int getPlayerIndex(const string&, bool, bool) const;

        void setRatingFinal(int new_rat) { this->rating.final = new_rat; };
        void setFormation(int def, int mid, int fwd) { this->formation.set(def, mid, fwd); };

        inline int getGoals() const { return this->statistics.goals; };
        inline double getPossession() const { return this->statistics.possession; };
        inline int getShots() const { return this->statistics.shots; };
        inline int getShotsOnTarget() const { return this->statistics.shots_on_target; };
        inline double getShotAccuracy() const { return (double)this->statistics.shot_accuracy; };
        inline double getShotEfficiency() const { return (double)this->statistics.shot_efficiency; };
        inline int getGoalkeeperSaves() const { return this->statistics.goalkeeper_saves; };
        inline int getOffsides() const { return this->statistics.offsides; };
        inline int getCorners() const { return this->statistics.corners; };
        inline int getPasses() const { return this->statistics.passes; };
        inline int getAccuratePasses() const { return this->statistics.accurate_passes; };
        inline double getPassAccuracy() const { return (double)this->statistics.pass_accuracy; };
        inline int getFouls() const { return this->statistics.fouls; };
        inline int getYellowCards() const { return this->statistics.yellow_cards; };
        inline int getRedCards() const { return this->statistics.red_cards; };

        inline void setGoals(int val) { this->statistics.goals = val; this->computeShotEfficiency(); };
        inline void setPossession(double val) { this->statistics.possession = val; };
        inline void setShots(int val) { this->statistics.shots = val; this->computeShotAccuracy(); this->computeShotEfficiency(); };
        inline void setShotsOnTarget(int val) { this->statistics.shots_on_target = val; this->computeShotAccuracy(); };
        inline void computeShotAccuracy() { this->statistics.shot_accuracy = this->statistics.shots == 0 ? 0 : 100 * this->statistics.shots_on_target / this->statistics.shots; };
        inline void computeShotEfficiency() { this->statistics.shot_efficiency = this->statistics.shots == 0 ? 0 : 100 * this->statistics.goals / this->statistics.shots; };
        inline void setGoalkeeperSaves(int val) { this->statistics.goalkeeper_saves = val; };
        inline void setOffsides(int val) { this->statistics.offsides = val; };
        inline void setCorners(int val) { this->statistics.corners = val; };
        inline void setPasses(int val) { this->statistics.passes = val; this->computePassAccuracy(); };
        inline void setAccuratePasses(int val) { this->statistics.accurate_passes = val; this->computePassAccuracy(); };
        inline void computePassAccuracy() { this->statistics.pass_accuracy = this->statistics.passes == 0 ? 0 : 100 * this->statistics.accurate_passes / this->statistics.passes; };
        inline void setFouls(int val) { this->statistics.fouls = val; };
        inline void setYellowCards(int val) { this->statistics.yellow_cards = val; };
        inline void setRedCards(int val) { this->statistics.red_cards = val; };

        inline void incrementGoals(int inc = 1) { this->statistics.goals += inc; this->computeShotEfficiency(); };
        inline void incrementPossession(double inc = 1.0) { this->statistics.possession += inc; };
        inline void incrementShots(int inc = 1) { this->statistics.shots += inc; this->computeShotAccuracy(); this->computeShotEfficiency(); };
        inline void incrementShotsOnTarget(int inc = 1) { this->statistics.shots_on_target += inc; this->computeShotAccuracy(); };
        inline void incrementGoalkeeperSaves(int inc = 1) { this->statistics.goalkeeper_saves += inc; };
        inline void incrementOffsides(int inc = 1) { this->statistics.offsides += inc; };
        inline void incrementCorners(int inc = 1) { this->statistics.corners += inc; };
        inline void incrementPasses(int inc = 1) { this->statistics.passes += inc; this->computePassAccuracy(); };
        inline void incrementAccuratePasses(int inc = 1) { this->statistics.accurate_passes += inc; this->computePassAccuracy(); };
        inline void incrementFouls(int inc = 1) { this->statistics.fouls += inc; };
        inline void incrementYellowCards(int inc = 1) { this->statistics.yellow_cards += inc; };
        inline void incrementRedCards(int inc = 1) { this->statistics.red_cards += inc; };

        Player* getBestPlayer(bool, bool) const;
        
        int doSubstitution(int, int, int);
        bool substitution(Player*&, Player*&);
        void decidePositions(char&, char&, int);
        Player*& getSubstitutionOff(char);
        Player*& getSubstitutionOn(char);
        int* Substitutions(int, int, int, int&);
        void printSubstitution(int, int, int, int);
        void printSubstitutions(int*, int, int, int);

        void incrementPlayerPasses(int player, int inc = 1) { if(player >= this->in) return; this->players[player]->incrementPasses(inc); };
        void incrementPlayerAccuratePasses(int player, int inc = 1) { if(player >= this->in) return; this->players[player]->incrementAccuratePasses(inc); };
        
        inline void setType(bool type) { this->type = type; };
        void readName();
        void computeRatings();
        void readTechnicalParameters();
        void readNationality(Countries);
        void readPlayers(Countries);
        void read(Countries, bool);
        
        void print();
        void printPlayerStatistics();
        void incrementMinutesPlayed();

        friend int expected(const Team&, const Team&);

        // Editing functions
        bool editTeam(Countries, const char);
        bool editName(const string);
        bool editType(const bool);
        bool editMorale(const int);
        bool editMood(const int);
        bool editAggressiveness(const int);
        bool editNationality(Country*);
        bool addPlayer(Player*);
        bool removePlayer(const int);
        bool editPlayer(const bool, const int, Player*);
        bool substitutePlayers(const int, const int);
};

int checkPlayersFile(fstream&, const Countries&);
bool interpretError(int error);