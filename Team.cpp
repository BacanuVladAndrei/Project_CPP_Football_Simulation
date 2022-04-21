#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "Team.h"
#include "Administrative_functions.h"
#include "Country.h"
#include "Minute.h"
#include "Goalkeeper.h"
#include "Defender.h"
#include "Midfielder.h"
#include "Forward.h"
using namespace std;

Country* getCountryadd(Country*, string);

vector<Player*> read_players(fstream&, Countries, int&, int, bool);
int printPlayersTable(Player**, int);

Team::Team()
{
    this->type = 0;
    this->name = '\0';
    this->rating.final = 0.0;
    this->rating.total = 0.0;
    this->rating.def = 0.0;
    this->rating.mid = 0.0;
    this->rating.off = 0.0;
    this->technical_parameters.morale = 0;
    this->technical_parameters.supp = 0;
    this->technical_parameters.mood = 0;
    this->technical_parameters.agg = 0;
    this->subs_left = 3;
    this->in = 11;
    this->out = 0;
    this->formation.set(0, 0, 0);
    this->nationality = NULL;
    this->goalscorers = NULL;
}

void Team::initStatistics()
{
    this->statistics.goals = 0;
    this->statistics.possession = 0.0;
    this->statistics.shots = 0;
    this->statistics.shots_on_target = 0;
    this->statistics.shot_accuracy = 0.0;
    this->statistics.shot_efficiency = 0.0;
    this->statistics.goalkeeper_saves = 0;
    this->statistics.offsides = 0;
    this->statistics.corners = 0;
    this->statistics.passes = 0;
    this->statistics.accurate_passes = 0;
    this->statistics.pass_accuracy = 0.0;
    this->statistics.fouls = 0;
    this->statistics.yellow_cards = 0;
    this->statistics.red_cards = 0;
}

Team::Team(bool type, string name, int morale, int supp, int mood, int agg, vector<Player*> players, vector<Player*> substitutes, int out, Country* nationality)
{
    this->type = type;
    this->name = name;
    //Rating
    this->technical_parameters.morale = morale;
    this->technical_parameters.supp = supp;
    this->technical_parameters.mood = mood;
    this->technical_parameters.agg = agg;
    this->players = players;
    this->substitutes = substitutes;
    this->subs_left = 3;
    this->in = 11;
    this->out = out;
    this->formation.computeFormation(this->players, 11);
    this->nationality = NULL;
    this->goalscorers = NULL;
    this->initStatistics();
}

Team::Team(const Team& team)
{
    this->type = team.type;
    this->name = team.name;
    this->rating = team.rating;
    this->technical_parameters = team.technical_parameters;
    this->in = team.in;
    this->players = team.players;
    this->out = team.out;
    this->substitutes = team.substitutes;
    this->subs_left = team.subs_left;
    this->formation = team.formation;
    this->nationality = team.nationality;
    this->goalscorers = team.goalscorers;
}

Team& Team::operator=(const Team& team)
{
    this->type = team.type;
    this->name = team.name;
    this->rating = team.rating;
    this->technical_parameters = team.technical_parameters;
    this->in = team.in;
    this->players = team.players;
    this->out = team.out;
    this->substitutes = team.substitutes;
    this->subs_left = team.subs_left;
    this->formation = team.formation;
    this->nationality = team.nationality;
    this->goalscorers = team.goalscorers;

    return *this;
}

Team::~Team() {}

void Team::computeRatings()
{
    Rating sum;
    sum.total = 0.0;
    sum.def = 0.0;
    sum.mid = 0.0;
    sum.off = 0.0;
    for(int i = 0; i < this->in; i++)
    {
        switch(this->players[i]->getPos()){
            case 'G':
            {
                sum.total += this->players[i]->getRat();
                break;
            }
            case 'D':
            {
                sum.def += this->players[i]->getRat();
                break;
            }
            case 'M':
            {
                sum.mid += this->players[i]->getRat();
                break;
            }
            case 'F':
            {
                sum.off += this->players[i]->getRat();
                break;
            }
            default:
                break;
        }
    }

    sum.def = sum.def / this->formation.getD();
    sum.mid = sum.mid / this->formation.getM();
    sum.off = sum.off / this->formation.getF();

    this->rating.def = (5 * sum.total + 10 * sum.def + 3 * sum.mid + sum.off) / 19;
    this->rating.mid = (3 * sum.def + 10 * sum.mid + 3 * sum.off) / 16;
    this->rating.off = (sum.def + 3 * sum.mid + 10 * sum.off) / 14;
    this->rating.total = (this->rating.def + this->rating.mid + this->rating.off) / 3;
    this->rating.final = this->rating.total;
}

void Team::readTechnicalParameters()
{
    this->technical_parameters.morale_vector = get_morale_vector(this->name);
    this->technical_parameters.morale = get_morale_recommendation(this->technical_parameters.morale_vector);
    this->technical_parameters.aggressiveness_vector = get_aggressiveness_vector(this->name);
    this->technical_parameters.agg = get_aggressiveness_recommendation(this->technical_parameters.aggressiveness_vector);

    // Morale
    bool can_default = (this->technical_parameters.morale != -1);
    cout << "Team morale (0 - 5";
    if(can_default)
    {
        cout << ", recommended " << this->technical_parameters.morale;
    }
    cout << "): ";
    opt_mor:
    char mor = option("012345\n");
    if(mor != '\n')
    {
        this->technical_parameters.morale = mor - 48;
        cout << endl;
    }
    else
    {
        if(!can_default)
        {
            goto opt_mor;
        }
    }
    
    // Crowd support
    cout << "Crowd support (0 - 5): ";
    if(!(this->type))
    {
        this->technical_parameters.supp = option("012345") - 48;
        cout << endl;
    }
    else
    {
        this->technical_parameters.supp = 0;
        cout << "0" << endl;
    }

    // Mood
    cout << "Defensive / Offensive (-5 - 5): ";
    char mod1 = option("-012345");
    cout << endl;
    if(mod1 == '-')
    {
        this->technical_parameters.mood = 48 - option("12345");
        cout << endl;
    }
    else
    {
        this->technical_parameters.mood = mod1 - 48;
    }

    // Aggressiveness
    can_default = (this->technical_parameters.agg != -6);
    cout << "Aggressiveness (-5 - 5";
    if(can_default)
    {
        cout << ", recommended " << this->technical_parameters.agg;
    }
    cout << "): ";
    char agg1 = option("-012345\n");
    if(agg1 == '-')
    {
        this->technical_parameters.agg = 48 - option("12345");
        cout << endl;
    }
    else if(agg1 == '\n')
    {
        // Continue
    }
    else
    {
        this->technical_parameters.agg = agg1 - 48;
        cout << endl;
    }
}

void Team::readNationality(Countries countries)
{
    this->nationality = countries.getCountryAdd(this->name.c_str());
    if(this->nationality != NULL)
    {
        cout << "Country: " << this->nationality->getName() << endl;
        return;
    }

    string country;
    do{
        cout << "Country: ";
        getline(cin, country);
        this->nationality = countries.getCountryAdd(country.c_str());
        if(this->nationality == NULL)
        {
            int nr_ctr = 5;
            vector<Country> suggest = countries.suggestions(country, nr_ctr, 80.0);
            cout << "Country not found! Did you mean ";
            for(int i = 0; i < suggest.size(); i++)
            {
                cout << suggest[i].getName();
                if(i < nr_ctr - 1)
                {
                    cout << ", ";
                }
                else
                {
                    cout << "?" << endl;
                }
            }
        }
    }while(this->nationality == NULL);
}

void Team::readName()
{
    do{
        cout << "Name: ";
        getline(cin, this->name);
        if(this->name.length() < 4)
        {
            cout << "Team's name must be at least 4 characters long!" << endl;
        }
        if(this->name.length() > 100)
        {
            cout << "Team's name must be at most 100 characters long!" << endl;
        }
    }while(this->name.length() < 4 || this->name.length() > 100);
}

void Team::readPlayers(Countries countries)
{
    cout << "Do you want to..." << endl;
    cout << "    P - enter players by hand" << endl;
    cout << "    F - read players from file" << endl;
    cout << "Option: ";
    char o = option("PpFf", NULL);
    cout << endl;

    if(o == 'F' || o == 'f')
    {
        fstream steam;
        string stream_name;
        string entered = this->name;
        int error = 0;
        int ok = 0;
        do{
            stream_name = replace_chars(entered.c_str(), '_', " -");
            if(stream_name.substr(stream_name.length() - 4, 4) != ".txt")
            {
                stream_name += ".txt";
            }
            steam.open(stream_name, ios::in);
            if(steam.is_open())
            {
                do{
                    if(error)
                    {
                        cout << "Correct the error and press enter! ";
                        option("\n", NULL);
                        steam.clear();
                        steam.seekg(0);
                    }
                    cout << "Checking file..." << endl;
                    error = checkPlayersFile(steam, countries);
                }while(!interpretError(error));
                steam.clear();
                steam.seekg(0);
                this->players = read_players(steam, countries, this->in, 11, true);
                this->substitutes = read_players(steam, countries, this->out, 25, false);
                if((this->players.size() == 11) && (this->substitutes.size() > 6) && (this->substitutes.size() < 26))
                {
                    cout << "Players read successfully!" << endl;
                }
            }
            else
            {
                cout << "File \"" << stream_name << "\" doesn't exist! Enter the name of the file: ";
                getline(cin, entered); 
            }
        }while(!steam.is_open());
        steam.close();
    }
    else
    {
        // Field players
        this->in = 11;
        bool already_one_gk = false;
        Player dummy;
        for(int i = 0; i < this->in; i++)
        {
            cout << "PLAYER " << i + 1 << endl;
            dummy.read(countries, true, already_one_gk, ((!already_one_gk) && (i == 10)));
            switch(dummy.getPos())
            {
                case 'G':
                {
                    already_one_gk = true;
                    Goalkeeper* gk = new Goalkeeper;
                    (*gk) = dummy;
                    this->players.push_back(gk);
                    break;
                }
                case 'D':
                {
                    Defender* def = new Defender;
                    (*def) = dummy;
                    this->players.push_back(def);
                    break;
                }
                case 'M':
                {
                    Midfielder* mid = new Midfielder;
                    (*mid) = dummy;
                    this->players.push_back(mid);
                    break;
                }
                case 'F':
                {
                    Forward* fwd = new Forward;
                    (*fwd) = dummy;
                    this->players.push_back(fwd);
                    break;
                }
                default:
                {
                    cout << "Error! Unknown player type." << endl;
                    break;
                }
            }
            cout << endl;
        }
        cout << endl;
        do{
            cout << "Number of substitutes: ";
            string nr_subs;
            getline(cin, nr_subs);
            if(nr_subs.length())
            {
                cout << "Invalid number!" << endl;
                this->out = 0;
            }
            else
            {
                this->out = stoi(nr_subs);
                if(this->out < 7 || this->out > 25)
                {
                    cout << "The number of substitutes must range between 7 and 25!" << endl;
                }
            }
        }while(this->out < 7 || this->out > 25);
        for(int i = 0; i < this->out; i++)
        {
            cout << "SUBSTITUTE " << i + 1 << endl;
            dummy.read(countries, false, false, false);
            switch(dummy.getPos())
            {
                case 'G':
                {
                    Goalkeeper* gk = new Goalkeeper;
                    (*gk) = dummy;
                    this->substitutes.push_back(gk);
                    break;
                }
                case 'D':
                {
                    Defender* def = new Defender;
                    (*def) = dummy;
                    this->substitutes.push_back(def);
                    break;
                }
                case 'M':
                {
                    Midfielder* mid = new Midfielder;
                    (*mid) = dummy;
                    this->substitutes.push_back(mid);
                    break;
                }
                case 'F':
                {
                    Forward* fwd = new Forward;
                    (*fwd) = dummy;
                    this->substitutes.push_back(fwd);
                    break;
                }
                default:
                {
                    cout << "Error! Unknown player type." << endl;
                    break;
                }
            }
            cout << endl;
        }
    }
}

void Team::read(Countries countries, bool type)
{
    this->type = type;
    this->readName();
    this->readNationality(countries);
    this->readTechnicalParameters();
    this->readPlayers(countries);
    this->subs_left = 3;
    this->formation.computeFormation(this->players, this->in);
    this->computeRatings();
    this->goalscorers = NULL;
}

void Team::print()
{
    if(this->type)
    {
        cout << "---AWAY TEAM---" << endl << endl;
    }
    else
    {
        cout << "---HOME TEAM---" << endl << endl;
    }

    cout << "Name: " << this->name << endl;
    cout << "Country: " << this->nationality->getName() << endl;

    cout << "Rating" << endl;
    cout << setprecision(2) << fixed;
    cout << "    DEF: " << this->rating.def << endl;
    cout << "    MID: " << this->rating.mid << endl;
    cout << "    OFF: " << this->rating.off << endl;
    cout << "    OVR: " << this->rating.total << endl;

    string mor[] = { "Extremely Low (0)", "Low (1)", "Average (2)", "High (3)", "Very High (4)", "Marvellous (5)" };
    cout << "Morale: " << mor[this->technical_parameters.morale] << endl;
    if(!(this->type))
    {
        string sup[] = { "No Support (0)", "Weak (1)", "Lukewarm (2)", "Average (3)", "Good (4)", "Outstanding (5)" };
        cout << "Crowd support: " << sup[this->technical_parameters.supp] << endl;
    }
    string mod[] = { "Ultra-Defensive (-5)", "Very Defensive (-4)", "Defensive (-3)", "Rather Defensive (-2)", "Slightly Defensive (-1)", "Balanced (0)", "Slightly Offensive (1)", "Rather Offensive (2)", "Offensive (3)", "Very Offensive (4)", "Ultra-Offensive (5)" };
    cout << "Strategy: " << mod[this->technical_parameters.mood + 5] << endl;
    cout << "Aggressiveness: " << this->technical_parameters.agg << endl;

    cout << "Formation: " << this->formation << endl;
    cout << endl << "          PLAYERS" << endl;
    printPlayersTable(this->players, this->in);
    cout << endl << "          SUBSTITUTES" << endl;
    printPlayersTable(this->substitutes, this->out);
    cout << endl << endl;
}

void Team::printPlayerStatistics()
{
    int max_str = 0;
    for(int i = 0; i < this->in; i++)
    {
        if(this->players[i]->getFirstName().length() + this->players[i]->getFamilyName().length() + 1 > max_str)
        {
            max_str = this->players[i]->getFirstName().length() + this->players[i]->getFamilyName().length() + 1;
        }
    }
    for(int i = 0; i < this->out; i++)
    {
        if(this->substitutes[i]->getFirstName().length() + this->substitutes[i]->getFamilyName().length() + 1 > max_str)
        {
            max_str = this->substitutes[i]->getFirstName().length() + this->substitutes[i]->getFamilyName().length() + 1;
        }
    }

    cout << "Name";
    for(int i = 4; i < max_str + 3; i++)
    {
        cout << " ";
    }
    cout << "Pos  Minutes  Goals   Goals    Assists  Shots  Shots on    Shot       Shot     Saves  Offsides  Passes  Accurate    Pass      Fouls     Fouls    Yellow  Red   FINAL MARK" << endl;
    for(int i = 0; i < max_str + 3; i++)
    {
        cout << " ";
    }
    cout << "     Played          Received                   Target   Accuracy  Efficiency                            Passes   Accuracy  Committed  Suffered   Card   Card" << endl;
    for(int i = 0; i < this->in; i++)
    {
        this->players[i]->printStatistics(max_str + 3);
    }
    for(int i = 0; i < this->out; i++)
    {
        this->substitutes[i]->printStatistics(max_str + 3);
    }
}

int Team::doSubstitution(int half, int min, int goal_diff)
{
    int chances = 0;
    int a = rand() % 900;
    if(half == 1)
    {
        chances = 3;
    }
    if(min == 1 && half == 2)
    {
        if(goal_diff > -2)
            chances = 800;
        else
            chances = 800 - 30 * goal_diff;
    }
    else
        if(half == 2)
        {
            if(goal_diff < -1)
            {
                if(min < 25)
                    chances = 25 + 2 * min - min * goal_diff;//30
                else
                    chances = 25 + 2 * min - (45 - min) * goal_diff;//30
            }
            else
                if(min < 16)
                    chances = 35 + 2 * min;//40
                else
                    if(min < 31)
                        chances = min + 40;
                    else
                        chances = 40 + 3 * min / 2;
        }
    bool do_subs;
    if(a < chances)
        do_subs = true;
    else
        do_subs = false;

    if(!do_subs)
    {
        return 0;
    }

    int c1, c2, c3, sum = 0;
    int nr = 0;
    if(goal_diff > -2)
    {
        //sum=210;
        int r = rand() % 7;
        c1 = 197 - r;
        c2 = 12 + r;
        c3 = 1;
    }
    else
    {
        if(goal_diff == -2)
        {
            int r = rand() % 25;
            c1 = 164 - r;
            if(r > 8 && r < 17)
            {
                c2 = 41 + r;
                c3 = 5;
            }
            else if(r > 16)
            {
                c2 = 40 + r;
                c3 = 6;
            }
            else
            {
                c2 = 42+r;
                c3 = 4;
            }
        }
        else
        {
            if(goal_diff < -2)
            {
                c1 = 141;
                c2 = 63;
                c3 = 6;
            }
        }
    }
    sum = c1 + c2 + c3;
    int b = rand() % sum;
    if(b < c1)
    {
        nr = 1;
    }
    else
        if(b < c1 + c2)
        {
            nr = 2;
        }
        else
        {
            nr = 3;
        }
    return this->subs_left < nr ? this->subs_left : nr;
}

bool Team::substitution(Player*& player, Player*& sub)
{
    if(player == NULL || sub == NULL)
    {
        return false;
    }
    else
    {
        Player* aux;
        aux = player;
        player = sub;
        sub = aux;
        player->setStatus(2);
        sub->setStatus(-1);
        return true;
    }
}

void Team::decidePositions(char& pos_off, char& pos_on, int goal_diff)
{
    //F -> D : 0
    //F -> M : 1
    //M -> D : 1
    //same   : 2
    //M -> F : 3
    //D -> M : 3
    //D -> F : 4
    int* v = new int[5]();

    switch(goal_diff){
        case 0:
            v[0]=1;
            v[1]=5;
            v[2]=88;
            v[3]=5;
            v[4]=1;
            break;
        case 1:
            v[0]=7;
            v[1]=23;
            v[2]=67;
            v[3]=2;
            v[4]=1;
            break;
        case -1:
            v[0]=1;
            v[1]=2;
            v[2]=67;
            v[3]=22;
            v[4]=8;
            break;
        case 2:
            v[0]=2;
            v[1]=9;
            v[2]=85;
            v[3]=3;
            v[4]=1;
            break;
        case -2:
            v[0]=1;
            v[1]=3;
            v[2]=85;
            v[3]=9;
            v[4]=2;
            break;
        default:
            v[0]=1;
            v[1]=4;
            v[2]=90;
            v[3]=4;
            v[4]=1;
            break;
    }

    int sub_case = wrand(v, 5);
    switch(sub_case) {
        case 0:
            {
                pos_off = 'F';
                pos_on = 'D';
                break;
            }
        case 1:
            {
                if(rand() % 2)
                {
                    pos_off = 'M';
                    pos_on = 'D';
                }
                else
                {
                    pos_off = 'F';
                    pos_on = 'M';
                }
                break;
            }
        case 2:
            {
                int c[] = { 1, 1, 1 };
                switch(wrand(c, 3)) {
                    case 0:
                        {
                            pos_off = 'F';
                            pos_on = 'F';
                            break;
                        }
                    case 1:
                        {
                            pos_off = 'M';
                            pos_on = 'M';
                            break;
                        }
                    case 2:
                        {
                            pos_off = 'D';
                            pos_on = 'D';
                            break;
                        }
                    default:
                        break;
                }
                break;
            }
        case 3:
            {
                if(rand() % 2)
                {
                    pos_off = 'D';
                    pos_on = 'M';
                    break;
                }
                else
                {
                    pos_off = 'M';
                    pos_on = 'F';
                }
                break;
            }
        case 4:
            {
                pos_off = 'D';
                pos_on = 'F';
                break;
            }
        default:
            break;
    }

    delete[] v;
}

Player*& Team::getSubstitutionOff(char pos)
{
    int max_rat = 0;
    for(int i = 0; i < this->getIn(); i++)
    {
        if(this->players[i]->getRat() > max_rat)
        {
            max_rat = this->players[i]->getRat();
        }
    }

    int* chances = new int[this->getIn()]();
    bool found = false;
    for(int i = 0; i < this->getIn(); i++)
    {
        if(this->players[i]->getPos() == pos)
        {
            found = true;
            chances[i] = this->players[i]->chancesSubstitutionOff(max_rat);
        }
    }

    if(!found)
    {
        delete[] chances;
        return this->players[0];
    }
    else
    {
        int pl = wrand(chances, this->getIn());
        delete[] chances;
        return this->players[pl];
    }
}

Player*& Team::getSubstitutionOn(char pos)
{
    int min_rat = 200;
    for(int i = 0; i < this->getOut(); i++)
    {
        if(this->substitutes[i]->getRat() < min_rat)
        {
            min_rat = this->substitutes[i]->getRat();
        }
    }

    int* chances = new int[this->getOut()]();
    bool found = false;
    for(int i = 0; i < this->getOut(); i++)
    {
        if(this->substitutes[i]->getPos() == pos)
        {
            found = true;
            chances[i] = this->substitutes[i]->chancesSubstitutionOn(min_rat);
        }
    }

    if(!found)
    {
        delete[] chances;
        return this->substitutes[0];
    }
    else
    {
        int pl = wrand(chances, this->getOut());
        delete[] chances;
        return this->substitutes[pl];
    }
}

int* Team::Substitutions(int half, int min, int goals_against, int& number)
{
    int nr = this->doSubstitution(half, min, this->getGoals() - goals_against);
    char pos_on = '\0';
    char pos_off = '\0';
    
    bool done = false;
    number = 0;
    int* vector = new int[nr]();

    for(int i = 0; i < nr; i++)
    {
        done = false;
        this->decidePositions(pos_off, pos_on, this->getGoals() - goals_against);
        Player*& pl_off = this->getSubstitutionOff(pos_off);
        Player*& pl_on = this->getSubstitutionOn(pos_on);
        if(pl_off != NULL && pl_on != NULL)
        {
            if(pos_off == pos_on)
            {
                if(pl_off->getRat() <= pl_on->getRat())
                {
                    substitution(pl_off, pl_on);
                    done = true;
                }
            }
            else
            {
                substitution(pl_off, pl_on);
                done = true;
            }
            if(done)
            {
                number++;
                this->subs_left--;
                this->formation.incrementPosition(pos_on);
                this->formation.incrementPosition(pos_off, -1);
                vector[number - 1] = 100 * this->getPlayerIndex(pl_off, 1) + this->getPlayerIndex(pl_on, 0);
            }
        }
    }
    vector = Resize<int>(vector, nr, number);

    return vector;
}

void Team::incrementMinutesPlayed()
{
    for(int i = 0; i < this->in; i++)
    {
        if(this->players[i]->getStatus() == 1 || this->players[i]->getStatus() == 2)
        {
            this->players[i]->incrementMinutesPlayed();
        }
    }
}

int Team::getPlayerIndex(Player* player, bool on) const
{
    if(on)
    {
        for(int i = 0; i < this->getIn(); i++)
        {
            if(this->getPlayer(i) == player)
            {
                return i;
            }
        }
        return this->getIn();
    }
    else
    {
        for(int i = 0; i < this->getOut(); i++)
        {
            if(this->getSubstitute(i) == player)
            {
                return i;
            }
        }
        return this->getOut();
    }
}

int Team::getPlayerIndex(const string& full_name, bool search_lineup, bool search_substitutes) const
{
    int index = -1;
    string name;
    if(search_lineup)
    {
        for(int i = 0; i < this->players.size(); i++)
        {
            name = this->getPlayer(i)->getFirstName() + " " + this->getPlayer(i)->getFamilyName();
            if(full_name == name)
            {
                index = i;
                break;
            }
        }
    }

    if(search_substitutes && index == -1)
    {
        for(int i = 0; i < this->substitutes.size(); i++)
        {
            name = this->getSubstitute(i)->getFirstName() + " " + this->getSubstitute(i)->getFamilyName();
            if(full_name == name)
            {
                index = i + 11;
                break;
            }
        }
    }

    return index;
}

void Team::printSubstitution(int off_index, int on_index, int half, int min)
{
    if(off_index >= this->getIn())
    {
        cout << "Index exceeds array bounds: OFF!" << endl;
    }
    if(on_index >= this->getOut())
    {
        cout << "Index exceeds array bounds: ON!" << endl;
    }

    Event aux(half, min, 0);
    cout << "Substitution ";
    aux.printMinute();
    cout << "': " << this->name << endl;
    cout << "OFF: " << this->getSubstitute(on_index)->getFirstName().at(0) << ". " << this->getSubstitute(on_index)->getFamilyName() << endl;
    cout << "ON: " << this->getPlayer(off_index)->getFirstName().at(0) << ". " << this->getPlayer(off_index)->getFamilyName() << endl;
}

void Team::printSubstitutions(int* v, int count, int half, int min)
{
    for(int i = 0; i < count; i++)
    {
        this->printSubstitution(v[i] / 100, v[i] % 100, half, min);
    }
}

Player* Team::getBestPlayer(bool playing, bool substitute) const
{
    Player* best_playing = NULL;
    int max_playing = 0;
    Player* best_substitute = NULL;
    int max_substitute = 0;

    if(playing && this->players.size())
    {
        for(int i = 0; i < this->players.size(); i++)
        {
            if(this->players[i]->getRat() > max_playing)
            {
                max_playing = this->players[i]->getRat();
                best_playing = this->players[i];
            }
        }
    }

    if(substitute && this->substitutes.size())
    {
        for(int i = 0; i < this->substitutes.size(); i++)
        {
            if(this->substitutes[i]->getRat() > max_substitute)
            {
                max_substitute = this->substitutes[i]->getRat();
                best_substitute = this->substitutes[i];
            }
        }
    }

    if(best_playing == NULL)
    {
        if(best_substitute == NULL)
        {
            return NULL;
        }
        else
        {
            return best_substitute;
        }
    }
    else
    {
        if(best_substitute == NULL)
        {
            return best_playing;
        }
        else
        {
            return (best_playing->getRat() < best_substitute->getRat() ? best_substitute : best_playing);
        }
    }
}

int checkPlayersFileLine(string line, const Countries& countries, bool cant_be_gk, bool must_be_gk, bool& already_one_gk)
{
    if(count(line.begin(), line.end(), ',') < 5)
    {
        return 1; // Not enough arguments
    }
    if(count(line.begin(), line.end(), ',') > 5)
    {
        return 2; // Too many arguments
    }

    // We do have enough arguments

    // Check first name
    string name = line.substr(0, line.find(','));
    if(name.length() < 3)
    {
        return 3; // First name too short
    }
    line = line.substr(line.find(',') + 1);

    // Check family name
    while(line[0] == ' ')
    {
        line = line.substr(1);
    }
    name = line.substr(0, line.find(','));
    if(name.length() < 3)
    {
        return 4; // Family name too short
    }
    line = line.substr(line.find(',') + 1);

    // Check nationality
    while(line[0] == ' ')
    {
        line = line.substr(1);
    }
    string nation;
    nation = line.substr(0, line.find(','));
    if(countries.getCountryAdd(nation) == NULL)
    {
        return 5; // Invalid nationality
    }
    line = line.substr(line.find(',') + 1);

    // Check position
    while(line[0] == ' ')
    {
        line = line.substr(1);
    }
    char pos;
    if(line.length())
    {
        pos = line[0];
    }
    else
    {
        return 9; // Invalid position
    }
    switch(pos)
    {
        case 'G':
        {
            already_one_gk = true;
            if(cant_be_gk)
            {
                return 6; // Can not be goalkeeper
            }
            break;
        }
        case 'D': case 'M': case 'F':
        {
            if(must_be_gk)
            {
                return 7; // Must be goalkeeper
            }
            break;
        }
        case 'g': case 'd': case 'm': case 'f':
        {
            return 8; // Lowercase position
            break;
        }
        default:
        {
            return 9; // Invalid position
            break;
        }
    }
    line = line.substr(line.find(',') + 1);

    // Check rating
    string raw_rating = line.substr(0, line.find(','));
    string actual_rating;
    for(int i = 0; i < raw_rating.length(); i++)
    {
        if(is_digit(raw_rating[i]))
        {
            actual_rating += raw_rating[i];
        }
    }
    if(actual_rating.length())
    {
        if(stoi(actual_rating) < 1)
        {
            return 11; // Rating less than 1
        }
        if(stoi(actual_rating) > 100)
        {
            return 12; // Rating exceeds 100
        }
    }
    else
    {
        return 10; // Invalid rating
    }
    line = line.substr(line.find(',') + 1);

    // Check birth date
    while(line[0] == ' ')
    {
        line = line.substr(1);
    }
    if(line.length() < 8)
    {
        return 13; // Incorrect date format
    }
    string bdt = line.substr(0, 8);

        // Check format
        if(bdt[2] != '/' || bdt[5] != '/')
        {
            return 13; // Incorrect date format
        }

        // Check year
        if(!is_digit(bdt[6]) || !is_digit(bdt[7]))
        {
            return 14; // Invalid year
        }

        // Check month
        if(is_digit(bdt[3]) && is_digit(bdt[4]))
        {
            if((10 * (bdt[3] - 48) + (bdt[4] - 48) < 1) || (10 * (bdt[3] - 48) + (bdt[4] - 48) > 12))
            {
                return 15; // Invalid month
            }
        }
        else
        {
            return 15; // Invalid month
        }

        // Check day
        int days_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if((10 * (bdt[6] - 48) + (bdt[7] - 48)) % 4 == 0 || ((bdt[6] == 48) && (bdt[7] == 48)))
        {
            days_month[1] = 29;
        }
        if(is_digit(bdt[0]) && is_digit(bdt[1]))
        {
            if(10 * (bdt[0] - 48) + (bdt[1] - 48) < 1 || 10 * (bdt[0] - 48) + (bdt[1] - 48) > days_month[10 * (bdt[3] - 48) + (bdt[4] - 48) - 1])
            {
                return 16; // Invalid day
            }
        }
        else
        {
            return 16; // Invalid day
        }

    // Nothing seems to be wrong. If there is, you will be the one complaining.
    return 0;
}

int checkPlayersFile(fstream& stream, const Countries& countries)
{
    if(!stream.is_open())
    {
        return -1; // Stream closed
    }

    int no_of_lines = 0;
    bool already_one_gk = false;
    string line;
    int line_status = 0;
    while(getline(stream, line))
    {
        no_of_lines ++;
        
        if(no_of_lines > 11)
        {
            already_one_gk = false;
        }
        line_status = checkPlayersFileLine(line, countries, already_one_gk, ((no_of_lines == 11) && (!already_one_gk)), already_one_gk);
        if(line_status)
        {
            return (no_of_lines * 100 + line_status);
        }
    }

    if(no_of_lines < 18)
    {
        return -2; // Too few lines
    }

    if(no_of_lines > 36)
    {
        return -3; // Too many lines, may_pass = true
    }

    return 0;
}

bool interpretError(int error)
{
    bool may_pass = false;
    if(error < 0)
    {
        cout << "ERROR!" << endl;
        switch(error)
        {
            case -1:
            {
                cout << "Could not check file!" << endl;
                may_pass = false;
                break;
            }
            case -2:
            {
                cout << "Too few players in file!" << endl;
                cout << "A team must have at least 18 players (11 in the starting line-up and 7 substitutes)." << endl;
                may_pass = false;
                break;
            }
            case -3:
            {
                cout << "Too many players in file (limit = 36)!" << endl;
                may_pass = true;
                break;
            }
            default:
            {
                may_pass = false;
                break;
            }
        }
    }
    else
    {
        if(error == 0)
        {
            may_pass = true;
            return may_pass;
        }
        else
        {
            cout << "ERROR!" << endl;
            int err = error % 100;
            int line = error / 100;
            cout << "Line: " << line << endl;
            cout << "Problem: ";
            switch(err)
            {
                case 1:
                {
                    cout << "Not enough arguments!" << endl;
                    break;
                }
                case 2:
                {
                    cout << "Too many arguments!" << endl;
                    break;
                }
                case 3:
                {
                    cout << "First name too short! Must be at least 3 characters long." << endl;
                    break;
                }
                case 4:
                {
                    cout << "Family name too short! Must be at least 3 characters long."  << endl;
                    break;
                }
                case 5:
                {
                    cout << "Invalid nationality!" << endl;
                    break;
                }
                case 6:
                {
                    cout << "Can not be a goalkeeper! There already is one in the starting line up." << endl;
                    break;
                }
                case 7:
                {
                    cout << "Must be a goalkeeper! There isn't another one in the starting line up." << endl;
                    break;
                }
                case 8:
                {
                    cout << "Position must be provided as an uppercase character (G, D, M, F)!" << endl;
                    break;
                }
                case 9:
                {
                    cout << "Invalid position!" << endl;
                    break;
                }
                case 10:
                {
                    cout << "Invalid rating!" << endl;
                    break;
                }
                case 11:
                {
                    cout << "Rating is less than 1!" << endl;
                    break;
                }
                case 12:
                {
                    cout << "Rating exceeds 100!" << endl;
                    break;
                }
                case 13:
                {
                    cout << "Incorrect date format! Date must be provided as DD/MM/YY." << endl;
                    break;
                }
                case 14:
                {
                    cout << "Invalid year!" << endl;
                    break;
                }
                case 15:
                {
                    cout << "Invalid month!" << endl;
                    break;
                }
                case 16:
                {
                    cout << "Invalid day!" << endl;
                    break;
                }
                default:
                {
                    cout << "Unknown." << endl;
                }
            }
            may_pass = false;
        }
    }

    return may_pass;
}

// Editing functions

bool Team::editName(const string new_name)
{
    if(new_name.length() > 3 && new_name.length() < 101)
    {
        this->name = new_name;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::editType(const bool new_type)
{
    this->type = new_type;
    return true;
}

bool Team::editMorale(const int new_morale)
{
    if(new_morale > -1 && new_morale < 6)
    {
        this->technical_parameters.morale = new_morale;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::editMood(const int new_mood)
{
    if(new_mood > -6 && new_mood < 6)
    {
        this->technical_parameters.mood = new_mood;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::editAggressiveness(const int new_agg)
{
    if(new_agg > -6 && new_agg < 6)
    {
        this->technical_parameters.agg = new_agg;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::editNationality(Country* new_nationality)
{
    if(new_nationality != NULL)
    {
        this->nationality = new_nationality;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::addPlayer(Player* new_player)
{
    if(this->substitutes.size() < 25 && new_player != NULL)
    {
        switch(new_player->getPos())
        {
            case 'G':
            {
                Goalkeeper *gk = new Goalkeeper;
                (*gk) = (*new_player);
                this->substitutes.push_back(gk);
                break;
            }
            case 'D':
            {
                Defender *def = new Defender;
                (*def) = (*new_player);
                this->substitutes.push_back(def);
                break;
            }
            case 'M':
            {
                Midfielder *mid = new Midfielder;
                (*mid) = (*new_player);
                this->substitutes.push_back(mid);
                break;
            }
            case 'F':
            {
                Forward *fwd = new Forward;
                (*fwd) = (*new_player);
                this->substitutes.push_back(fwd);
                break;
            }
            default:
            {
                this->out --;
                break;
            }
        }
        this->out ++;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::removePlayer(const int index)
{
    if(this->substitutes.size() > 7 && (index > -1 && index < this->substitutes.size()))
    {
        delete this->substitutes[index];
        this->substitutes.erase(this->substitutes.begin() + index);
        this->out --;
        return true;
    }
    else
    {
        return false;
    }
}

bool Team::editPlayer(const bool playing, const int index, Player* new_player)
{
    if(playing)
    {
        if(index > -1 && index < 11 && new_player != NULL)
        {
            switch(this->players[index]->getPos())
            {
                case 'D':
                {
                    this->setFormation(this->getFormation().getD() - 1, this->getFormation().getM(), this->getFormation().getF());
                    break;
                }
                case 'M':
                {
                    this->setFormation(this->getFormation().getD(), this->getFormation().getM() - 1, this->getFormation().getF());
                    break;
                }
                case 'F':
                {
                    this->setFormation(this->getFormation().getD(), this->getFormation().getM(), this->getFormation().getF() - 1);
                    break;
                }
                default:
                {
                    break;
                }
            }
            switch(new_player->getPos())
            {
                case 'G':
                {
                    Goalkeeper *new_player_cast = new Goalkeeper;
                    (*new_player_cast) = (*new_player);
                    delete this->players[index];
                    this->players[index] = new_player_cast;
                    break;
                }
                case 'D':
                {
                    Defender *new_player_cast = new Defender;
                    (*new_player_cast) = (*new_player);
                    delete this->players[index];
                    this->players[index] = new_player_cast;
                    this->setFormation(this->getFormation().getD() + 1, this->getFormation().getM(), this->getFormation().getF());
                    break;
                }
                case 'M':
                {
                    Midfielder *new_player_cast = new Midfielder;
                    (*new_player_cast) = (*new_player);
                    delete this->players[index];
                    this->players[index] = new_player_cast;
                    this->setFormation(this->getFormation().getD(), this->getFormation().getM() + 1, this->getFormation().getF());
                    break;
                }
                case 'F':
                {
                    Forward *new_player_cast = new Forward;
                    (*new_player_cast) = (*new_player);
                    delete this->players[index];
                    this->players[index] = new_player_cast;
                    this->setFormation(this->getFormation().getD(), this->getFormation().getM(), this->getFormation().getF() + 1);
                    break;
                }
                default:
                {
                    this->out --;
                    break;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(index > -1 && index < this->substitutes.size() && new_player != NULL)
        {
            switch(new_player->getPos())
            {
                case 'G':
                {
                    Goalkeeper *new_player_cast = new Goalkeeper;
                    delete this->substitutes[index];
                    this->substitutes[index] = new_player_cast;
                    break;
                }
                case 'D':
                {
                    Defender *new_player_cast = new Defender;
                    (*new_player_cast) = (*new_player);
                    delete this->substitutes[index];
                    this->substitutes[index] = new_player_cast;
                    break;
                }
                case 'M':
                {
                    Midfielder *new_player_cast = new Midfielder;
                    (*new_player_cast) = (*new_player);
                    delete this->substitutes[index];
                    this->substitutes[index] = new_player_cast;
                    break;
                }
                case 'F':
                {
                    Forward *new_player_cast = new Forward;
                    (*new_player_cast) = (*new_player);
                    delete this->substitutes[index];
                    this->substitutes[index] = new_player_cast;
                    break;
                }
                default:
                {
                    this->out --;
                    break;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Team::substitutePlayers(const int index_off, const int index_on)
{
    cout << "Indexes: " << index_off << " " << index_on << endl;
    if(index_off < 0 || index_off > 10 || index_on < 0 || index_on > this->getSubstitutes().size() - 1)
    {
        return false;
    }
    cout << "Positions: " << this->getPlayers()[index_off]->getPos() << " " << this->getSubstitutes()[index_on]->getPos() << endl;
    if((this->getPlayers()[index_off]->getPos() == 'G' && this->getSubstitutes()[index_on]->getPos() != 'G') || (this->getPlayers()[index_off]->getPos() != 'G' && this->getSubstitutes()[index_on]->getPos() == 'G'))
    {
        return false;
    }

    switch(this->getPlayers()[index_off]->getPos())
    {
        case 'D':
        {
            this->setFormation(this->getFormation().getD() - 1, this->getFormation().getM(), this->getFormation().getF());
            break;
        }
        case 'M':
        {
            this->setFormation(this->getFormation().getD(), this->getFormation().getM() - 1, this->getFormation().getF());
            break;
        }
        case 'F':
        {
            this->setFormation(this->getFormation().getD(), this->getFormation().getM(), this->getFormation().getF() - 1);
            break;
        }
        default:
        {
            break;
        }
    }

    switch(this->getSubstitutes()[index_on]->getPos())
    {
        case 'D':
        {
            this->setFormation(this->getFormation().getD() + 1, this->getFormation().getM(), this->getFormation().getF());
            break;
        }
        case 'M':
        {
            this->setFormation(this->getFormation().getD(), this->getFormation().getM() + 1, this->getFormation().getF());
            break;
        }
        case 'F':
        {
            this->setFormation(this->getFormation().getD(), this->getFormation().getM(), this->getFormation().getF() + 1);
            break;
        }
        default:
        {
            break;
        }
    }

    cout << "Before: " << this->getPlayers().at(index_off)->getFamilyName() << " - " << this->getSubstitutes().at(index_on)->getFamilyName() << endl;
    // swap(this->getPlayers().at(index_off), this->getSubstitutes().at(index_on));
    Player* aux = this->getPlayers().at(index_off);
    this->getPlayers().at(index_off) = this->getSubstitutes().at(index_on);
    this->getSubstitutes().at(index_on) = aux;
    this->getPlayers().at(index_off)->setStatus(true);
    this->getSubstitutes().at(index_on)->setStatus(false);
    cout << "After: " << this->getPlayers().at(index_off)->getFamilyName() << " - " << this->getSubstitutes().at(index_on)->getFamilyName() << endl;
    return true;
}

bool Team::editTeam(Countries countries, const char what)
{
    string trial;
    bool success = false;
    switch(what)
    {
        case 'N': // Name
        {
            do{
                cout << "Current name: " << this->name << endl;
                cout << "New name: ";
                getline(cin, trial);
                success = editName(trial);
                if(!success)
                {
                    cout << "The team's name must not be shorter than 4 characters or longer than 100!" << endl;
                }
            }while(!success);
            break;
        }
        case 'M': // Morale
        {
            do{
                getmorale:
                cout << "Current morale: " << this->technical_parameters.morale << endl;
                cout << "New morale: ";
                getline(cin, trial);
                for(int i = 0; i < trial.length(); i++)
                {
                    if(trial[i] < 48 || trial[i] > 57)
                    {
                        trial.erase(i);
                        i--;
                    }
                }
                if(!trial.length())
                {
                    cout << "Invalid value!" << endl;
                    goto getmorale;
                }
                if(stoi(trial) > 5 || stoi(trial) < 0)
                {
                    cout << "Morale must range between 0 and 5!" << endl;
                }
            }while(stoi(trial) > 5 || stoi(trial) < 0);
            success = editMorale(stoi(trial));
            break;
        }
        case 'S': // Mood
        {
            do{
                getmood:
                cout << "Current mood: " << this->technical_parameters.mood << endl;
                cout << "New mood: ";
                getline(cin, trial);
                for(int i = 0; i < trial.length(); i++)
                {
                    if((trial[i] < 48 || trial[i] > 57) && trial[i] != '-')
                    {
                        trial.erase(i);
                        i--;
                    }
                }
                if(!trial.length() || (count(trial.begin(), trial.end(), '-') == trial.length()))
                {
                    cout << "Invalid value!" << endl;
                    goto getmood;
                }
                if(stoi(trial) > 5 || stoi(trial) < -5)
                {
                    cout << "Mood must range between -5 and 5!" << endl;
                }
            }while(stoi(trial) > 5 || stoi(trial) < -5);
            success = editMood(stoi(trial));
            break;
        }
        case 'A': // Aggressiveness
        {
            do{
                getagg:
                cout << "Current aggressiveness: " << this->technical_parameters.agg << endl;
                cout << "New aggressiveness: ";
                getline(cin, trial);
                for(int i = 0; i < trial.length(); i++)
                {
                    if((trial[i] < 48 || trial[i] > 57) && trial[i] != '-')
                    {
                        trial.erase(i);
                        i--;
                    }
                }
                if(!trial.length() || (count(trial.begin(), trial.end(), '-') == trial.length()))
                {
                    cout << "Invalid value!" << endl;
                    goto getagg;
                }
                if(stoi(trial) > 5 || stoi(trial) < -5)
                {
                    cout << "Aggressiveness must range between -5 and 5!" << endl;
                }
            }while(stoi(trial) > 5 || stoi(trial) < -5);
            success = editAggressiveness(stoi(trial));
            break;
        }
        case 'C': // Nationality
        {
            Country* new_nationality = NULL;
            vector<Country> suggestions;
            do{
                cout << "Current nationality: " << this->nationality->getName() << endl;
                cout << "New nationality: ";
                getline(cin, trial);
                new_nationality = countries.getCountryAdd(trial);
                if(new_nationality == NULL)
                {
                    cout << "Invalid nationality!" << endl;
                    suggestions = countries.suggestions(trial, 5, 80.0);
                    presentSuggestions(suggestions);
                    cout << endl;
                }
            }while(new_nationality == NULL);
            success = editNationality(new_nationality);
            break;
        }
        case 'P': // Players
        {
            cout << "Select an option: " << endl;
            cout << "    A - Add new player*" << endl;
            cout << "    R - Remove player*" << endl;
            cout << "    E - Edit player" << endl;
            cout << "    S - Substitute players" << endl;
            cout << "    * these operations can only be done on substitutes." << endl;
            cout << "Option: ";
            char opt = option("AaSsRrEe");
            cout << endl;
            switch(opt)
            {
                case 'A': case 'a': // Add new player
                {
                    cout << "ADD PLAYER" << endl;
                    Player* new_player = new Player;
                    new_player->read(countries, false, false, false);
                    success = this->addPlayer(new_player);
                    break;
                }
                case 'R': case 'r': // Remove player
                {
                    cout << "REMOVE PLAYER" << endl;
                    int index = -1;
                    do{
                        cout << "Enter his full name, first and family separated by one space: ";
                        getline(cin, trial);
                        index = this->getPlayerIndex(trial, false, true);
                        if(index == -1)
                        {
                            cout << "This player does not exist!" << endl;
                        }
                    }while(index == -1);
                    success = this->removePlayer(index - 11);
                    break;
                }
                case 'E': case 'e': // Edit player
                {
                    int index = -1;
                    cout << "EDIT PLAYER" << endl;
                    do{
                        cout << "Enter his full name, first and family separated by one space: ";
                        getline(cin, trial);
                        index = this->getPlayerIndex(trial, true, true);
                        if(index == -1)
                        {
                            cout << "This player does not exist!" << endl;
                        }
                    }while(index == -1);
                    Player* new_player = new Player;
                    new_player->read(countries, (index < 11), (index < 11 && this->getPlayer(index)->getPos() != 'G'), (index < 11 && this->getPlayer(index)->getPos() == 'G'));
                    success = this->editPlayer((index < 11), (index > 10 ? index - 11 : index), new_player);
                    this->computeRatings();
                    break;
                }
                case 'S': case 's': // Substitute players
                {
                    cout << "SUBSTITUTE PLAYERS" << endl;
                    int index_off = -1;
                    int index_on = -1;
                    do{
                        cout << "Full name of player to come OFF ([first name] [family name]): ";
                        getline(cin, trial);
                        index_off = this->getPlayerIndex(trial, true, false);
                        if(index_off == -1)
                        {
                            cout << "This player does not exist!" << endl;
                        }
                    }while(index_off == -1);
                    do{
                        cout << "Full name of substitute to come ON ([first name] [family name]): ";
                        getline(cin, trial);
                        index_on = this->getPlayerIndex(trial, false, true);
                        if(index_on == -1)
                        {
                            cout << "This substitute does not exist!" << endl;
                        }
                    }while(index_on == -1);
                    success = this->substitutePlayers(index_off, index_on - 11);
                    if(!success)
                    {
                        cout << "Invalid substitution between a goalkeeper and a field player!" << endl;
                    }
                    this->computeRatings();
                    break;
                }
                default:
                {
                    cout << "Unknown command!" << endl;
                    success = false;
                    break;
                }
            }
            break;
        }
        default:
        {
            return false;
        }
    }

    return success;
}