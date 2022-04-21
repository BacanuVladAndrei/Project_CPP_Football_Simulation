#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Technical {
    int morale;
    int supp;
    int mood;
    int agg;
    vector<int> morale_vector;
    vector<int> aggressiveness_vector;
};

vector<int> get_morale_vector(const string& name);

int get_morale_recommendation(const vector<int>& hist_morale);

void update_morale(const string& name, vector<int>& vec, int result);

vector<int> get_aggressiveness_vector(const string& name);

int get_aggressiveness_recommendation(const vector<int>& hist_agg);

void update_aggressiveness(const string& name, vector<int>& vec, int fouls, int yc, int rc);
