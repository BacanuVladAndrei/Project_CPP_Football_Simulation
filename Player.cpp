#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include "Player.h"
#include "Country.h"
#include "Administrative_functions.h"
#include "Goalkeeper.h"
#include "Defender.h"
#include "Midfielder.h"
#include "Forward.h"
using namespace std;

Country* getCountryadd(Country*, string);
Country* getCountries();

Player::Player()
{
    nationality = NULL;
    pos = '\0';
    birth_date.tm_sec = 0;
    birth_date.tm_min = 0;
    birth_date.tm_hour = 0;
    birth_date.tm_mday = 0;
    birth_date.tm_mon = 0;
    birth_date.tm_year = 0;
    birth_date.tm_wday = 0;
    birth_date.tm_yday = 0;
    birth_date.tm_isdst = 0;
    age = 0;
    cond = 100;
    rat = 0;
    on = 0;
    mins_played = 0;
}

Player::Player(string first_name, string family_name, Country* nationality, char pos, struct tm birth_date, int rat, int on, int mins_played)
{
    this->first_name = first_name;
    this->family_name = family_name;
    this->nationality = nationality;
    this->pos = pos;
    this->birth_date = birth_date;
    this->rat = rat;
    this->on = on;
    this->cond = 100;
    this->age = 0;
    this->mins_played = mins_played;
}

Player& Player::operator=(const Player& player)
{
    this->first_name = player.first_name;
    this->family_name = player.family_name;
    this->nationality = player.nationality;
    this->pos = player.pos;
    this->birth_date = player.birth_date;
    this->rat = player.rat;
    this->on = player.on;
    this->cond = player.cond;
    this->age = player.age;
    this->mins_played = player.mins_played;

    return *this;
}

int Player::read(fstream& stri, Countries countries)
{
    string l;
    !getline(stri, l);
    if(!l.length())
    {
        return 1;
    }

    char* line = new char[l.length() + 1];
    strcpy(line, l.c_str());

    char* token = strtok(line, ",");
    this->first_name = token;

    token = strtok(NULL, ",");
    this->family_name = token;
    this->family_name = this->family_name.substr(1);

    token = strtok(NULL, ",");
    this->ctr = token;
    this->ctr = this->ctr.substr(1);

    token = strtok(NULL, ",");
    this->pos = token[1];

    token = strtok(NULL, ",");
    string r = token;
    r = r.substr(1);
    this->rat = stoi(r);

    token = strtok(NULL, "\n");
    token++;
    char* token2 = strtok(token, "/");
    this->birth_date.tm_mday = atoi(token2);
    token2 = strtok(NULL, "/");
    this->birth_date.tm_mon = atoi(token2);
    token2 = strtok(NULL, "\0");
    this->birth_date.tm_year = atoi(token2);
    if(this->birth_date.tm_year > 30)
    {
        this->birth_date.tm_year += 1900;
    }
    else
    {
        this->birth_date.tm_year += 2000;
    }

    this->Age();
    this->cond = 100;
    this->mins_played = 0;

    delete[] line;
    return 0;
}

int Player::read(Countries countries, bool on_off, bool cant_be_gk, bool must_be_gk)
{
    // First Name
    do{
        cout << "First name: ";
        getline(cin, this->first_name);
        if(this->first_name.length() < 3)
        {
            cout << "First name must be at least 3 characters long!" << endl;
        }
    }while(this->first_name.length() < 3);
    
    // Family name
    do{
        cout << "Family name: ";
        getline(cin, this->family_name);
        if(this->family_name.length() < 3)
        {
            cout << "Family name must be at least 3 characters long!" << endl;
        }
    }while(this->family_name.length() < 3);
    
    // Nationality
    while(this->nationality == NULL)
    {
        cout << "Nationality: ";
        getline(cin, this->ctr);
        this->nationality = countries.getCountryAdd(this->ctr);
        if(this->nationality == NULL)
        {
            vector<Country> suggest = countries.suggestions(this->ctr, 5, 50); //countrySuggestions(countries, this->ctr, count, 50);
            cout << "Unknown country!" << endl;
            if(presentSuggestions(suggest))
            {
                cout << endl;
            }
        }
    }

    // Position
    bool ok = false;
    do{
        ok = true;
        cout << "Position: ";
        this->pos = option("GDMF");
        cout << endl;
        if(must_be_gk && this->pos != 'G')
        {
            ok = false;
            cout << "The starting line-up has to have at least one goalkeeper!" << endl;
        }
        if(cant_be_gk && this->pos == 'G')
        {
            ok = false;
            cout << "The starting line-up can not have more than one goalkeeper!" << endl;
        }
    }while(!ok);
    

    // Birth Date
    bool correct_bdt = false;
    int days_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    do{
        // Read birth date
        correct_bdt = true;
        cout << "Birth date (DD/MM/YY): ";
        string bdt;
        getline(cin, bdt);
        bdt = bdt.substr(0, 8);
        if(bdt[2] != '/' || bdt[5] != '/')
        {
            cout << "Incorrect format!" << endl;
            correct_bdt = false;
            continue;
        }
        
        // Compute year
        if(is_digit(bdt[6]) && is_digit(bdt[7]))
        {
            this->birth_date.tm_year = 10 * (bdt[6] - 48) + (bdt[7] - 48);
            if(this->birth_date.tm_year < 22)
            {
                this->birth_date.tm_year += 2000;
            }
            else
            {
                this->birth_date.tm_year += 1900;
            }
        }
        else
        {
            cout << "Incorrect year!" << endl;
            correct_bdt = false;
            continue;
        }

        // Compute month
        if(is_digit(bdt[3]) && is_digit(bdt[4]))
        {
            this->birth_date.tm_mon = 10 * (bdt[3] - 48) + (bdt[4] - 48);
            if(this->birth_date.tm_mon < 1 || this->birth_date.tm_mon > 12)
            {
                cout << "Incorrect month!" << endl;
                correct_bdt = false;
                continue;
            }
        }
        else
        {
            cout << "Incorrect month!" << endl;
            correct_bdt = false;
            continue;
        }

        if(this->birth_date.tm_year % 4 == 0)
        {
            days_month[1] = 29;
        }

        // Compute day
        if(is_digit(bdt[0]) && is_digit(bdt[1]))
        {
            this->birth_date.tm_mday = 10 * (bdt[0] - 48) + (bdt[1] - 48);
            if(this->birth_date.tm_mday < 1 || this->birth_date.tm_mday > days_month[this->birth_date.tm_mon - 1])
            {
                cout << "Incorrect day!" << endl;
                correct_bdt = false;
                continue;
            }
        }
        else
        {
            cout << "Incorrect date!" << endl;
            correct_bdt = false;
            continue;
        }
    }while(!correct_bdt);

    // Age
    cout << "Age: " << this->Age() << endl;

    // Rating
    string rating;
    do{
        cout << "Rating (1 - 100): ";
        getline(cin, rating);
        for(int i = 0; i < rating.size(); i++)
        {
            if(!is_digit(rating[i]))
            {
                rating.erase(i);
                i --;
            }
        }
        if(rating.length())
        {
            this->rat = stoi(rating);
        }
        else
        {
            cout << "Invalid rating!" << endl;
            this->rat = 0;
        }
        if(this->rat < 1 || this->rat > 100)
        {
            cout << "Rating must be in the [1 - 100] range!" << endl;
        }
    }while(this->rat < 1 || this->rat > 100);

    // Status
    this->on = on_off;

    return 0;
}

int Player::write(fstream& stro)
{
    stro << "First name: " << this->first_name << endl;
    stro << "Family name: " << this->family_name << endl;
    stro << "Nationality: " << this->nationality->getName() << endl;
    stro << "Position: ";
    switch(this->pos){
        case 'G':
        {
            stro << "Goalkeeper" << endl;
            break;
        }
        case 'D':
        {
            stro << "Defender" << endl;
            break;
        }
        case 'M':
        {
            stro << "Midfielder" << endl;
            break;
        }
        case 'F':
        {
            stro << "Forward" << endl;
            break;
        }
        default:
        {
            stro << "Unknown" << endl;
            break;
        }
    }
    stro << "Rating: " << this->rat << endl;
    stro << "Birth date: ";
    if(this->birth_date.tm_mday < 10)
    {
        stro << "0" << this->birth_date.tm_mday << "/";
    }
    else
    {
        stro << this->birth_date.tm_mday << "/";
    }
    if(this->birth_date.tm_mon < 10)
    {
        stro << "0" << this->birth_date.tm_mon << "/";
    }
    else
    {
        stro << this->birth_date.tm_mon << "/";
    }
    if(this->birth_date.tm_year % 100 < 10)
    {
        stro << "0" << this->birth_date.tm_year % 100 << endl;
    }
    else
    {
        stro << this->birth_date.tm_year % 100 << endl;
    }
    stro << "Age: " << this->age << endl;
    stro << "Condition: " << this->cond << endl;
    stro << "Status: ";
    if(this->on)
    {
        stro << "Playing" << endl;
    }
    else
    {
        stro << "Substitute" << endl;
    }
    stro << "Minutes played: " << this->mins_played << endl;

    return 0;
}

int Player::write(fstream& stro, int number, int width)
{
    if(this->on > 0)
    {
        stro << "P";
    }
    else
    {
        stro << "S";
    }
    
    if(number < 10)
    {
        stro << " " << number << "   ";
    }
    else
    {
        stro << number << "   ";
    }

    if(this->pos == '\0')
    {
        stro << "U   ";
    }
    else
    {
        stro << pos << "   ";
    }

    stro << this->first_name << " " << this->family_name;
    for(int i = this->first_name.length() + this->family_name.length() + 1; i < width; i++)
    {
        stro << " ";
    }

    stro << this->nationality->getCode() << "   ";
    if(this->rat == 100)
    {
        stro << "100     ";
    }
    else
    {
        if(this->rat > 9)
        {
            stro << " " << this->rat << "     ";
        }
        else
        {
            stro << "  " << this->rat << "     ";
        }
    }

    if(this->birth_date.tm_mday < 10)
    {
        stro << "0" << this->birth_date.tm_mday << "/";
    }
    else
    {
        stro << this->birth_date.tm_mday << "/";
    }
    if(this->birth_date.tm_mon < 10)
    {
        stro << "0" << this->birth_date.tm_mon << "/";
    }
    else
    {
        stro << this->birth_date.tm_mon << "/";
    }
    if(this->birth_date.tm_year % 100 < 10)
    {
        stro << "0" << this->birth_date.tm_year % 100 << "    ";
    }
    else
    {
        stro << this->birth_date.tm_year % 100 << "    ";
    }

    stro << this->age << "   ";

    if(this->cond == 100)
    {
        stro << "100  ";
    }
    else
    {
        if(this->cond > 9)
        {
            stro << this->cond << "   ";
        }
        else
        {
            stro << " " << this->cond << "   ";
        }
    }

    if(this->on > 0)
    {
        stro << "Playing      " << this->mins_played << endl;
    }
    else
    {
        stro << "Substitute   " << this->mins_played << endl;
    }
    
    return 0;
}

int Player::print()
{
    cout << "First name: " << this->first_name << endl;
    cout << "Family name: " << this->family_name << endl;
    cout << "Nationality: " << this->nationality->getName() << endl;
    cout << "Position: ";
    switch(this->pos){
        case 'G':
        {
            cout << "Goalkeeper" << endl;
            break;
        }
        case 'D':
        {
            cout << "Defender" << endl;
            break;
        }
        case 'M':
        {
            cout << "Midfielder" << endl;
            break;
        }
        case 'F':
        {
            cout << "Forward" << endl;
            break;
        }
        default:
        {
            cout << "Unknown" << endl;
            break;
        }
    }
    cout << "Rating: " << this->rat << endl;
    cout << "Birth date: ";
    if(this->birth_date.tm_mday < 10)
    {
        cout << "0" << this->birth_date.tm_mday << "/";
    }
    else
    {
        cout << this->birth_date.tm_mday << "/";
    }
    if(this->birth_date.tm_mon < 10)
    {
        cout << "0" << this->birth_date.tm_mon << "/";
    }
    else
    {
        cout << this->birth_date.tm_mon << "/";
    }
    if(this->birth_date.tm_year % 100 < 10)
    {
        cout << "0" << this->birth_date.tm_year % 100 << endl;
    }
    else
    {
        cout << this->birth_date.tm_year % 100 << endl;
    }
    cout << "Age: " << this->age << endl;
    cout << "Condition: " << this->cond << endl;
    cout << "Status: ";
    if(this->on)
    {
        cout << "Playing" << endl;
    }
    else
    {
        cout << "Substitute" << endl;
    }

    cout << "Minutes played: " << this->mins_played << endl;
    
    return 0;
}

int Player::print(int number, int width)
{
    //        #   Pos  Name              Nat  Rating  Birth Date  Age  Cond  Status       MP
    if(this->on > 0)
    {
        cout << "P";
    }
    else
    {
        cout << "S";
    }
    
    if(number < 10)
    {
        cout << " " << number << "   ";
    }
    else
    {
        cout << number << "   ";
    }

    if(this->pos == '\0')
    {
        cout << "U   ";
    }
    else
    {
        cout << pos << "   ";
    }

    cout << this->first_name << " " << this->family_name;
    for(int i = this->first_name.length() + this->family_name.length() + 1; i < width; i++)
    {
        cout << " ";
    }

    cout << this->nationality->getCode() << "   ";
    if(this->rat == 100)
    {
        cout << "100     ";
    }
    else
    {
        if(this->rat > 9)
        {
            cout << " " << this->rat << "     ";
        }
        else
        {
            cout << "  " << this->rat << "     ";
        }
    }

    if(this->birth_date.tm_mday < 10)
    {
        cout << "0" << this->birth_date.tm_mday << "/";
    }
    else
    {
        cout << this->birth_date.tm_mday << "/";
    }
    if(this->birth_date.tm_mon < 10)
    {
        cout << "0" << this->birth_date.tm_mon << "/";
    }
    else
    {
        cout << this->birth_date.tm_mon << "/";
    }
    if(this->birth_date.tm_year % 100 < 10)
    {
        cout << "0" << this->birth_date.tm_year % 100 << "    ";
    }
    else
    {
        cout << this->birth_date.tm_year % 100 << "    ";
    }

    cout << this->age << "   ";

    if(this->cond == 100)
    {
        cout << "100  ";
    }
    else
    {
        if(this->cond > 9)
        {
            cout << this->cond << "   ";
        }
        else
        {
            cout << " " << this->cond << "   ";
        }
    }

    if(this->on > 0)
    {
        cout << "Playing      " << this->mins_played << endl;
    }
    else
    {
        cout << "Substitute   " << this->mins_played << endl;
    }
    
    return 0;
}

string Player::getFirstName() const
{
    return this->first_name;
}

string Player::getFamilyName() const
{
    return this->family_name;
}

Country* Player::getNationality() const
{
    return this->nationality;
}

string Player::getCtr() const
{
    return this->ctr;
}

char Player::getPos() const
{
    return this->pos;
}

struct tm Player::getBirthDate() const
{
    return this->birth_date;
}

int Player::getAge() const
{
    return this->age;
}

int Player::getCond() const
{
    return this->cond;
}

int Player::getRat() const
{
    return this->rat;
}

int Player::getStatus() const
{
    return this->on;
}

int Player::getMinsPlayed() const
{
    return this->mins_played;
}

int Player::Cond()
{
    if(this->on < 0)
    {
        return this->cond;
    }

    int diff;
    if(this->age < 20)
    {
        diff = 20 - (this->age);
    }
    else
    {
        diff = (this->age) - 20;
    }

    int a = 60 + 2 * diff;
    if((rand()%90) < a && this->cond > 1)
    {
        this->cond--;
    }
    
    return this->cond;
}

int Player::incrementMins()
{
    return ++(this->mins_played);
}

bool Player::operator<(const Player& pl)
{
    //Status
    if(this->on != pl.on)
    {
        if(this->on == 3)
        {
            return 0;
        }
        else
        {
            if(pl.on == 3)
            {
                return 1;
            }
        }
    }

    //Position
    if(this->getPos() != pl.getPos())
    {
        switch(this->getPos()){
            case 'G':
            {
                return 1;
                break;
            }
            case 'D':
            {
                if(pl.getPos() == 'G')
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
                break;
            }
            case 'M':
            {
                if(pl.getPos() == 'F')
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                break;
            }
            case 'F':
            {
                return 0;
                break;
            }
            default:
                break;
        }
    }

    //Rating
    if(this->rat < pl.rat)
    {
        return 1;
    }
    else
    {
        if(this->rat > pl.rat)
        {
            return 0;
        }
    }

    //Names
    return this->family_name < pl.family_name;
}

int Player::Age()
{
    int month[]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    time_t now = time(0);
    struct tm *current = gmtime(&now);
    current->tm_year += 1900;
    if (this->birth_date.tm_mday > current->tm_mday)
    {
        current->tm_mday = current->tm_mday + month[this->birth_date.tm_mon];
        current->tm_mon--;
    }
    if (this->birth_date.tm_mon > current->tm_mon)
    {
        current->tm_year--;
        current->tm_mon = current->tm_mon + 12;
    }

    this->age = current->tm_year - this->birth_date.tm_year;

    return this->age;
}

int Player::goalChance(int min_rat)
{
    if(this->on > 0)
    {
        return 3 * (this->rat - min_rat + 1) + this->cond;
    }
    else
    {
        return 0;
    }
}

int Player::assistChance(Player* scorer, int min_rat)
{
    if(this == scorer)
    {
        return 0;
    }
    else
    {
        if(this->on > 0)
        {
            return 3 * (this->rat - min_rat + 1) + this->cond;
        }
        else
        {
            return 0;
        }
    }
}

int Player::penaltyTakerChance(int min_rat)
{
    if(this->on > 0)
    {
        return 3 * (this->rat - min_rat + 1) + this->cond;
    }
    else
    {
        return 0;
    }
}

int Player::penaltyGuiltyChance(int max_rat)
{
    if(this->on > 0)
    {
        return 3 * (max_rat - this->rat + 1) + 100 - this->cond;
    }
    else
    {
        return 0;
    }
}

int Player::shotTakerChance(int min_rat)
{
    if(this->on > 0)
    {
        return 2 * (this->rat - min_rat + 1) + 100 - this->cond;
    }
    else
    {
        return 0;
    }
}

int Player::foulAgainstChance(char opp_pos)
{
    if(this->on > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Player::foulChance(int max_rat)
{
    if(this->on > 0)
    {
        return 2 * (max_rat - this->rat + 1) + 100 - this->cond;
    }
    else
    {
        return 0;
    }
}

int Player::offsideChance()
{
    if(this->on > 0)
    {
        return 100 - this->cond + 1;
    }
    else
    {
        return 0;
    }
}

int Player::cornerTakerChance()
{
    return 100 - this->cond;
}

int Player::cornerTouchChance()
{
    return 1;
}

int Player::chancesSubstitutionOff(int max_rat)
{
    return (this->getStatus() == 1) ? (100 - this->cond + 1) * (max_rat - this->rat + 1) : 0;
}

int Player::chancesSubstitutionOn(int min_rat)
{
    return (this->getStatus() == 0) ? this->rat - min_rat + 1 : 0;
}

int Player::passChance()
{
    return (this->on == 1 || this->on == 2) ? 1 : 0;
}

bool Player::accuratePass()
{
    return rand() % 100 < (45 + this->rat / 2.0);
}

int Player::err()
{
    return 0;
}

vector<Player*> read_players(fstream& team, Countries countries, int& count, int max_read, bool playing)
{
    Player pl;
    int c = 0;
    vector<Player*> players;
    while(!(pl.read(team, countries)))
    {
        pl.nationality = countries.getCountryAdd(pl.ctr.c_str());
        pl.on = playing;
        switch(pl.pos){
            case 'G':
            {
                Goalkeeper* gk = new Goalkeeper;
                (*gk) = pl;
                players.push_back(gk);
                break;
            }
            case 'D':
            {
                Defender* def = new Defender;
                (*def) = pl;
                players.push_back(def);
                break;
            }
            case 'M':
            {
                Midfielder* mid = new Midfielder;
                (*mid) = pl;
                players.push_back(mid);
                break;
            }
            case 'F':
            {
                Forward* fwd = new Forward;
                (*fwd) = pl;
                players.push_back(fwd);
                break;
            }
        }
        c++;
        if(c == max_read)
        {
            break;
        }
    }
    count = c;

    // sort<Player*>(players, count, [](Player* elem1, Player* elem2){ return (*elem1) < (*elem2); });

    return players;
}

double Player::getMark()
{
    return 0.0;
}

int maxNameLength(vector<Player*> players, int count)
{
    int max = 0;
    for(int i = 0; i < count; i++)
    {
        if(players[i]->first_name.length() + players[i]->family_name.length() + 1 > max)
        {
            max = players[i]->first_name.length() + players[i]->family_name.length() + 1;
        }
    }

    return max;
}

int printPlayersTable(vector<Player*> players, int count)
{
    int width = maxNameLength(players, count) + 3;
    cout << " #   Pos  Name";
    for(int i = 4; i < width; i++)
    {
        cout << " ";
    }
    cout << "Nat  Rating  Birth Date  Age  Cond  Status       MP" << endl;
    
    for(int i = 0; i < count; i++)
    {
        players[i]->print(i + 1, width);
    }

    return 0;
}

int writePlayersTable(fstream& stro, vector<Player*> players, int count)
{
    int width = maxNameLength(players, count) + 3;
    cout << " #   Pos  Name";
    for(int i = 4; i < width; i++)
    {
        cout << " ";
    }
    cout << "Nat  Rating  Birth Date  Age  Cond  Status       MP" << endl;
    
    for(int i = 0; i < count; i++)
    {
        players[i]->write(stro, i + 1, width);
    }

    return 0;
}

void Player::printStatistics(int width)
{
    cout << this->first_name << " " << this->family_name;
    for(int i = this->first_name.length() + this->family_name.length() + 1; i < width; i++)
    {
        cout << " ";
    }

    // Pos  Minutes  Goals   Goals    Assists  Shots  Shots on    Shot       Shot     Saves  Offsides  Passes  Accurate    Pass      Fouls     Fouls    Yellow  Red   FINAL MARK
    //      Played          Received                   Target   Accuracy  Efficiency                            Passes   Accuracy  Committed  Suffered   Card   Card

    if(this->getPos() == 'G')
    {
        // Position
        cout << " G   ";

        // Minutes Played
        if(this->getMinutesPlayed() < 10)
        {
            cout << "   " << this->getMinutesPlayed() << "     ";
        }
        else
        {
            if(this->getMinutesPlayed() < 100)
            {
                cout << "  " << this->getMinutesPlayed() << "     ";
            }
            else
            {
                cout << "  " << this->getMinutesPlayed() << "    ";
            }
        }

        // Goals
        cout << "  -    ";

        // Goals Received
        if(this->getGoalsReceived() < 10)
        {
            cout << "    " << this->getGoalsReceived() << "    ";
        }
        else
        {
            cout << "   " << this->getGoalsReceived() << "    ";
        }

        // Assists
        cout << "    -     ";

        // Shots
        cout << "  -    ";

        // Shots on Target
        cout << "    -     ";

        // Shot Accuracy
        cout << "   -      ";

        // Shot Efficiency
        cout << "    -       ";

        // Saves
        if(this->getSaves() < 10)
        {
            cout << "  " << this->getSaves() << "    ";
        }
        else
        {
            cout << " " << this->getSaves() << "    ";
        }

        // Offsides
        cout << "    -     ";

        // Passes
        if(this->getPasses() < 10)
        {
            cout << "   " << this->getPasses() << "    ";
        }
        else
        {
            if(this->getPasses() < 100)
            {
                cout << "  " << this->getPasses() << "    ";
            }
            else
            {
                cout << " " << this->getPasses() << "    ";
            }
        }

        // Accurate Passes
        if(this->getAccuratePasses() < 10)
        {
            cout << "    " << this->getAccuratePasses() << "     ";
        }
        else
        {
            if(this->getAccuratePasses() < 100)
            {
                cout << "   " << this->getAccuratePasses() << "     ";
            }
            else
            {
                cout << "  " << this->getAccuratePasses() << "     ";
            }
        }

        // Pass Accuracy
        if(this->getPassAccuracy() < 10)
        {
            cout << "  ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getPassAccuracy() << "%   ";
        }
        else
        {
            if(this->getPassAccuracy() < 100)
            {
                cout << " ";
                cout << setprecision(2);
                cout << fixed;
                cout << this->getPassAccuracy() << "%   ";
            }
            else
            {
                cout << setprecision(2);
                cout << fixed;
                cout << this->getPassAccuracy() << "%   ";
            }
        }

        // Fouls Committed
        if(this->getFoulsCommitted() < 10)
        {
            cout << "    " << this->getFoulsCommitted() << "      ";
        }
        else
        {
            cout << "   " << this->getFoulsCommitted() << "      ";
        }

        // Fouls Suffered
        if(this->getFoulsSuffered() < 10)
        {
            cout << "    " << this->getFoulsSuffered() << "     ";
        }
        else
        {
            cout << "   " << this->getFoulsSuffered() << "     ";
        }

        // Yellow Card
        cout << "   " << this->getYellowCard() << "    ";
        
        // Red Card
        cout << "  " << this->getRedCard() << "   ";

        // MARK
        if(this->getMark() < 10)
        {
            cout << "   ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getMark() << endl;
        }
        else
        {
            cout << "  ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getMark() << endl;
        } 
    }
    else
    {
        // Position
        cout << " " << this->pos << "   ";

        // Minutes Played
        if(this->getMinutesPlayed() < 10)
        {
            cout << "   " << this->getMinutesPlayed() << "     ";
        }
        else
        {
            if(this->getMinutesPlayed() < 100)
            {
                cout << "  " << this->getMinutesPlayed() << "     ";
            }
            else
            {
                cout << "  " << this->getMinutesPlayed() << "    ";
            }
        }

        // Goals
        if(this->getGoals() < 10)
        {
            cout << "  " << this->getGoals() << "    ";
        }
        else
        {
            cout << " " << this->getGoals() << "    ";
        }

        // Goals Received
        cout << "    -     ";

        // Assists
        cout << "   " << this->getAssists() << "     ";

        // Shots
        if(this->getShots() < 10)
        {
            cout << "  " << this->getShots() << "    ";
        }
        else
        {
            cout << " " << this->getShots() << "    ";
        }

        // Shots on Target
        if(this->getShotsOnTarget() < 10)
        {
            cout << "    " << this->getShotsOnTarget() << "     ";
        }
        else
        {
            cout << "   " << this->getShotsOnTarget() << "     ";
        }

        // Shot Accuracy
        if(this->getShotAccuracy() < 10)
        {
            cout << "  ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getShotAccuracy() << "%   ";
        }
        else
        {
            if(this->getShotAccuracy() < 100)
            {
                cout << " ";
                cout << setprecision(2);
                cout << fixed;
                cout << this->getShotAccuracy() << "%   ";
            }
            else
            {
                cout << setprecision(2);
                cout << fixed;
                cout << this->getShotAccuracy() << "%   ";
            }
        }

        // Shot Efficiency
        if(this->getShotEfficiency() < 10)
        {
            cout << "   ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getShotEfficiency() << "%    ";
        }
        else
        {
            if(this->getShotEfficiency() < 100)
            {
                cout << "  ";
                cout << setprecision(2);
                cout << fixed;
                cout << this->getShotEfficiency() << "%    ";
            }
            else
            {
                cout << " ";
                cout << setprecision(2);
                cout << fixed;
                cout << this->getShotEfficiency() << "%    ";
            }
        }

        // Saves
        cout << "  -    ";

        // Offsides
        cout << "    " << this->getOffsides() << "     ";

        // Passes
        if(this->getPasses() < 10)
        {
            cout << "   " << this->getPasses() << "    ";
        }
        else
        {
            if(this->getPasses() < 100)
            {
                cout << "  " << this->getPasses() << "    ";
            }
            else
            {
                cout << " " << this->getPasses() << "    ";
            }
        }

        // Accurate Passes
        if(this->getAccuratePasses() < 10)
        {
            cout << "    " << this->getAccuratePasses() << "     ";
        }
        else
        {
            if(this->getAccuratePasses() < 100)
            {
                cout << "   " << this->getAccuratePasses() << "     ";
            }
            else
            {
                cout << "  " << this->getAccuratePasses() << "     ";
            }
        }

        // Pass Accuracy
        if(this->getPassAccuracy() < 10)
        {
            cout << "  ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getPassAccuracy() << "%   ";
        }
        else
        {
            if(this->getPassAccuracy() < 100)
            {
                cout << " ";
                cout << setprecision(2);
                cout << fixed;
                cout << this->getPassAccuracy() << "%   ";
            }
            else
            {
                cout << setprecision(2);
                cout << fixed;
                cout << this->getPassAccuracy() << "%   ";
            }
        }

        // Fouls Committed
        if(this->getFoulsCommitted() < 10)
        {
            cout << "    " << this->getFoulsCommitted() << "      ";
        }
        else
        {
            cout << "   " << this->getFoulsCommitted() << "      ";
        }

        // Fouls Suffered
        if(this->getFoulsSuffered() < 10)
        {
            cout << "    " << this->getFoulsSuffered() << "     ";
        }
        else
        {
            cout << "   " << this->getFoulsSuffered() << "     ";
        }

        // Yellow Card
        cout << "   " << this->getYellowCard() << "    ";
        
        // Red Card
        cout << "  " << this->getRedCard() << "   ";

        // MARK
        if(this->getMark() < 10)
        {
            cout << "   ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getMark() << endl;
        }
        else
        {
            cout << "  ";
            cout << setprecision(2);
            cout << fixed;
            cout << this->getMark() << endl;
        }
    }
}