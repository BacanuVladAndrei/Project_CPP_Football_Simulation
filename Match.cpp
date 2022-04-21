#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Match.h"
#include "Passes.h"
#include "Administrative_functions.h"
using namespace std;

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#ifndef EXPECTED_PARAMETERS_H
#define EXPECTED_PARAMETERS_H

exp_Events* getExpectedParameters(const Team& home, const Team& away)
{
    exp_Events* expected = new exp_Events;

    expected->exp_Corners = expectedCorners(home, away);
    expected->exp_Offsides = expectedOffsides(home, away);
    expected->exp_Fouls = expectedFouls(home, away);
    expected->exp_Goals = expectedGoals(home, away);
    expected->exp_Shots = expectedShots(home, away);
    expected->exp_Passes = expectedPasses();

    return expected;
}

#endif

void Match::prepareMatch(Team* home, Team* away, Stadium* stadium, Referees* referees, Weather* weather)
{
    this->active = false;
    this->home_t = home;
    this->away_t = away;
    this->stadium = stadium;
    this->referees = referees;
    this->weather = weather;
    this->mins_half1 = 45 + rand() % 8;
    this->mins_half2 = 45 + rand() % 8;
    this->mins_extratime1 = 0;
    this->mins_extratime2 = 0;
    this->expected_events = getExpectedParameters(*home, *away);
    this->ShootOut = NULL;
    this->home_t->initStatistics();
    this->away_t->initStatistics();
    this->CoinToss();
}

void Match::KickOff(int half)
{
    bool who_kicks_off = half % 2 ? this->kick_off1 : (!this->kick_off1);
    cout << "The teams are ready!" << endl;
    cout << "Press K to kick off! ";
    option("Kk");
    cout << endl;

    this->active = true;

    if(who_kicks_off)
    {
        cout << this->away_t->getName() << " kicks off in the ";
    }
    else
    {
        cout << this->home_t->getName() << " kicks off in the ";
    }
    switch(half)
    {
        case 1:
        {
            cout << "first half!" << endl;
            break;
        }
        case 2:
        {
            cout << "second half!" << endl;
            break;
        }
        case 3:
        {
            cout << "first extra half!" << endl;
            break;
        }
        case 4:
        {
            cout << "second extra half!" << endl;
            break;
        }
        default:
        {
            cout << "[error]!" << endl;
            break;
        }
    }
}

void Match::finalWhistle(int half)
{
    if(half % 2)
    {
        cout << "Half-time whistle!" << endl;
    }
    else
    {
        cout << "Full-time whistle!" << endl;
    }

    this->active = false;
}

void Match::printTeamStatistics(const Team& home, const Team& away)
{
    cout << "               --- TEAM STATISTICS ---" << endl << endl;

    cout << "                    HOME  -  AWAY" << endl;
    cout << "Goals:            " << setw(7) << home.getGoals() << " - " << away.getGoals() << endl;
    cout << "Possession:       " << setw(6) << setprecision(2) << fixed << home.getPossession() << "% - " << setprecision(2) << fixed << away.getPossession() << "%" << endl;
    cout << "Shots:            " << setw(7) << home.getShots() << " - " << away.getShots() << endl;
    cout << "Shots on target:  " << setw(7) << home.getShotsOnTarget() << " - " << away.getShotsOnTarget() << endl;
    cout << "Shot accuracy:   " << setw(7) << setprecision(2) << fixed << (double)home.getShotAccuracy() << "% - " << setprecision(2) << fixed << (double)away.getShotAccuracy() << "%" << endl;
    cout << "Shot efficiency: " << setw(7) << setprecision(2) << fixed << (double)home.getShotEfficiency() << "% - " << setprecision(2) << fixed << (double)away.getShotEfficiency() << "%" << endl;
    cout << "Goalkeeper saves: " << setw(7) << home.getGoalkeeperSaves() << " - " << away.getGoalkeeperSaves() << endl;
    cout << "Offsides:         " << setw(7) << home.getOffsides() << " - " << away.getOffsides() << endl;
    cout << "Corners:          " << setw(7) << home.getCorners() << " - " << away.getCorners() << endl;
    cout << "Passes:           " << setw(7) << home.getPasses() << " - " << away.getPasses() << endl;
    cout << "Accurate passes:  " << setw(7) << home.getAccuratePasses() << " - " << away.getAccuratePasses() << endl;
    cout << "Pass accuracy:   " << setw(7) << setprecision(2) << fixed << (double)home.getPassAccuracy() << "% - " << setprecision(2) << fixed << (double)away.getPassAccuracy() << "%" << endl;
    cout << "Fouls:            " << setw(7) << home.getFouls() << " - " << away.getFouls() << endl;
    cout << "Yellow cards:     " << setw(7) << home.getYellowCards() << " - " << away.getYellowCards() << endl;
    cout << "Red cards:        " << setw(7) << home.getRedCards() << " - " << away.getRedCards() << endl;
}

void Match::match()
{
    int cooldown = 1;
    Minute new_minute;
    KickOff(1);
    
    int* first_half_passes = calculatePassesEachMinute(this->expected_events->exp_Passes / 2, this->mins_half1);
    for(int i = 0; i < this->mins_half1; i++)
    {
        getche();
        this->Half1.push_back(new_minute);
        cout << "Min. " << i + 1 << endl;
        this->Half1[i].setMinute(1, i + 1);
        this->Half1[i].minute(*(this->home_t), *(this->away_t), this->expected_events, this->mins_half1 + 45 - i, this->mins_half1, cooldown, passesThisMinute(i + 1, first_half_passes, this->mins_half1));
    }
    delete[] first_half_passes;

    finalWhistle(1);

    KickOff(2);

    int* second_half_passes = calculatePassesEachMinute(this->expected_events->exp_Passes / 2, this->mins_half2);
    for(int i = 0; i < this->mins_half2; i++)
    {
        getche();
        this->Half2.push_back(new_minute);
        cout << "Min. " << i + 46 << endl;
        this->Half2[i].setMinute(2, i + 1);
        this->Half2[i].minute(*(this->home_t), *(this->away_t), this->expected_events, this->mins_half2 - i + 20, this->mins_half2, cooldown, passesThisMinute(i + 1, second_half_passes, this->mins_half2));
    }
    delete[] second_half_passes;

    finalWhistle(2);

    cout << endl << endl;
    // this->home_t->printPlayerStatistics();
    cout << endl;
    // this->away_t->printPlayerStatistics();

    this->printTeamStatistics(*(this->home_t), *(this->away_t));
}

void Match::preview()
{
    //                                               |
    //                                            STADIUM
    //                                         [Stadium name]
    //                                       [Stadium location]
    //                                     [Attend] / [Capacity]
    //                                           LP$ - HP$
    //                                      
    //                                     [Weather description]
    //                                         [Temperature]
    //
    // HOME TEAM                                     |   AWAY TEAM
    // Name: home_team_name                          |   Name: away_team_name
    // Nationality: home_team_nationality            |   Nationality: away_team_nationality
    // Rating: rat                                   |   Rating: rat
    // Morale: hm                                    |   Morale: am
    // Defensive / Offensive: hs                     |   Defensive / Offensive: as
    // Aggressiveness: ha                            |   Aggressiveness: aa
    // Formation: h_f_0                              |   Formation: a_f_0
    //                                               |
    // PLAYERS                                       |   PLAYERS
    // P  Nat  F. Name             Rat  Birth date   |   P  Nat  F. Name             Rat  Birth date
    // ...........................................   |   ...........................................
    //                                               |
    // SUBSTITUTES                                   |   SUBSTITUTES
    // P  Nat  F. Name             Rat  Birth date   |   P  Nat  F. Name             Rat  Birth date
    // ...........................................   |   ...........................................
    // |               width home                |               |   width_away   |
    //
    //                                            REFEREES
    //                                            Central
    //                                          Assistant 1
    //                                          Assistant 2
    //                                          4th Official
    //                                             VAR 1
    //                                             VAR 2
    //                                               |

    int width_home = 18;
    int width_away = 18;

    for(int i = 0; i < this->home_t->getPlayers().size(); i++)
    {
        if(this->home_t->getPlayer(i)->getFamilyName().length() + 3 > width_home)
        {
            width_home = this->home_t->getPlayer(i)->getFamilyName().length() + 3;
        }
    }

    for(int i = 0; i < this->home_t->getSubstitutes().size(); i++)
    {
        if(this->home_t->getSubstitute(i)->getFamilyName().length() + 3 > width_home)
        {
            width_home = this->home_t->getSubstitute(i)->getFamilyName().length() + 3;
        }
    }

    width_home = width_home + 25;

    if(this->home_t->getNationality()->getName().length() > 30)
    {
        width_home = width_home + this->home_t->getNationality()->getName().length() - 30;
    }

    if(this->home_t->getName().length() > 37)
    {
        width_home = width_home + this->home_t->getName().length() - 37;
    }

    for(int i = 0; i < this->away_t->getPlayers().size(); i++)
    {
        if(this->away_t->getPlayer(i)->getFamilyName().length() + 3 > width_away)
        {
            width_away = this->away_t->getPlayer(i)->getFamilyName().length() + 3;
        }
    }

    for(int i = 0; i < this->away_t->getSubstitutes().size(); i++)
    {
        if(this->away_t->getSubstitute(i)->getFamilyName().length() + 3 > width_away)
        {
            width_away = this->away_t->getSubstitute(i)->getFamilyName().length() + 3;
        }
    }

    fillSpaces(width_home - 6);
    cout << "---MATCH PREVIEW---" << endl << endl;

    // Preview stadium
    string to_print;
    fillSpaces(width_home);
    cout << "STADIUM" << endl;
    
    to_print = this->stadium->getName();
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = this->stadium->getLocation() + ", " + this->stadium->getCountry()->getName();
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

        // Compute attendance / capacity as string
        to_print.clear();
        if(this->stadium->getAttendance() / 1000)
        {
            to_print = to_string(this->stadium->getAttendance() / 1000) + ",";
            if(this->stadium->getAttendance() % 1000 < 10)
            {
                to_print += "00";
                to_print += to_string(this->stadium->getAttendance() % 1000);
            }
            else
            {
                if(this->stadium->getAttendance() % 1000 < 100)
                {
                    to_print += "0";
                    to_print += to_string(this->stadium->getAttendance() % 1000);
                }
                else
                {
                    to_print += to_string(this->stadium->getAttendance() % 1000);
                }
            }
        }
        else
        {
            to_print = to_string(this->stadium->getAttendance());
        }

        to_print += " / ";

        if(this->stadium->getCapacity() / 1000)
        {
            to_print += to_string(this->stadium->getCapacity() / 1000) + ",";
            if(this->stadium->getCapacity() % 1000 < 10)
            {
                to_print += "00";
                to_print += to_string(this->stadium->getCapacity() % 1000);
            }
            else
            {
                if(this->stadium->getCapacity() % 1000 < 100)
                {
                    to_print += "0";
                    to_print += to_string(this->stadium->getCapacity() % 1000);
                }
                else
                {
                    to_print += to_string(this->stadium->getCapacity() % 1000);
                }
            }
        }
        else
        {
            to_print += to_string(this->stadium->getCapacity());
        }

        fillSpaces(width_home - (to_print.length() - 7) / 2);
        cout << to_print << endl;

    string l_price = to_string(this->stadium->getLowestPrice());
    string h_price = to_string(this->stadium->getHighestPrice());
    to_print = l_price.substr(0, l_price.find('.') + 3) + "$ - " + h_price.substr(0, h_price.find('.') + 3) + "$";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl << endl;

    // Preview weather
    to_print = this->weather->describeWeather();
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = to_string(this->weather->getTemperature());
    if(to_print.find('.') != string::npos)
    {
        to_print = to_print.substr(0, to_print.find('.') + 3);
    }
    to_print += "*C";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl << endl;

    // Preview teams
    cout << "HOME TEAM";
    fillSpaces(width_home - 9);
    cout << "   |   AWAY TEAM" << endl;

    cout << "Name: " << this->home_t->getName();
    fillSpaces(width_home - 6 - this->home_t->getName().length());
    cout << "   |   Name: " << this->away_t->getName() << endl;

    cout << "Nationality: " << this->home_t->getNationality()->getName();
    fillSpaces(width_home - 13 - this->home_t->getNationality()->getName().length());
    cout << "   |   Nationality: " << this->away_t->getNationality()->getName() << endl;

    to_print = "Rating: " + to_string(this->home_t->getRatingTotal());
    if(to_print.find('.') != string::npos)
    {
        to_print = to_print.substr(0, to_print.find('.') + 3);
    }
    cout << to_print;
    fillSpaces(width_home - to_print.length());
    cout << "   |   Rating: " << setprecision(2) << fixed << this->away_t->getRatingTotal() << endl;

    to_print = "Morale: " + to_string(this->home_t->getMorale());
    cout << to_print;
    fillSpaces(width_home - to_print.length());
    cout << "   |   Morale: " << this->away_t->getMorale() << endl;

    to_print = "Defensive / Offensive: " + to_string(this->home_t->getMood());
    cout << to_print;
    fillSpaces(width_home - to_print.length());
    cout << "   |   Defensive / Offensive: " << this->away_t->getMood() << endl;

    to_print = "Aggressiveness: " + to_string(this->home_t->getAgg());
    cout << to_print;
    fillSpaces(width_home - to_print.length());
    cout << "   |   Aggressiveness: " << this->away_t->getAgg() << endl;

    cout << "Formation: " << this->home_t->getFormation();
    fillSpaces(width_home - 16);
    cout << "   |   Formation: " << this->away_t->getFormation() << endl << endl;

    cout << "STARTING LINE-UP";
    fillSpaces(width_home - 16);
    cout << "   |   STARTING LINE-UP" << endl;

    cout << "P  Nat  Full name";
    fillSpaces(width_home - 34);
    cout << "  Rat  Birth date   |   P  Nat  Full name";
    fillSpaces(width_away - 9);
    cout << "  Rat  Birth date" << endl;

    for(int i = 0; i < 11; i++)
    {
        cout << this->home_t->getPlayer(i)->getPos() << "  " << this->home_t->getPlayer(i)->getNationality()->getCode() << "  ";
        cout << this->home_t->getPlayer(i)->getFirstName()[0] << ". " << this->home_t->getPlayer(i)->getFamilyName();
        fillSpaces(width_home - 28 - this->home_t->getPlayer(i)->getFamilyName().length());
        cout << "  " << setw(3) << this->home_t->getPlayer(i)->getRat() << "   ";
        if(this->home_t->getPlayer(i)->getBirthDate().tm_mday < 10)
        {
            cout << "0" << this->home_t->getPlayer(i)->getBirthDate().tm_mday << "/";
        }
        else
        {
            cout << this->home_t->getPlayer(i)->getBirthDate().tm_mday << "/";
        }
        if(this->home_t->getPlayer(i)->getBirthDate().tm_mon < 10)
        {
            cout << "0" << this->home_t->getPlayer(i)->getBirthDate().tm_mon << "/";
        }
        else
        {
            cout << this->home_t->getPlayer(i)->getBirthDate().tm_mon << "/";
        }
        if(this->home_t->getPlayer(i)->getBirthDate().tm_year % 100 < 10)
        {
            cout << "0" << this->home_t->getPlayer(i)->getBirthDate().tm_year % 100 << " ";
        }
        else
        {
            cout << this->home_t->getPlayer(i)->getBirthDate().tm_year % 100 << " ";
        }
        cout << "   |   ";

        cout << this->away_t->getPlayer(i)->getPos() << "  " << this->away_t->getPlayer(i)->getNationality()->getCode() << "  ";
        cout << this->away_t->getPlayer(i)->getFirstName()[0] << ". " << this->away_t->getPlayer(i)->getFamilyName();
        fillSpaces(width_away - 3 - this->away_t->getPlayer(i)->getFamilyName().length());
        cout << "  " << setw(3) << this->away_t->getPlayer(i)->getRat() << "   ";
        if(this->away_t->getPlayer(i)->getBirthDate().tm_mday < 10)
        {
            cout << "0" << this->away_t->getPlayer(i)->getBirthDate().tm_mday << "/";
        }
        else
        {
            cout << this->away_t->getPlayer(i)->getBirthDate().tm_mday << "/";
        }
        if(this->away_t->getPlayer(i)->getBirthDate().tm_mon < 10)
        {
            cout << "0" << this->away_t->getPlayer(i)->getBirthDate().tm_mon << "/";
        }
        else
        {
            cout << this->away_t->getPlayer(i)->getBirthDate().tm_mon << "/";
        }
        if(this->away_t->getPlayer(i)->getBirthDate().tm_year % 100 < 10)
        {
            cout << "0" << this->away_t->getPlayer(i)->getBirthDate().tm_year % 100 << endl;
        }
        else
        {
            cout << this->away_t->getPlayer(i)->getBirthDate().tm_year % 100 << endl;
        }
    }

    cout << endl << "SUBSTITUTES";
    fillSpaces(width_home - 11);
    cout << "   |   SUBSTITUTES" << endl;

    cout << "P  Nat  Full name";
    fillSpaces(width_home - 34);
    cout << "  Rat  Birth date   |   P  Nat  Full name";
    fillSpaces(width_away - 9);
    cout << "  Rat  Birth date" << endl;

    int max_length = max<int>(this->home_t->getSubstitutes().size(), this->away_t->getSubstitutes().size());
    for(int i = 0; i < max_length; i++)
    {
        if(i < this->home_t->getSubstitutes().size())
        {
            cout << this->home_t->getSubstitute(i)->getPos() << "  " << this->home_t->getSubstitute(i)->getNationality()->getCode() << "  ";
            cout << this->home_t->getSubstitute(i)->getFirstName()[0] << ". " << this->home_t->getSubstitute(i)->getFamilyName();
            fillSpaces(width_home - 28 - this->home_t->getSubstitute(i)->getFamilyName().length());
            cout << "  " << setw(3) << this->home_t->getSubstitute(i)->getRat() << "   ";
            if(this->home_t->getSubstitute(i)->getBirthDate().tm_mday < 10)
            {
                cout << "0" << this->home_t->getSubstitute(i)->getBirthDate().tm_mday << "/";
            }
            else
            {
                cout << this->home_t->getSubstitute(i)->getBirthDate().tm_mday << "/";
            }
            if(this->home_t->getSubstitute(i)->getBirthDate().tm_mon < 10)
            {
                cout << "0" << this->home_t->getSubstitute(i)->getBirthDate().tm_mon << "/";
            }
            else
            {
                cout << this->home_t->getSubstitute(i)->getBirthDate().tm_mon << "/";
            }
            if(this->home_t->getSubstitute(i)->getBirthDate().tm_year % 100 < 10)
            {
                cout << "0" << this->home_t->getSubstitute(i)->getBirthDate().tm_year % 100 << " ";
            }
            else
            {
                cout << this->home_t->getSubstitute(i)->getBirthDate().tm_year % 100 << " ";
            }
        }
        else
        {
            fillSpaces(width_home);
        }
         
        cout << "   |   ";
        
        if(i < this->away_t->getSubstitutes().size())
        {
            cout << this->away_t->getSubstitute(i)->getPos() << "  " << this->away_t->getSubstitute(i)->getNationality()->getCode() << "  ";
            cout << this->away_t->getSubstitute(i)->getFirstName()[0] << ". " << this->away_t->getSubstitute(i)->getFamilyName();
            fillSpaces(width_away - 3 - this->away_t->getSubstitute(i)->getFamilyName().length());
            cout << "  " << setw(3) << this->away_t->getSubstitute(i)->getRat() << "   ";
            if(this->away_t->getSubstitute(i)->getBirthDate().tm_mday < 10)
            {
                cout << "0" << this->away_t->getSubstitute(i)->getBirthDate().tm_mday << "/";
            }
            else
            {
                cout << this->away_t->getSubstitute(i)->getBirthDate().tm_mday << "/";
            }
            if(this->away_t->getSubstitute(i)->getBirthDate().tm_mon < 10)
            {
                cout << "0" << this->away_t->getSubstitute(i)->getBirthDate().tm_mon << "/";
            }
            else
            {
                cout << this->away_t->getSubstitute(i)->getBirthDate().tm_mon << "/";
            }
            if(this->away_t->getSubstitute(i)->getBirthDate().tm_year % 100 < 10)
            {
                cout << "0" << this->away_t->getSubstitute(i)->getBirthDate().tm_year % 100 << endl;
            }
            else
            {
                cout << this->away_t->getSubstitute(i)->getBirthDate().tm_year % 100 << endl;
            }
        }
        else
        {
            cout << endl;
        }
    }
    cout << endl;

    // Preview referees
    to_print = "REFEREES";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = "Central: " + this->referees->getMain().getName() + " (" + this->referees->getMain().getNationality()->getCode() + ")";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = "Assistant 1: " + this->referees->getAss1().getName() + " (" + this->referees->getAss1().getNationality()->getCode() + ")";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = "Assistant 2: " + this->referees->getAss2().getName() + " (" + this->referees->getAss2().getNationality()->getCode() + ")";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = "4th Official: " + this->referees->getSide().getName() + " (" + this->referees->getSide().getNationality()->getCode() + ")";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = "VAR 1: " + this->referees->getVAR1().getName() + " (" + this->referees->getVAR1().getNationality()->getCode() + ")";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl;

    to_print = "VAR 2: " + this->referees->getVAR2().getName() + " (" + this->referees->getVAR2().getNationality()->getCode() + ")";
    fillSpaces(width_home - (to_print.length() - 7) / 2);
    cout << to_print << endl << endl;

}

bool Match::editMatch(Countries countries)
{
    cout << "MATCH EDITOR" << endl << endl;
    cout << "Select an option:" << endl;
    cout << "    H - Edit home team" << endl;
    cout << "    A - Edit away team" << endl;
    cout << "    S - Edit stadium" << endl;
    cout << "    R - Edit referees" << endl;
    cout << "    W - Re-evaluate weather" << endl;
    cout << "Option: ";
    char opt = option("HhAaSsRrWw");
    cout << endl << endl;

    bool success = false;

    switch(opt)
    {
        case 'H': case 'h':
        {
            cout << "EDITING HOME TEAM" << endl;
            cout << "Select an option: " << endl;
            cout << "    N - Edit name" << endl;
            cout << "    C - Edit country" << endl;
            cout << "    M - Edit morale" << endl;
            cout << "    S - Edit mood (strategy)" << endl;
            cout << "    A - Edit aggressiveness" << endl;
            cout << "    P - Edit players" << endl;
            cout << "Option: ";
            char opt2 = option("NnCcMmSsAaPp");
            cout << endl << endl;
            this->home_t->editTeam(countries, toupper(opt2));
            break;
        }
        case 'A': case 'a':
        {
            cout << "EDITING AWAY TEAM" << endl;
            cout << "Select an option: " << endl;
            cout << "    N - Edit name" << endl;
            cout << "    C - Edit country" << endl;
            cout << "    M - Edit morale" << endl;
            cout << "    S - Edit mood (strategy)" << endl;
            cout << "    A - Edit aggressiveness" << endl;
            cout << "    P - Edit players" << endl;
            cout << "Option: ";
            char opt2 = option("NnCcMmSsAaPp");
            cout << endl << endl;
            this->away_t->editTeam(countries, toupper(opt2));
            break;
        }
        default:
        {
            success = true;
            break;
        }
    }

    return success;
}