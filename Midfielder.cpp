#include <iostream>
#include <string>
#include "Player.h"
#include "Midfielder.h"
using namespace std;

Midfielder& Midfielder::operator=(const Player& player)
{
    this->first_name = player.getFirstName();
    this->family_name = player.getFamilyName();
    this->nationality = player.getNationality();
    this->ctr = player.getCtr();
    this->pos = 'M';
    this->birth_date = player.getBirthDate();
    this->age = player.getAge();
    this->cond = player.getCond();
    this->rat = player.getRat();
    this->on = player.getStatus();
    this->InitStatistics();
    
    return *this;
}

void Midfielder::InitStatistics()
{
    this->statistics.minutes_played = 0;
    this->statistics.goals = 0;
    this->statistics.assists = 0;
    this->statistics.shots = 0;
    this->statistics.shots_on_target = 0;
    this->statistics.shot_accuracy = 0.0;
    this->statistics.shot_efficiency = 0.0;
    this->statistics.offsides = 0;
    this->statistics.passes = 0;
    this->statistics.accurate_passes = 0;
    this->statistics.pass_accuracy = 0.0;
    this->statistics.fouls_committed = 0;
    this->statistics.fouls_suffered = 0;
    this->statistics.yellow_card = 0;
    this->statistics.red_card = 0;
}

string Midfielder::getFirstName() const
{
    return this->first_name;
}

string Midfielder::getFamilyName() const
{
    return this->family_name;
}

Country* Midfielder::getNationality() const
{
    return this->nationality;
}

string Midfielder::getCtr() const
{
    return this->ctr;
}

char Midfielder::getPos() const
{
    return this->pos;
}

struct tm Midfielder::getBirthDate() const
{
    return this->birth_date;
}

int Midfielder::getAge() const
{
    return this->age;
}

int Midfielder::getCond() const
{
    return this->cond;
}

int Midfielder::getRat() const
{
    return this->rat;
}

int Midfielder::getStatus() const
{
    return this->on;
}

int Midfielder::getMinsPlayed() const
{
    return this->mins_played;
}

int Midfielder::incrementMins()
{
    return this->Player::incrementMins();
}

int Midfielder::Cond()
{
    return this->Player::Cond();
}

double Midfielder::getMark()
{
    return 0.0;
}

int Midfielder::goalChance(int min_rat)
{
    return 378 * this->Player::goalChance(min_rat);
}

int Midfielder::assistChance(Player* scorer, int min_rat)
{
    return 15 * this->Player::assistChance(scorer, min_rat);
}

int Midfielder::penaltyTakerChance(int min_rat)
{
    return 80 * this->Player::penaltyTakerChance(min_rat);
}

int Midfielder::penaltyGuiltyChance(int max_rat)
{
    return 8 * this->Player::penaltyGuiltyChance(max_rat);
}

int Midfielder::shotTakerChance(int min_rat)
{
    return 8 * this->Player::shotTakerChance(min_rat);
}

int Midfielder::foulAgainstChance(char opp_pos)
{
    if(this->on < 1)
    {
        return 0;
    }
    switch(opp_pos) {
        case 'G':
        {
            return 1;
            break;
        }
        case 'D':
        {
            return 8;
            break;
        }
        case 'M':
        {
            return 20;
            break;
        }
        case 'F':
        {
            return 16;
            break;
        }
        default:
            break;
    }
    return 0;
}

int Midfielder::foulChance(int max_rat)
{
    return 15 * this->Player::foulChance(max_rat);
}

int Midfielder::offsideChance()
{
    return 3 * this->Player::offsideChance();
}

int Midfielder::cornerTakerChance()
{
    return 10;
}

int Midfielder::cornerTouchChance()
{
    return 12;
}

int Midfielder::passChance()
{
    return (this->on == 1 || this->on == 2) ? 20 : 0;
}

bool Midfielder::accuratePass()
{
    return rand() % 100 < (45 + this->rat / 2.0);
}

int Midfielder::print()
{
    return this->Player::print();
}

int Midfielder::print(int number, int width)
{
    return this->Player::print(number, width);
}

int Midfielder::write(fstream& stro)
{
    return this->Player::write(stro);
}

int Midfielder::write(fstream& stro, int number, int width)
{
    return this->Player::write(stro, number, width);
}