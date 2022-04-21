#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "Team.h"
#pragma once
using namespace std;

class Odd;

class Match_Odds {
    protected:
        Odd** home_draw_away; // 3-by-3 matrix, columns {X 1 2}, lines {X 1 2}
        Odd** correct_score_ft; // 10-by-10 matrix, columns {*total home scoring* 0 ... 9}, lines {*total away scoring* 0 ... 9}
        Odd** correct_score_h1; // 6-by-6 matrix, columns {*1st half home scoring* 0 ... 5}, lines {*1st half away scoring* 0 ... 5}
        Odd** correct_score_h2; // 6-by-6 matrix, columns {*2nd half home scoring* 0 ... 5}, lines {*2nd half away scoring* 0 ... 5}

    public:
        Match_Odds();
        ~Match_Odds();

        double poisson(int, int, const Team&, const Team&, int);

        void calculateCorrectScores(int, const Team&, const Team&);
        void printCorrectScoreH1() const;
        void printCorrectScoreH2() const;
        void printCorrectScoreFT() const;
        void writeCorrectScoreH1(fstream&) const;
        void writeCorrectScoreH2(fstream&) const;
        void writeCorrectScoreFT(fstream&) const;

        void computeHomeDrawAway();
};

class Odd {
    protected:
        double odd;

    public:
        Odd();
        explicit Odd(double);
        Odd(const Odd&);
        Odd& operator=(const Odd&);
        ~Odd() {};

        void set(const double);
        double get() const;
        double chance() const;

        friend istream& operator>>(istream&, Odd&);
        friend ostream& operator<<(ostream&, const Odd&);
        friend fstream& operator<<(fstream&, const Odd&);
        void print(int, int) const;
        fstream& print(fstream&, int, int) const;

        friend Odd operator+(const Odd&, const Odd&);
        friend Odd operator-(const Odd&, const Odd&);
        friend Odd operator*(const Odd&, const Odd&);
        friend Odd operator/(const Odd&, const Odd&);
        Odd& operator+=(const Odd&);
        Odd& operator-=(const Odd&);
        Odd& operator*=(const Odd&);
        Odd& operator/=(const Odd&);

        friend bool operator==(const Odd&, const Odd&);
        friend bool operator!=(const Odd&, const Odd&);
        friend bool operator>(const Odd&, const Odd&);
        friend bool operator<(const Odd&, const Odd&);
        friend bool operator<=(const Odd&, const Odd&);
        friend bool operator>=(const Odd&, const Odd&);
};

class Bet {
    protected:
        Odd o;
        bool status;
    public:
        Bet();
        Bet(const Odd&, bool);
        Bet(double, bool);
        Bet(const Bet&);
        Bet& operator=(const Bet&);
        ~Bet() {};

        Odd getOdd() const;
        void setOdd(const Odd&);
        bool getStatus() const;
        void setStatus(bool);

        friend ostream& operator<<(ostream&, const Bet&);
        friend fstream& operator<<(fstream&, const Bet&);

        virtual void read() {};
        virtual void print() { cout << (*this); };
        virtual void write(fstream& stro) { stro << (*this); };
        virtual int getType() { return 0; }; 
        virtual bool Check() { return false; };
};

class Bet_1X2 : public Bet {
    protected:
        bool home_wins;
        bool draw;
        bool away_wins;
    public:
        Bet_1X2();
        Bet_1X2(bool, bool, bool);
        ~Bet_1X2() {};

        void read();
        void print(bool);
        void write(fstream&, bool);
        int getType() { return 1; };
        bool Check(const Team&, const Team&);
};