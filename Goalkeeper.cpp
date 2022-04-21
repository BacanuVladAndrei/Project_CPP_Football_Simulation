#include <iostream>
#include <string>
#include "Player.h"
#include "Goalkeeper.h"
using namespace std;

Goalkeeper& Goalkeeper::operator=(const Player& player)
{
    this->first_name = player.getFirstName();
    this->family_name = player.getFamilyName();
    this->nationality = player.getNationality();
    this->ctr = player.getCtr();
    this->pos = 'G';
    this->birth_date = player.getBirthDate();
    this->age = player.getAge();
    this->cond = player.getCond();
    this->rat = player.getRat();
    this->on = player.getStatus();
    this->InitStatistics();

    return *this;
}

void Goalkeeper::InitStatistics()
{
    this->statistics.minutes_played = 0;
    this->statistics.goals_received = 0;
    this->statistics.saves = 0;
    this->statistics.assists = 0;
    this->statistics.passes = 0;
    this->statistics.accurate_passes = 0;
    this->statistics.pass_accuracy = 0.0;
    this->statistics.fouls_committed = 0;
    this->statistics.fouls_suffered = 0;
    this->statistics.yellow_card = 0;
    this->statistics.red_card = 0;
}

string Goalkeeper::getFirstName() const
{
    return this->first_name;
}

string Goalkeeper::getFamilyName() const
{
    return this->family_name;
}

Country* Goalkeeper::getNationality() const
{
    return this->nationality;
}

string Goalkeeper::getCtr() const
{
    return this->ctr;
}

char Goalkeeper::getPos() const
{
    return this->pos;
}

struct tm Goalkeeper::getBirthDate() const
{
    return this->birth_date;
}

int Goalkeeper::getAge() const
{
    return this->age;
}

int Goalkeeper::getCond() const
{
    return this->cond;
}

int Goalkeeper::getRat() const
{
    return this->rat;
}

int Goalkeeper::getStatus() const
{
    return this->on;
}

int Goalkeeper::getMinsPlayed() const
{
    return this->mins_played;
}

int Goalkeeper::incrementMins()
{
    return this->Player::incrementMins();
}

int Goalkeeper::Cond()
{
    return this->Player::Cond();
}

double Goalkeeper::getMark()
{
    return 0.0;
}

int Goalkeeper::goalChance(int min_rat)
{
    return 0;
}

int Goalkeeper::assistChance(Player* scorer, int min_rat)
{
    return this->Player::assistChance(scorer, min_rat);
}

int Goalkeeper::penaltyTakerChance(int min_rat)
{
    return this->Player::penaltyTakerChance(min_rat);
}

int Goalkeeper::penaltyGuiltyChance(int max_rat)
{
    return 10 * this->Player::penaltyGuiltyChance(max_rat);
}

int Goalkeeper::shotTakerChance(int min_rat)
{
    return 0;
}

int Goalkeeper::foulAgainstChance(char opp_pos)
{
    if(this->on < 1)
    {
        return 0;
    }
    switch(opp_pos) {
        case 'G':
        {
            return 0;
            break;
        }
        case 'D':
        {
            return 0;
            break;
        }
        case 'M':
        {
            return 1;
            break;
        }
        case 'F':
        {
            return 3;
            break;
        }
        default:
            break;
    }
    return 0;
}

int Goalkeeper::foulChance(int max_rat)
{
    return this->Player::foulChance(max_rat);
}

int Goalkeeper::offsideChance()
{
    return 0;
}

int Goalkeeper::cornerTakerChance()
{
    return 0;
}

int Goalkeeper::cornerTouchChance()
{
    return 10;
}

int Goalkeeper::passChance()
{
    return (this->on == 1 || this->on == 2) ? 1 : 0;
}

bool Goalkeeper::accuratePass()
{
    return rand() % 100 < (80 + this->rat / 5.0);
}

int Goalkeeper::print()
{
    return this->Player::print();
}

int Goalkeeper::print(int number, int width)
{
    return this->Player::print(number, width);
}

int Goalkeeper::write(fstream& stro)
{
    return this->Player::write(stro);
}

int Goalkeeper::write(fstream& stro, int number, int width)
{
    return this->Player::write(stro, number, width);
}