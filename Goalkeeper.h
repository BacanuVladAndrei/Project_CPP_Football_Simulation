#include <iostream>
#include <string>
#pragma once
#include "Player.h"
using namespace std;

class Goalkeeper : public Player {
    protected:
        GoalkeeperStats statistics;

    public:
        Goalkeeper() { this->InitStatistics(); };
        Goalkeeper& operator=(const Player&);
        void InitStatistics();
        ~Goalkeeper() {};

        string getFirstName() const;
        string getFamilyName() const;
        Country* getNationality() const;
        string getCtr() const;
        char getPos() const;
        struct tm getBirthDate() const;
        int getAge() const;
        int getCond() const;
        int getRat() const;
        int getStatus() const;
        int getMinsPlayed() const;

        int Cond();
        int incrementMins();

        // Statistics
        inline int getMinutesPlayed() const { return this->statistics.minutes_played; };
        inline int getGoals() const { return -1; };
        inline int getAssists() const { return this->statistics.assists; };
        inline int getShots() const { return -1; };
        inline int getShotsOnTarget() const { return -1; };
        inline double getShotAccuracy() const { return -1.0; };
        inline double getShotEfficiency() const { return -1.0; };
        inline int getOffsides() const { return -1; };
        inline int getPasses() const { return this->statistics.passes; };
        inline int getAccuratePasses() const { return this->statistics.accurate_passes; };
        inline double getPassAccuracy() const { return this->statistics.pass_accuracy; };
        inline int getFoulsCommitted() const { return this->statistics.fouls_committed; };
        inline int getFoulsSuffered() const { return this->statistics.fouls_suffered; };
        inline int getYellowCard() const { return this->statistics.yellow_card; };
        inline int getRedCard() const { return this->statistics.red_card; };
        inline int getGoalsReceived() const { return this->statistics.goals_received; };
        inline int getSaves() const { return this->statistics.saves; };

        inline void setMinutesPlayed(int val) { this->statistics.minutes_played = val; };
        inline void setGoals(int val) {};
        inline void setAssists(int val) { this->statistics.assists = val; };
        inline void setShots(int val) {};
        inline void setShotsOnTarget(int val) {};
        inline void computeShotAccuracy() {};
        inline void computeShotEfficiency() {};
        inline void setOffsides(int val) {};
        inline void setPasses(int val) { this->statistics.passes = val; this->computePassAccuracy(); };
        inline void setAccuratePasses(int val) { this->statistics.accurate_passes = val; this->computePassAccuracy(); };
        inline void computePassAccuracy() { this->statistics.pass_accuracy = this->statistics.passes == 0 ? 0 : 100 * (double)this->statistics.accurate_passes / (double)this->statistics.passes; };
        inline void setFoulsCommitted(int val) { this->statistics.fouls_committed = val; };
        inline void setFoulsSuffered(int val) { this->statistics.fouls_suffered = val; };
        inline void setYellowCard(int val) { this->statistics.yellow_card = val; };
        inline void setRedCard(int val) { this->statistics.red_card = val; };
        inline void setGoalsReceived(int val) { this->statistics.goals_received = val; };
        inline void setSaves(int val) { this->statistics.saves = val; };

        inline virtual void incrementMinutesPlayed(int inc = 1) { this->statistics.minutes_played += inc; };
        inline void incrementGoals(int inc = 1) {};
        inline void incrementAssists(int inc = 1) { this->statistics.assists += inc; };
        inline void incrementShots(int inc = 1) {};
        inline void incrementShotsOnTarget(int inc = 1) {};
        inline void incrementOffsides(int inc = 1) {};
        inline void incrementPasses(int inc = 1) { this->statistics.passes += inc; this->computePassAccuracy(); };
        inline void incrementAccuratePasses(int inc = 1) { this->statistics.accurate_passes += inc; this->computePassAccuracy(); };
        inline void incrementFoulsCommitted(int inc = 1) { this->statistics.fouls_committed += inc; };
        inline void incrementFoulsSuffered(int inc = 1) { this->statistics.fouls_suffered += inc; };
        inline void incrementYellowCard(int inc = 1) { this->statistics.yellow_card += inc; };
        inline void incrementRedCard(int inc = 1) { this->statistics.red_card += inc; };
        inline void incrementGoalsReceived(int inc = 1) { this->statistics.goals_received += inc; };
        inline void incrementSaves(int inc = 1) { this->statistics.saves += inc; };
        
        double getMark();
        int goalChance(int);
        int assistChance(Player*, int);
        int penaltyTakerChance(int);
        int penaltyGuiltyChance(int);
        int shotTakerChance(int);
        int foulChance(int);
        int foulAgainstChance(char);
        int offsideChance();
        int cornerTakerChance();
        int cornerTouchChance();
        int passChance();
        bool accuratePass();

        int print();
        int print(int, int);
        int write(fstream&);
        int write(fstream&, int, int);
};