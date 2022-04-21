#include <iostream>
#include <string>
#include "Goal.h"
#include "Penalty.h"
using namespace std;

Goal::Goal()
{
    this->scorer = NULL;
    this->assist = NULL;
    this->half = 0;
    this->min = 0;
}

Goal::Goal(Player* scorer, Player* assist, int half, int min)
{
    this->scorer = scorer;
    this->assist = assist;
    this->half = half;
    this->min = min;
}

Goal::Goal(const Goal& g)
{
    this->scorer = g.scorer;
    this->assist = g.assist;
    this->half = g.half;
    this->min = g.min;
}

Goal& Goal::operator=(const Goal& g)
{
    this->scorer = g.scorer;
    this->assist = g.assist;
    this->half = g.half;
    this->min = g.min;

    return *this;
}

Goal& Goal::operator=(const Penalty& pen)
{
    this->scorer = pen.getTaker();
    this->assist = NULL;

    return *this;
}

Player* Goal::getScorer() const
{
    return this->scorer;
}

Player* Goal::getAssist() const
{
    return this->assist;
}

int Goal::getHalf() const
{
    return this->half;
}

int Goal::getMin() const
{
    return this->min;
}

void Goal::setScorer(Player* scorer)
{
    this->scorer = scorer;
}

void Goal::setAssist(Player* assist)
{
    this->assist = assist;
}

void Goal::setHalf(int half)
{
    this->half = half;
}

void Goal::setMin(int min)
{
    this->min = min;
}

void Goal::write(fstream& stro) const
{
    string fir = this->scorer->getFirstName();
    string fam = this->scorer->getFamilyName();

    stro << fir.at(0) << ". " << fam << " (";

    fir = this->assist->getFirstName();
    fam = this->assist->getFamilyName();

    stro << fir.at(0) << ". " << fam << ") ";

    switch(this->half){
        case 1:
        {
            if(this->min < 46)
            {
                stro << this->min << "'";
            }
            else
            {
                stro << "45 + " << this->min - 45 << "'";
            }
            break;
        }
        case 2:
        {
            if(this->min < 46)
            {
                stro << this->min + 45 << "'";
            }
            else
            {
                stro << "90 + " << this->min - 45 << "'";
            }
            break;
        }
        case 3:
        {
            if(this->min < 16)
            {
                stro << this->min + 90 << "'";
            }
            else
            {
                stro << "105 + " << this->min - 15 << "'";
            }
            break;
        }
        case 4:
        {
            if(this->min < 16)
            {
                stro << this->min + 105 << "'";
            }
            else
            {
                stro << "120 + " << this->min - 15 << "'";
            }
            break;
        }
        default:
            break;
    }
}

int expectedGoals(const Team& home, const Team& away)
{
    int mood = 30 + 2*(home.getMood() + away.getMood());
    if(mood < 1)
    {
        mood = 1;
    }

    int a = rand() % 168;
    int max = 0;
    int total_goals = 0;

    if(a < 20)
    {
        max = 2;
    }
    else
        if(a < 80)
        {
            max = 3;
        }
        else
            if(a < 150)
            {
                max = 4;
            }
            else
                if(a < 160)
                {
                    max = 5;
                }
                else
                    if(a < 165)
                    {
                        max = 6;
                    }
                    else
                        if(a < 167)
                        {
                            max = 7;
                        }
                        else
                        {
                            max = 8;
                        }
    max++;

    int rat_diff;
    if(away.getRatingFinal() > home.getRatingFinal())
    {
        rat_diff = away.getRatingFinal() - home.getRatingFinal();
    }
    else
    {
        rat_diff = home.getRatingFinal() - away.getRatingFinal();
    }

    max += rat_diff / 8;
    total_goals = mood * max / 60;

    return (int)total_goals;
}

int minScoreChance(int half, int min)
{
    switch(half){
        case 1:
        {
            if(min < 16)
            {
                return 116;
            }
            else
            {
                if(min < 31)
                {
                    return 140;
                }
                else
                {
                    return 145;
                }
            }
            break;
        }
        case 2:
        {
            if(min < 16)
            {
                return 155;
            }
            else
            {
                if(min < 31)
                {
                    return 151;
                }
                else
                {
                    return 235;
                }
            }
            break;
        }
        case 3:
        {
            return 172;
            break;
        }
        case 4:
        {
            return 190;
            break;
        }
        default:
        {
            return 0;
            break;
        }
    }
}

bool scoreMin(int total_goals, int half, int min, int mins_in_half, int& cooldown)
{
    int a = rand() % mins_in_half;
    int x, y, cd = cooldown * cooldown * cooldown * cooldown;
    cooldown--;
    if(cooldown < 1)
    {
        cooldown = 1;
    }

    if(a < 3 * total_goals / 2)
    {
        x = 1;
    }
    else
    {
        x = 0;
    }

    a = rand() % 235;
    if(a < minScoreChance(half, min))
    {
        y = 1;
    }
    else
    {
        y = 0;
    }

    bool cld;
    if(cd == 0)
    {
        cld = 1;
    }
    else
    {
        cld = !(rand() % cd);
    }

    if(x && y && cld)
    {
        cooldown = 4;
        return 1;
    }
    else
    {
        return 0;
    }
}

bool scoreTeam(double rat_h, double rat_a, int goals_home, int goals_away)
{
    double diff = rat_h - rat_a;
    double ho = rat_h + 2 * diff;
    if(goals_home < goals_away)
    {
        ho += goals_away - goals_home;
    }
    if(ho < 1)
    {
        ho = 1.0;
    }
    double aw = rat_a - 2 * diff;
    if(goals_away < goals_home)
    {
        aw += goals_home - goals_away;
    }
    if(aw < 1)
    {
        aw = 1.0;
    }

    double rat_home = ho * ho * ho; // + FORMATION PARAMETERS!!!
    double rat_away = aw * aw * aw; // + FORMATION PARAMETERS!!!
    double rat_sum = rat_home + rat_away;

    int a = rand() % (int)rat_sum;
    
    return a < rat_away;
}

Player* playerScores(vector<Player*> players)
{
    int min_rat = 100;
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i]->getRat() < min_rat)
        {
            min_rat = players[i]->getRat();
        }
    }

    int chances_sum = 0;
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->goalChance(min_rat);
        chances_sum += chances[i];
    }

    if(chances_sum == 0)
    {
        return NULL;
    }

    int lim = rand() % chances_sum;
    chances_sum = 0;
    for(int i = 0; i < players.size(); i++)
    {
        chances_sum +=chances[i];
        if(lim < chances_sum)
        {
            return players[i];
        }
    }

    return NULL;
}

Player* playerAssist(vector<Player*> players, Player* scorer)
{
    int min_rat = 100;
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i]->getRat() < min_rat)
        {
            min_rat = players[i]->getRat();
        }
    }

    int chances_sum = 0;
    int* chances = new int[players.size()];
    for(int i = 0; i < players.size(); i++)
    {
        chances[i] = players[i]->assistChance(scorer, min_rat);
        chances_sum += chances[i];
    }

    if(chances_sum == 0)
    {
        return NULL;
    }

    int lim = rand() % chances_sum;
    chances_sum = 0;
    for(int i = 0; i < players.size(); i++)
    {
        chances_sum +=chances[i];
        if(lim < chances_sum)
        {
            return players[i];
        }
    }

    return NULL;
}

Goal* Score(vector<Player*> home_pl, double home_rat, int home_mood, vector<Player*> away_pl, double away_rat, int away_mood, int total_goals, int goals_home, int goals_away, int half, int min, int mins_in_half, int& cooldown)
{
    bool g = scoreMin(total_goals, half, min, mins_in_half, cooldown);
    if(g)
    {
        Goal *goal = new Goal;
        goal->half = half;
        goal->min = min;
        bool who = scoreTeam(home_rat, away_rat, goals_home, goals_away);
        goal->team = who;
        if(!who)
        {
            goal->scorer = playerScores(home_pl);
            goal->assist = playerAssist(home_pl, goal->scorer);
            goals_home++;
        }
        else
        {
            goal->scorer = playerScores(away_pl);
            goal->assist = playerAssist(away_pl, goal->scorer);
            goals_away++;
        }
        return goal;
    }
    else
    {
        return NULL;
    }
}

bool Goal::updatePlayer()
{
    if(this->scorer != NULL)
    {
        this->scorer->incrementGoals(1);
    }
    else
    {
        return 1;
    }
    if(this->assist != NULL)
    {
        this->assist->incrementAssists(1);
    }
    else
    {
        return 1;
    }

    return 0;
}

void Goal::printList()
{
    cout << "Goal: " << this->scorer->getFirstName().at(0) << ". " << this->scorer->getFamilyName() << " ";
    if(this->assist != NULL)
    {
        cout << "(" << this->assist->getFirstName().at(0) << ". " << this->assist->getFamilyName() << ") ";
    }
    this->printMinute();
    cout << "'" << endl;
}