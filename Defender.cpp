#include <iostream>
#include <string>
#include "Player.h"
#include "Defender.h"
using namespace std;

Defender& Defender::operator=(const Player& player)
{
    this->first_name = player.getFirstName();
    this->family_name = player.getFamilyName();
    this->nationality = player.getNationality();
    this->ctr = player.getCtr();
    this->pos = 'D';
    this->birth_date = player.getBirthDate();
    this->age = player.getAge();
    this->cond = player.getCond();
    this->rat = player.getRat();
    this->on = player.getStatus();
    this->InitStatistics();
    
    return *this;
}

void Defender::InitStatistics()
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

string Defender::getFirstName() const
{
    return this->first_name;
}

string Defender::getFamilyName() const
{
    return this->family_name;
}

Country* Defender::getNationality() const
{
    return this->nationality;
}

string Defender::getCtr() const
{
    return this->ctr;
}

char Defender::getPos() const
{
    return this->pos;
}

struct tm Defender::getBirthDate() const
{
    return this->birth_date;
}

int Defender::getAge() const
{
    return this->age;
}

int Defender::getCond() const
{
    return this->cond;
}

int Defender::getRat() const
{
    return this->rat;
}

int Defender::getStatus() const
{
    return this->on;
}

int Defender::getMinsPlayed() const
{
    return this->mins_played;
}

int Defender::incrementMins()
{
    return this->Player::incrementMins();
}

int Defender::Cond()
{
    return this->Player::Cond();
}

double Defender::getMark()
{
    return 0.0;
}

int Defender::goalChance(int min_rat)
{
    return 101 * this->Player::goalChance(min_rat);
}

int Defender::assistChance(Player* scorer, int min_rat)
{
    return 6 * this->Player::assistChance(scorer, min_rat);
}

int Defender::penaltyTakerChance(int min_rat)
{
    return 50 * this->Player::penaltyTakerChance(min_rat);
}

int Defender::penaltyGuiltyChance(int max_rat)
{
    return 15 * this->Player::penaltyGuiltyChance(max_rat);
}

int Defender::shotTakerChance(int min_rat)
{
    return 3 * this->Player::shotTakerChance(min_rat);
}

int Defender::foulAgainstChance(char opp_pos)
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
            return 3;
            break;
        }
        case 'M':
        {
            return 8;
            break;
        }
        case 'F':
        {
            return 20;
            break;
        }
        default:
            break;
    }
    return 0;
}

int Defender::foulChance(int max_rat)
{
    return 20 * this->Player::foulChance(max_rat);
}

int Defender::offsideChance()
{
    return this->Player::offsideChance();
}

int Defender::cornerTakerChance()
{
    return 3;
}

int Defender::cornerTouchChance()
{
    return 20;
}

int Defender::passChance()
{
    return (this->on == 1 || this->on == 2) ? 8 : 0;
}

bool Defender::accuratePass()
{
    return rand() % 100 < (75 + this->rat / 4.0);
}

int Defender::print()
{
    return this->Player::print();
}

int Defender::print(int number, int width)
{
    return this->Player::print(number, width);
}

int Defender::write(fstream& stro)
{
    return this->Player::write(stro);
}

int Defender::write(fstream& stro, int number, int width)
{
    return this->Player::write(stro, number, width);
}