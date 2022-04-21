#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "MatchFile.h"
using namespace std;

MatchFile::MatchFile()
{
    // Defaults all attributes
    if(this->stream.is_open())
    {
        this->stream.close();
    }
    this->stream_name.clear();
}

MatchFile::MatchFile(const string& stream_name)
{
    // Defaults stream and sets stream_name
    if(stream.is_open())
    {
        stream.close();
    }
    this->stream_name = stream_name;
}

MatchFile::MatchFile(const string& stream_name, const char mode)
{
    this->open(stream_name, mode);
}

string MatchFile::getName() const
{
    // Returns stream_name
    return this->stream_name;
}

bool MatchFile::open(const char mode)
{
    // Opens the stream depending on the mode provided:
    //     w - writing;
    //     r - reading;
    //     a - appending;
    // Returns true if the stream failed to open, false otherwise
    if(this->stream.is_open())
    {
        return true;
    }
    switch(mode){
        case 'w': case 'W':
        {
            this->stream.open(this->stream_name, ios::out);
            break;
        }
        case 'r': case 'R':
        {
            this->stream.open(this->stream_name, ios::in);
            break;
        }
        case 'a': case 'A':
        {
            this->stream.open(this->stream_name, ios::app);
            break;
        }
        default:
        {
            return true;
        }
    }

    return !(this->stream.is_open());
}

bool MatchFile::open(const string& path, const char mode)
{
    // Opens the stream depending on the name and mode provided:
    //     w - writing;
    //     r - reading;
    //     a - appending;
    // Returns true if the stream failed to open, false otherwise
    switch(mode){
        case 'w':
        {
            this->stream.open(path, ios::out);
            break;
        }
        case 'r':
        {
            this->stream.open(path, ios::in);
            break;
        }
        case 'a':
        {
            this->stream.open(path, ios::app);
            break;
        }
        default:
        {
            return true;
        }
    }

    return !(this->stream.is_open());
}

bool MatchFile::is_open() const
{
    // Checks if the stream is open or not
    return this->stream.is_open();
}

void MatchFile::write(const string& str)
{
    // If the stream is open, it writes str inside the stream
    if(this->stream.is_open())
    {
        this->stream << str;
    }
}

bool MatchFile::close()
{
    // Closes the stream, if it is open
    if(this->stream.is_open())
    {
        stream.close();
    }

    return this->stream.is_open();
}

bool MatchFile::writeTableofContents()
{
    if(!(this->stream.is_open()))
    {
        return true;
    }

    this->stream << "---TABLE OF CONTENTS---" << endl << endl;

    this->stream << "A. PREGAME" << endl;
    this->stream << "    1. Stadium" << endl;
    this->stream << "    2. Weather" << endl;
    this->stream << "    3. Teams' overview" << endl;
    this->stream << "        a) Home team" << endl;
    this->stream << "        b) Away team" << endl;
    this->stream << "    4. Referees" << endl;
    this->stream << "    5. Betting" << endl;
    this->stream << "        a) Odds" << endl;
    this->stream << "        b) Ticket" << endl;
    // ...
    this->stream << "B. MATCH" << endl;
    // ...
    this->stream << "C. AFTERMATH" << endl;
    // ...

    return false;
}

bool MatchFile::writeReferees(const Referees& referees)
{
    if(!(this->stream.is_open()))
    {
        return true;
    }

    this->stream << "---REFEREES---" << endl;
    this->stream << "Central: " << referees.getMain().getName() << " (" << referees.getMain().getNationality()->getCode() << ")" << endl;
    this->stream << "Assistant 1: " << referees.getAss1().getName() << " (" << referees.getAss1().getNationality()->getCode() << ")" << endl;
    this->stream << "Assistant 2: " << referees.getAss2().getName() << " (" << referees.getAss2().getNationality()->getCode() << ")" << endl;
    this->stream << "4th Official: " << referees.getSide().getName() << " (" << referees.getSide().getNationality()->getCode() << ")" << endl;
    this->stream << "VAR 1: " << referees.getVAR1().getName() << " (" << referees.getVAR1().getNationality()->getCode() << ")" << endl;
    this->stream << "VAR 2: " << referees.getVAR2().getName() << " (" << referees.getVAR2().getNationality()->getCode() << ")" << endl;

    return false;
}

bool MatchFile::writeStadium(const Stadium& stadium)
{
    if(!(this->stream.is_open()))
    {
        return true;
    }

    this->stream << "---STADIUM---" << endl;
    this->stream << "Name: " << stadium.getName() << endl;
    this->stream << "Location: " << stadium.getLocation() << ", " << stadium.getCountry()->getName() << endl;
    this->stream << "Capacity: " << stadium.getCapacity() << endl;
    this->stream << "Attendance: " << stadium.getAttendance() << endl;
    this->stream << "Home support: " << stadium.getHomesupport() << endl;
    this->stream << "Ticket Price Range: " << stadium.getLowestPrice() << "$ - " << stadium.getHighestPrice() << "$" << endl;
    this->stream << "Class: " << stadium.getClass() << endl;
    this->stream << "Code: " << stadium.getCode() << endl;

    return false;
}

bool MatchFile::writeWeather(const Weather& weather)
{
    if(!(this->stream.is_open()))
    {
        return true;
    }

    this->stream << "---WEATHER---" << endl;
    this->stream << "Description: " << weather.describeWeather() << endl;
    this->stream << "Temperature: " << setprecision(1) << fixed << weather.getTemperature() << "*C" << endl;
    this->stream << "Cloudy: " << (weather.isCloudy() ? "Yes" : "No") << endl;
    this->stream << "Level of precipitation (0 - 10): " << weather.getPrecipitation() << endl;
    this->stream << "Clock value (minutes after UTC midnight): " << weather.getClock() << endl;
    string m[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    this->stream << "Month: " << m[weather.getMonth() - 1] << endl;

    return false;
}

bool MatchFile::writeTeamOverview(const Team& team)
{
    if(!(this->stream.is_open()))
    {
        return true;
    }

    if(team.getType())
    {
        this->stream << "--AWAY TEAM--" << endl;
    }
    else
    {
        this->stream << "--HOME TEAM--" << endl;
    }

    this->stream << "Name: " << team.getName() << endl;
    this->stream << "Country: " << team.getNationality()->getName() << endl;
    this->stream << "Rating: " << setw(6) << setprecision(2) << fixed << team.getRatingTotal() << endl;
    this->stream << "   DEF: " << setw(6) << setprecision(2) << fixed << team.getRatingDef() << endl;
    this->stream << "   MID: " << setw(6) << setprecision(2) << fixed << team.getRatingMid() << endl;
    this->stream << "   OFF: " << setw(6) << setprecision(2) << fixed << team.getRatingOff() << endl;
    this->stream << "Morale (0 - 5): " << team.getMorale() << endl;
    this->stream << "Crowd support (0 - 5): " << team.getSupp() << endl;
    this->stream << "Defensive / Offensive (-5 - 5): " << team.getMood() << endl;
    this->stream << "Aggressiveness (-5 - 5): " << team.getAgg() << endl;
    this->stream << "Last 6 matches: ";
    bool at_least_one = false;
    for(int i = 0; i < 6; i++)
    {
        switch(team.getMoraleVector()[i]){
            case 0:
            {
                this->stream << "L ";
                at_least_one = true;
                break;
            }
            case 1:
            {
                this->stream << "D ";
                at_least_one = true;
                break;
            }
            case 3:
            {
                this->stream << "W ";
                at_least_one = true;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    if(!at_least_one)
    {
        this->stream << "No matches played yet..." << endl;
    }
    else
    {
        this->stream << "..." << endl;
    }
    this->stream << "Formation: " << team.getFormation() << endl;
    this->stream << "Best player: " << team.getBestPlayer(true, true) << endl << endl;

    // Find longest playing full name
    int longest_playing = 0;
    for(int i = 0; i < 11; i++)
    {
        if(team.getPlayer(i)->getFirstName().length() + team.getPlayer(i)->getFirstName().length() > longest_playing)
        {
            longest_playing = team.getPlayer(i)->getFirstName().length() + team.getPlayer(i)->getFirstName().length();
        }
    }
    longest_playing ++; // Space between names

    // Players
    this->stream << "STARTING LINE-UP" << endl;
    this->stream << " #   Pos  " << setw(longest_playing) << left << "Name" << "  Nat  Rat  Birth date  Age" << endl;
    string full_name;
    for(int i = 0; i < 11; i++)
    {
        full_name = team.getPlayer(i)->getFirstName() + " " + team.getPlayer(i)->getFamilyName();
        this->stream << "P" << setw(2) << i + 1 << "   " << team.getPlayer(i)->getPos() << "   " << setw(longest_playing) << left << full_name << "  " << team.getPlayer(i)->getNationality()->getCode() << "  " << setw(3) << team.getPlayer(i)->getRat() << "   ";
        if(team.getPlayer(i)->getBirthDate().tm_mday < 10)
        {
            this->stream << "0" << team.getPlayer(i)->getBirthDate().tm_mday << "/";
        }
        else
        {
            this->stream << team.getPlayer(i)->getBirthDate().tm_mday << "/";
        }
        if(team.getPlayer(i)->getBirthDate().tm_mon < 10)
        {
            this->stream << "0" << team.getPlayer(i)->getBirthDate().tm_mon << "/";
        }
        else
        {
            this->stream << team.getPlayer(i)->getBirthDate().tm_mon << "/";
        }
        if(team.getPlayer(i)->getBirthDate().tm_year % 10 < 10)
        {
            this->stream << "0" << team.getPlayer(i)->getBirthDate().tm_year % 10;
        }
        else
        {
            this->stream << team.getPlayer(i)->getBirthDate().tm_year % 10;
        }
        this->stream << "   " << setw(3) << team.getPlayer(i)->getAge() << endl;
    }
    full_name.clear();
    this->stream << endl;

    // Find longest substitute full name
    int longest_substitute = 0;
    for(int i = 0; i < 11; i++)
    {
        if(team.getPlayer(i)->getFirstName().length() + team.getPlayer(i)->getFirstName().length() > longest_substitute)
        {
            longest_substitute = team.getPlayer(i)->getFirstName().length() + team.getPlayer(i)->getFirstName().length();
        }
    }
    longest_substitute ++; // Space between names

    // Substitutes
    this->stream << "AVAILABLE SUBSTITUTES" << endl;
    this->stream << " #   Pos  " << setw(longest_substitute) << left << "Name" << "  Nat  Rat  Birth date  Age" << endl;
    for(int i = 0; i < 11; i++)
    {
        full_name = team.getSubstitute(i)->getFirstName() + " " + team.getSubstitute(i)->getFamilyName();
        this->stream << "P" << setw(2) << i + 1 << "   " << team.getSubstitute(i)->getPos() << "   " << setw(longest_substitute) << left << full_name << "  " << team.getSubstitute(i)->getNationality()->getCode() << "  " << setw(3) << team.getSubstitute(i)->getRat() << "   ";
        if(team.getSubstitute(i)->getBirthDate().tm_mday < 10)
        {
            this->stream << "0" << team.getSubstitute(i)->getBirthDate().tm_mday << "/";
        }
        else
        {
            this->stream << team.getSubstitute(i)->getBirthDate().tm_mday << "/";
        }
        if(team.getSubstitute(i)->getBirthDate().tm_mon < 10)
        {
            this->stream << "0" << team.getSubstitute(i)->getBirthDate().tm_mon << "/";
        }
        else
        {
            this->stream << team.getSubstitute(i)->getBirthDate().tm_mon << "/";
        }
        if(team.getSubstitute(i)->getBirthDate().tm_year % 10 < 10)
        {
            this->stream << "0" << team.getSubstitute(i)->getBirthDate().tm_year % 10;
        }
        else
        {
            this->stream << team.getSubstitute(i)->getBirthDate().tm_year % 10;
        }
        this->stream << "   " << setw(3) << team.getSubstitute(i)->getAge() << endl;
    }

    return false;
}