#include <iostream>
#include <string>
#pragma once
#include "Player.h"
using namespace std;

class Forward : public Player {
    protected:
        PlayerStats statistics;
    
    public:
        Forward() { this->InitStatistics(); };
        Forward& operator=(const Player&);
        void InitStatistics();
        ~Forward() {};

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

        inline int getMinutesPlayed() const { return this->statistics.minutes_played; };
        inline int getGoals() const { return this->statistics.goals; };
        inline int getAssists() const { return this->statistics.assists; };
        inline int getShots() const { return this->statistics.shots; };
        inline int getShotsOnTarget() const { return this->statistics.shots_on_target; };
        inline double getShotAccuracy() const { return this->statistics.shot_accuracy; };
        inline double getShotEfficiency() const { return this->statistics.shot_efficiency; };
        inline int getOffsides() const { return this->statistics.offsides; };
        inline int getPasses() const { return this->statistics.passes; };
        inline int getAccuratePasses() const { return this->statistics.accurate_passes; };
        inline double getPassAccuracy() const { return this->statistics.pass_accuracy; };
        inline int getFoulsCommitted() const { return this->statistics.fouls_committed; };
        inline int getFoulsSuffered() const { return this->statistics.fouls_suffered; };
        inline int getYellowCard() const { return this->statistics.yellow_card; };
        inline int getRedCard() const { return this->statistics.red_card; };
        inline int getGoalsReceived() const { return -1; };
        inline int getSaves() const { return -1; };

        inline void setMinutesPlayed(int val) { this->statistics.minutes_played = val; };
        inline void setGoals(int val) { this->statistics.goals = val; this->computeShotEfficiency(); };
        inline void setAssists(int val) { this->statistics.assists = val; };
        inline void setShots(int val) { this->statistics.shots = val; this->computeShotAccuracy(); this->computeShotEfficiency(); };
        inline void setShotsOnTarget(int val) { this->statistics.shots_on_target = val; this->computeShotAccuracy(); };
        inline void computeShotAccuracy() { this->statistics.shot_accuracy = this->statistics.shots == 0 ? 0 : 100 * (double)this->statistics.shots_on_target / (double)this->statistics.shots; };
        inline void computeShotEfficiency() { this->statistics.shot_efficiency = this->statistics.shots == 0 ? 0 : 100 * (double)this->statistics.goals / (double)this->statistics.shots; };
        inline void setOffsides(int val) { this->statistics.offsides = val; };
        inline void setPasses(int val) { this->statistics.passes = val; this->computePassAccuracy(); };
        inline void setAccuratePasses(int val) { this->statistics.accurate_passes = val; this->computePassAccuracy(); };
        inline void computePassAccuracy() { this->statistics.pass_accuracy = this->statistics.passes == 0 ? 0 : 100 * (double)this->statistics.accurate_passes / (double)this->statistics.passes; };
        inline void setFoulsCommitted(int val) { this->statistics.fouls_committed = val; };
        inline void setFoulsSuffered(int val) { this->statistics.fouls_suffered = val; };
        inline void setYellowCard(int val) { this->statistics.yellow_card = val; };
        inline void setRedCard(int val) { this->statistics.red_card = val; };
        inline void setGoalsReceived(int val) {};
        inline void setSaves(int val) {};

        inline virtual void incrementMinutesPlayed(int inc = 1) { this->statistics.minutes_played += inc; };
        inline void incrementGoals(int inc = 1) { this->statistics.goals += inc; this->computeShotEfficiency(); };
        inline void incrementAssists(int inc = 1) { this->statistics.assists += inc; };
        inline void incrementShots(int inc = 1) { this->statistics.shots += inc; this->computeShotAccuracy(); this->computeShotEfficiency(); };
        inline void incrementShotsOnTarget(int inc = 1) { this->statistics.shots_on_target += inc; this->computeShotAccuracy(); };
        inline void incrementOffsides(int inc = 1) { this->statistics.offsides += inc; };
        inline void incrementPasses(int inc = 1) { this->statistics.passes += inc; this->computePassAccuracy(); };
        inline void incrementAccuratePasses(int inc = 1) { this->statistics.accurate_passes += inc; this->computePassAccuracy(); };
        inline void incrementFoulsCommitted(int inc = 1) { this->statistics.fouls_committed += inc; };
        inline void incrementFoulsSuffered(int inc = 1) { this->statistics.fouls_suffered += inc; };
        inline void incrementYellowCard(int inc = 1) { this->statistics.yellow_card += inc; };
        inline void incrementRedCard(int inc = 1) { this->statistics.red_card += inc; };
        inline void incrementGoalsReceived(int inc = 1) {};
        inline void incrementSaves(int inc = 1) {};
        
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