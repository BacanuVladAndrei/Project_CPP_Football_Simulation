#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "Betting_Application.h"
#include "Administrative_functions.h"
using namespace std;

Match_Odds::Match_Odds()
{
    this->correct_score_h1 = new Odd*[6]();
    this->correct_score_h2 = new Odd*[6]();
    for(int i = 0; i < 6; i++)
    {
        this->correct_score_h1[i] = new Odd[6]();
        this->correct_score_h2[i] = new Odd[6]();
    }

    this->correct_score_ft = new Odd*[10]();
    for(int i = 0; i < 10; i++)
    {
        this->correct_score_ft[i] = new Odd[10]();
    }

    this->home_draw_away = new Odd*[3]();
    for(int i = 0; i < 3; i++)
    {
        this->home_draw_away[i] = new Odd[3]();
    }
}

Match_Odds::~Match_Odds()
{
    for(int i = 0; i < 6; i++)
    {
        delete[] this->correct_score_h1[i];
        delete[] this->correct_score_h2[i];
    }
    delete[] this->correct_score_h1;
    delete[] this->correct_score_h2;

    for(int i = 0; i < 10; i++)
    {
        delete[] this->correct_score_ft[i];
    }
    delete[] this->correct_score_ft;

    for(int i = 0; i < 3; i++)
    {
        delete[] this->home_draw_away[i];
    }
    delete[] this->home_draw_away;
}

double fact(int n)
{
    if(n < 1)
        return 1;
    
    double res = 1;
    for(int i = 0; i < n; i++)
    {
        res = res * (i + 1);
    }

    return res;
}

double Match_Odds::poisson(int k, int total_goals, const Team& team, const Team& opponent, int half)
{
    double l = 0.0;
    total_goals = (total_goals < 1) ? 1 : total_goals;
    if(half == 1)
    {
        l = 402 * total_goals / 470.0;
    }
    if(half == 2)
    {
        l = 540 * total_goals / 470.0;
    }

    double team_rating = (3 * team.getRatingFinal() - 2 * opponent.getRatingFinal()) * (3 * team.getRatingFinal() - 2 * opponent.getRatingFinal()) * (3 * team.getRatingFinal() - 2 * opponent.getRatingFinal()) + 1000 * (2 * team.getFormation().getF() - team.getFormation().getD());
    double opponent_rating = (3 * opponent.getRatingFinal() - 2 * team.getRatingFinal()) * (3 * opponent.getRatingFinal() - 2 * team.getRatingFinal()) * (3 * opponent.getRatingFinal() - 2 * team.getRatingFinal()) + 1000 * (2 * opponent.getFormation().getF() - opponent.getFormation().getD());
    double l_team = team_rating / (team_rating + opponent_rating);

    double pois = exp(-(l * l_team)) * pow(l * l_team, k) / fact(k);

    return pois;
}

void Match_Odds::calculateCorrectScores(int total_goals, const Team& home, const Team& away)
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            this->correct_score_h1[i][j].set(1.0 / (this->poisson(i, total_goals, away, home, 1) * this->poisson(j, total_goals, home, away, 1)));
            this->correct_score_h2[i][j].set(1.0 / (this->poisson(i, total_goals, away, home, 2) * this->poisson(j, total_goals, home, away, 2)));
        }
    }

    for(int i1 = 0; i1 < 6; i1++)
    {
        for(int j1 = 0; j1 < 6; j1++)
        {
            for(int i2 = 0; i2 < 6; i2++)
            {
                for(int j2 = 0; j2 < 6; j2++)
                {
                    if(((i1 + i2) < 10) && ((j2 + j1) < 10))
                    {
                        this->correct_score_ft[i1 + i2][j1 + j2] = (this->correct_score_ft[i1 + i2][j1 + j2]) + ((this->correct_score_h1[i1][j1]) * (this->correct_score_h2[i2][j2]));
                        this->correct_score_ft[i1 + i2][j1 + j2].print(6, 2);
                    }
                }
            }
        }
    }

    this->printCorrectScoreFT();
}

void Match_Odds::printCorrectScoreH1() const
{
    cout << "                H       O       M       E" << endl;
    cout << "        0       1       2       3       4       5" << endl;
    for(int i = 0; i < 6; i++)
    {
        switch(i){
            case 1: {cout << "A "; break;}
            case 2: {cout << "W "; break;}
            case 3: {cout << "A "; break;}
            case 4: {cout << "Y "; break;}
            default: {cout << "  "; break;}
        }
        cout << i << "  ";
        for(int j = 0; j < 6; j++)
        {
            this->correct_score_h1[i][j].print(6, 2);
            cout << "  ";
        }
        cout << endl;
    }
}

void Match_Odds::printCorrectScoreH2() const
{
    cout << "                H       O       M       E" << endl;
    cout << "        0       1       2       3       4       5" << endl;
    for(int i = 0; i < 6; i++)
    {
        switch(i){
            case 1: {cout << "A "; break;}
            case 2: {cout << "W "; break;}
            case 3: {cout << "A "; break;}
            case 4: {cout << "Y "; break;}
            default: {cout << "  "; break;}
        }
        cout << i << "  ";
        for(int j = 0; j < 6; j++)
        {
            this->correct_score_h2[i][j].print(6, 2);
            cout << "  ";
        }
        cout << endl;
    }
}

void Match_Odds::printCorrectScoreFT() const
{
    cout << "                                H       O       M       E" << endl;
    cout << "        0       1       2       3       4       5       6       7       8       9" << endl;
    for(int i = 0; i < 10; i++)
    {
        switch(i){
            case 3: {cout << "A "; break;}
            case 4: {cout << "W "; break;}
            case 5: {cout << "A "; break;}
            case 6: {cout << "Y "; break;}
            default: {cout << "  "; break;}
        }
        cout << i << "  ";
        for(int j = 0; j < 10; j++)
        {
            this->correct_score_ft[i][j].print(6, 2);
            cout << "  ";
        }
        cout << endl;
    }
}