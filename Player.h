#include <iostream>
#include <string>
#pragma once
#include "Country.h"
using namespace std;

struct PlayerStats {
    int minutes_played;
    int goals;
    int assists;
    int shots;
    int shots_on_target;
    double shot_accuracy; // shots_on_target / shots
    double shot_efficiency; // goals / shots
    int offsides;
    int passes;
    int accurate_passes;
    double pass_accuracy; // accurate_passes / passes
    int fouls_committed;
    int fouls_suffered;
    int yellow_card;
    int red_card;
};

struct GoalkeeperStats {
    int minutes_played;
    int goals_received;
    int saves;
    int assists;
    int passes;
    int accurate_passes;
    double pass_accuracy;
    int fouls_committed;
    int fouls_suffered;
    int yellow_card;
    int red_card;
};

class Player{
    protected:
        string first_name;
        string family_name;
        Country *nationality;
        string ctr;
        char pos;
        struct tm birth_date;
        int age;
        int cond;
        int rat;
        int on;
        int mins_played;

    public:
        Player();
        Player(string, string, Country*, char, struct tm, int, int, int);
        Player& operator=(const Player&);
        virtual void InitStatistics() {};
        virtual ~Player() {};

        int read(fstream&, Countries);
        int read(Countries, bool, bool, bool);
        virtual int write(fstream&);
        virtual int write(fstream&, int, int);
        virtual int print();
        virtual int print(int, int);

        virtual string getFirstName() const;
        virtual string getFamilyName() const;
        virtual Country* getNationality() const;
        virtual string getCtr() const;
        virtual char getPos() const;
        virtual struct tm getBirthDate() const;
        virtual int getAge() const;
        virtual int getCond() const;
        virtual int getRat() const;
        virtual int getStatus() const;
        void setStatus(int status = 0) { this->on = status; };
        virtual int getMinsPlayed() const;

        // Statistics
        inline virtual int getMinutesPlayed() const { return 0; };
        inline virtual int getGoals() const { return 0; };
        inline virtual int getAssists() const { return 0; };
        inline virtual int getShots() const { return 0; };
        inline virtual int getShotsOnTarget() const { return 0; };
        inline virtual double getShotAccuracy() const { return 0.0; };
        inline virtual double getShotEfficiency() const { return 0.0; };
        inline virtual int getOffsides() const { return 0; };
        inline virtual int getPasses() const { return 0; };
        inline virtual int getAccuratePasses() const { return 0; };
        inline virtual double getPassAccuracy() const { return 0.0; };
        inline virtual int getFoulsCommitted() const { return 0; };
        inline virtual int getFoulsSuffered() const { return 0; };
        inline virtual int getYellowCard() const { return 0; };
        inline virtual int getRedCard() const { return 0; };
        inline virtual int getGoalsReceived() const { return 0; };
        inline virtual int getSaves() const { return 0; };

        inline virtual void setMinutesPlayed(int val) {};
        inline virtual void setGoals(int val) {};
        inline virtual void setAssists(int val) {};
        inline virtual void setShots(int val) {};
        inline virtual void setShotsOnTarget(int val) {};
        inline virtual void computeShotAccuracy() {};
        inline virtual void computeShotEfficiency() {};
        inline virtual void setOffsides(int val) {};
        inline virtual void setPasses(int val) {};
        inline virtual void setAccuratePasses(int val) {};
        inline virtual void computePassAccuracy() {};
        inline virtual void setFoulsCommitted(int val) {};
        inline virtual void setFoulsSuffered(int val) {};
        inline virtual void setYellowCard(int val) {};
        inline virtual void setRedCard(int val) {};
        inline virtual void setGoalsReceived(int val) {};
        inline virtual void setSaves(int val) {};

        inline virtual void incrementMinutesPlayed(int inc = 1) {};
        inline virtual void incrementGoals(int inc = 1) {};
        inline virtual void incrementAssists(int inc = 1) {};
        inline virtual void incrementShots(int inc = 1) {};
        inline virtual void incrementShotsOnTarget(int inc = 1) {};
        inline virtual void incrementOffsides(int inc = 1) {};
        inline virtual void incrementPasses(int inc = 1) {};
        inline virtual void incrementAccuratePasses(int inc = 1) {};
        inline virtual void incrementFoulsCommitted(int inc = 1) {};
        inline virtual void incrementFoulsSuffered(int inc = 1) {};
        inline virtual void incrementYellowCard(int inc = 1) {};
        inline virtual void incrementRedCard(int inc = 1) {};
        inline virtual void incrementGoalsReceived(int inc = 1) {};
        inline virtual void incrementSaves(int inc = 1) {};

        virtual void printStatistics(int);

        virtual int Cond();
        virtual int incrementMins();
        bool operator<(const Player&);

        int Age();
        virtual double getMark();
        virtual int goalChance(int);
        virtual int assistChance(Player*, int);
        virtual int penaltyTakerChance(int);
        virtual int penaltyGuiltyChance(int);
        virtual int shotTakerChance(int);
        virtual int foulChance(int);
        virtual int foulAgainstChance(char);
        virtual int offsideChance();
        virtual int cornerTakerChance();
        virtual int cornerTouchChance();
        int chancesSubstitutionOff(int);
        int chancesSubstitutionOn(int);
        virtual int passChance();
        virtual bool accuratePass();
        int err();

        friend vector<Player*> read_players(fstream&, Countries, int&, int, bool);
        friend int maxNameLength(vector<Player*>, int);
        friend int printPlayersTable(vector<Player*>, int);
        friend int writePlayersTable(fstream&, vector<Player*>, int);
};