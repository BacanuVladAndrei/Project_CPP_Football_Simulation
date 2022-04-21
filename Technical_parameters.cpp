#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

vector<int> get_morale_vector(const string& name)
{
    fstream mor;
    vector<int> vec;
    mor.open("morale.txt", ios::in);
    if(!mor.is_open())
    {
        for(int i = 0; i < 6; i++)
        {
            vec.push_back(-1);
        }
        return vec;
    }

    string line;
    while(getline(mor, line))
    {
        if(line.substr(0, name.length()) == name)
        {
            mor.close();
            line = line.substr(line.find('%') + 2);
            for(int i = 0; i < 6; i++)
            {
                if(line[2 * i] == 'x')
                {
                    vec.push_back(-1);
                }
                else if(line[2 * i] == '0')
                {
                    vec.push_back(0);
                }
                else if(line[2 * i] == '1')
                {
                    vec.push_back(1);
                }
                else if(line[2 * i] == '3')
                {
                    vec.push_back(3);
                }
                else
                {
                    vec.push_back(-1);
                }
            }
            return vec;
        }
    }

    for(int i = 0; i < 6; i++)
    {
        vec.push_back(-1);
    }
    mor.close();
    return vec;
}

int get_morale_recommendation(const vector<int>& hist_morale)
{
    int matches = 0;
    int sum = 0;
    for(int i = 0; i < 6; i++)
    {
        if(hist_morale[i] != -1)
        {
            matches ++;
            sum += hist_morale[i];
        }
    }

    if(matches < 3)
    {
        return -1;
    }
    else
    {
        int morale = 2 * sum / matches;
        return morale == 6 ? 5 : morale;
    }
}

void update_morale(const string& name, vector<int>& vec, int result)
{
    if(result != 3 && result != 1 && result != 0)
    {
        result = 0;
    }

    vector<int> new_vec;
    new_vec.push_back(result);
    for(int i = 0; i < 5; i++)
    {
        new_vec.push_back(vec[i]);
    }

    vec = new_vec;

    fstream morale;
    fstream new_morale;
    morale.open("morale.txt", ios::in);
    new_morale.open("new_morale.txt", ios::out);
    if(!morale.is_open())
    {
        if(!new_morale.is_open())
        {
            return;
        }
        else
        {
            new_morale.close();
            return;
        }
    }
    else
    {
        if(!new_morale.is_open())
        {
            morale.close();
            return;
        }
    }

    bool found = false;
    string line;
    while(getline(morale, line))
    {
        if(line.substr(0, name.length()) == name)
        {
            found = true;
            new_morale << name << " % ";
            for(int i = 0; i < 6; i++)
            {
                if(new_vec[i] == -1)
                {
                    new_morale << "x ";
                }
                else
                {
                    new_morale << new_vec[i] << " ";
                }
            }
            new_morale << endl;
        }
        else
        {
            new_morale << line << endl;
        }
    }

    if(!found)
    {
        new_morale << name << " % " << result << " x x x x x " << endl;
    }

    morale.close();
    new_morale.close();

    remove("morale.txt");
    rename("new_morale.txt", "morale.txt");
}

vector<int> get_aggressiveness_vector(const string& name)
{
    fstream aggr;
    vector<int> aggressiveness_vec;
    string line;
    aggr.open("aggressiveness.txt", ios::in);
    if(!aggr.is_open())
    {
        for(int i = 0; i < 6; i++)
        {
            aggressiveness_vec.push_back(-6);
        }
        return aggressiveness_vec;
    }

    while(getline(aggr, line))
    {
        if(line.substr(0, name.length()) == name)
        {
            line = line.substr(line.find('%') + 2);
            for(int i = 0; i < 6; i++)
            {
                if(line.substr(0, line.find(' ')) == "x")
                {
                    aggressiveness_vec.push_back(-6);
                }
                else
                {
                    aggressiveness_vec.push_back(stoi(line.substr(0, line.find(' '))));
                }
                line = line.substr(line.find(' ') + 1);
            }

            return aggressiveness_vec;
        }
    }

    for(int i = 0; i < 6; i++)
    {
        aggressiveness_vec.push_back(-6);
    }

    return aggressiveness_vec;
}

int get_aggressiveness_recommendation(const vector<int>& hist_agg)
{
    // Level  Fouls   YC    RC   Total
    //  -5     10.2  1.10  0.07  11.51
    //   0     13.5  1.45  0.09  15.22
    //   5     16.8  1.81  0.11  18.94
    // Slope = 1.346
    // y + 5 = 1.346 * (x - 11.51)
    // y = 1.346 * x - 20.492

    int matches = 0;
    double sum = 0;
    double mean = 0;
    for(int i = 0; i < 6; i++)
    {
        if(hist_agg[i] != -6)
        {
            matches ++;
            sum += (double)hist_agg[i];
        }
    }

    if(matches < 3)
    {
        return -6;
    }
    else
    {
        mean = sum / (double)matches;
        return (int)round(1.346 * mean - 20.492);
    }
}

void update_aggressiveness(const string& name, vector<int>& vec, int fouls, int yc, int rc)
{
    fouls = fouls < 0 ? 0 : fouls;
    yc = yc < 0 ? 0 : yc;
    rc = rc < 0 ? 0 : rc;

    int value = fouls + yc + 3 * rc;

    vector<int> new_vec;
    new_vec.push_back(value);
    for(int i = 0; i < 5; i++)
    {
        new_vec.push_back(vec[i]);
    }

    vec = new_vec;

    fstream aggressiveness;
    fstream new_aggressiveness;
    aggressiveness.open("aggressiveness.txt", ios::in);
    new_aggressiveness.open("new_aggressiveness.txt", ios::out);
    if(!aggressiveness.is_open())
    {
        if(!new_aggressiveness.is_open())
        {
            return;
        }
        else
        {
            new_aggressiveness.close();
            return;
        }
    }
    else
    {
        if(!new_aggressiveness.is_open())
        {
            aggressiveness.close();
            return;
        }
    }

    bool found = false;
    string line;
    while(getline(aggressiveness, line))
    {
        if(line.substr(0, name.length()) == name)
        {
            found = true;
            new_aggressiveness << name << " % ";
            for(int i = 0; i < 6; i++)
            {
                if(new_vec[i] == -6)
                {
                    new_aggressiveness << "x ";
                }
                else
                {
                    new_aggressiveness << new_vec[i] << " ";
                }
            }
            new_aggressiveness << endl;
        }
        else
        {
            new_aggressiveness << line << endl;
        }
    }

    if(!found)
    {
        new_aggressiveness << name << " % " << value << " x x x x x " << endl;
    }

    aggressiveness.close();
    new_aggressiveness.close();

    remove("aggressiveness.txt");
    rename("new_aggressiveness.txt", "aggressiveness.txt");
}