#include <iostream>
#include <string>
#include "Player.h"
#include "Forward.h"
using namespace std;

Forward& Forward::operator=(const Player& player)
{
    this->first_name = player.getFirstName();
    this->family_name = player.getFamilyName();
    this->nationality = player.getNationality();
    this->ctr = player.getCtr();
    this->pos = 'F';
    this->birth_date = player.getBirthDate();
    this->age = player.getAge();
    this->cond = player.getCond();
    this->rat = player.getRat();
    this->on = player.getStatus();
    this->InitStatistics();

    return *this;
}

void Forward::InitStatistics()
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

string Forward::getFirstName() const
{
    return this->first_name;
}

string Forward::getFamilyName() const
{
    return this->family_name;
}

Country* Forward::getNationality() const
{
    return this->nationality;
}

string Forward::getCtr() const
{
    return this->ctr;
}

char Forward::getPos() const
{
    return this->pos;
}

struct tm Forward::getBirthDate() const
{
    return this->birth_date;
}

int Forward::getAge() const
{
    return this->age;
}

int Forward::getCond() const
{
    return this->cond;
}

int Forward::getRat() const
{
    return this->rat;
}

int Forward::getStatus() const
{
    return this->on;
}

int Forward::getMinsPlayed() const
{
    return this->mins_played;
}

int Forward::incrementMins()
{
    return this->Player::incrementMins();
}

int Forward::Cond()
{
    return this->Player::Cond();
}

double Forward::getMark()
{
    return 0.0;
}

int Forward::goalChance(int min_rat)
{
    return 463 * this->Player::goalChance(min_rat);
}

int Forward::assistChance(Player* scorer, int min_rat)
{
    return 18 * this->Player::assistChance(scorer, min_rat);
}

int Forward::penaltyTakerChance(int min_rat)
{
    return 120 * this->Player::penaltyTakerChance(min_rat);
}

int Forward::penaltyGuiltyChance(int max_rat)
{
    return 3 * this->Player::penaltyGuiltyChance(max_rat);
}

int Forward::shotTakerChance(int min_rat)
{
    return 15 * this->Player::shotTakerChance(min_rat);
}

int Forward::foulAgainstChance(char opp_pos)
{
    if(this->on < 1)
    {
        return 0;
    }
    switch(opp_pos) {
        case 'G':
        {
            return 3;
            break;
        }
        case 'D':
        {
            return 20;
            break;
        }
        case 'M':
        {
            return 12;
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

int Forward::foulChance(int max_rat)
{
    return 5 * this->Player::foulChance(max_rat);
}

int Forward::offsideChance()
{
    return 8 * this->Player::offsideChance();
}

int Forward::cornerTakerChance()
{
    return 5;
}

int Forward::cornerTouchChance()
{
    return 5;
}

int Forward::passChance()
{
    return (this->on == 1 || this->on == 2) ? 10 : 0;
}

bool Forward::accuratePass()
{
    return rand() % 100 < (25 + this->rat / 2.0);
}

int Forward::print()
{
    return this->Player::print();
}

int Forward::print(int number, int width)
{
    return this->Player::print(number, width);
}

int Forward::write(fstream& stro)
{
    return this->Player::write(stro);
}

int Forward::write(fstream& stro, int number, int width)
{
    return this->Player::write(stro, number, width);
}