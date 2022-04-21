#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include "Country.h"
using namespace std;

Country::Country()
{
    this->index = 0;
    this->code = "000";
}

Country::Country(const int &index, const string& code, const string& name, const vector<string>& alt_names)
{
    this->index = index;
    this->code = code;
    this->name = name;
    this->alternative_names = alt_names;
}

Country::Country(const Country &ctr)
{
    this->index = ctr.index;
    this->code = ctr.code;
    this->name = ctr.name;
    this->alternative_names = ctr.alternative_names;
}

Country& Country::operator=(const Country &ctr)
{
    this->index = ctr.index;
    this->code = ctr.code;
    this->name = ctr.name;
    this->alternative_names = ctr.alternative_names;

    return *this;
}

ostream& operator<<(ostream &devo, const Country &ctr)
{
    devo << ctr.index << " - " << ctr.name << " (" << ctr.code << ")" << endl;

    return devo;
}

Country::~Country() {}

bool operator==(const Country& ctr1, const Country& ctr2)
{
    return ctr1.index == ctr2.index;
}

const string Country::altName(const int& i) const
{
    if(i < 0 || i >= this->alternative_names.size())
    {
        string empty;
        return empty;
    }

    return this->alternative_names[i];
}

bool operator!=(const Country& ctr1, const Country& ctr2)
{
    return ctr1.index != ctr2.index;
}

bool operator>(const Country& ctr1, const Country& ctr2)
{
    return ctr1.index > ctr2.index;
}

bool operator<(const Country& ctr1, const Country& ctr2)
{
    return ctr1.index < ctr2.index;
}

bool operator>=(const Country& ctr1, const Country& ctr2)
{
    return ctr1.index >= ctr2.index;
}

bool operator<=(const Country& ctr1, const Country& ctr2)
{
    return ctr1.index <= ctr2.index;
}

int Country::setCountry(string line)
{
    this->index = stoi(line.substr(0, 3));
    line = line.substr(4);

    this->code = line.substr(0, 3);
    line = line.substr(4);

    this->name = line.substr(0, line.find_first_of(",\n\r"));
    line = line.find_first_of(",\n\r") + 2 < line.length() ? line.substr(line.find_first_of(",\n\r") + 2) : line;

    string alt_name;
    while(line.find_first_of(",\n\r") + 2 < line.length())
    {
        alt_name = line.substr(0, line.find_first_of(",\n\r"));
        this->alternative_names.push_back(alt_name);
        line = line.substr(line.find_first_of(",\n\r") + 2);
    }

    return 0;
}

int Country::getIndex() const
{
    return this->index;
}

string Country::getCode() const
{
    return this->code;
}

string Country::getName() const
{
    return this->name;
}

int Country::getContinent() const
{
    return index / 100;
}

bool Country::refersTo(string name) const
{
    if(name == this->code)
    {
        return true;
    }

    if(name == this->name)
    {
        return true;
    }

    for(int i = 0; i < this->alternative_names.size(); i++)
    {
        if(name == this->alternative_names[i])
        {
            return true;
        }
    }

    return false;
}

Country* getCountries()
{
    fstream countries;
    Country *ctrs = new Country[233];
    if(ctrs == NULL)
    {
        return NULL;
    }
    countries.open("countries.txt", ios::in);
    if(countries.is_open())
    {
        string line;
        for(int i=0; i<233; i++)
        {
            getline(countries, line);
            ctrs[i].setCountry(line.c_str());
        }
        countries.close();
        return ctrs;
    }
    else
    {
        delete[] ctrs;
        ctrs = NULL;
        return ctrs;
    }
}

const Country getCountry(Country *countries, const int &index)
{
    for(int i=0; i<233; i++)
    {
        if(index == countries[i].index)
        {
            return countries[i];
        }
    }
    Country ctr_err;
    return ctr_err;
}

const Country getCountry(Country *countries, string str)
{
    if(str.length() < 3)
    {
        Country ctr_err;
        return ctr_err;
    }
    if(str.length() == 3)
    {
        for(int i=0; i<233; i++)
        {
            if(str == countries[i].code)
            {
                return countries[i];
            }
        }
    }
    else
    {
        for(int i=0; i<233; i++)
        {
            if(str == countries[i].code)
            {
                return countries[i];
            }
        }
    }
    Country ctr_err;
    return ctr_err;
}

Country* getCountryadd(Country *countries, const int &index)
{
    for(int i=0; i<233; i++)
    {
        if(index == countries[i].index)
        {
            return &(countries[i]);
        }
    }
    return NULL;
}

Country* getCountryadd(Country *countries, string str)
{
    if(str.length() < 3)
    {
        return NULL;
    }
    if(str.length() == 3)
    {
        for(int i=0; i<233; i++)
        {
            if(str == countries[i].code)
            {
                return &(countries[i]);
            }
        }
    }
    else
    {
        for(int i=0; i<233; i++)
        {
            if(str == countries[i].name)
            {
                return &(countries[i]);
            }
        }
    }
    return NULL;
}

double string_sim(const char *base, const char *search)
{
	int i = 0;
	int matches = 0;
	while(search[i] != '\0')
	{
		if(strchr(base, search[i]) != NULL)
		{
			matches++;
		}
		i++;
	}

	return (double)matches * 100 / (double)strlen(search);
}

void sort_sim(Country *ctrs, double *sim)
{
    bool sch = true;
    Country auxc;
    double auxd = 0.0;
    while(sch)
    {
        sch = false;
        for(int i = 0; i < 232; i++)
        {
            if(sim[i] < sim[i + 1])
            {
                auxc = ctrs[i];
                ctrs[i] = ctrs[i + 1];
                ctrs[i + 1] = auxc;
                auxd = sim[i];
                sim[i] = sim[i + 1];
                sim[i + 1] = auxd;
                sch = true;
            }
        }
    }
}

Country* countrySuggestions(Country *countries, const char *base, int &n, const double &lim)
{
    Country *ctrs = new Country[233];
    for(int i=0; i<233; i++)
    {
        ctrs[i] = countries[i];
    }

    double *sim = new double[233];
    for(int i=0; i<233; i++)
    {
        sim[i] = string_sim(base, ctrs[i].getName().c_str());
    }

    sort_sim(ctrs, sim);

    int real_count = 0;
    for(int i=0; i<n; i++)
    {
        if(sim[i] >= lim)
        {
            real_count++;
        }
    }
    n = real_count;
    if(!n)
    {
        return NULL;
    }
    
    Country *ctrs_r = new Country[n];
    for(int i=0; i<n; i++)
    {
        ctrs_r[i] = ctrs[i];
    }

    delete[] ctrs;
    delete[] sim;
    return ctrs_r;
}

bool Country::err() const
{
    return (this == NULL || (this->code == "000" && this->index == 0));
}



// ----- COUNTRIES -----

Countries::Countries()
{
    fstream ctrs;
    ctrs.open("countries.txt", ios::in);
    if(!ctrs.is_open())
    {
        cout << "Error: Could not read countries!" << endl;
        exit(-1);
    }

    string line;
    Country ctr;
    for(int i = 0; i < 233; i++)
    {
        getline(ctrs, line);
        ctr.setCountry(line.c_str());
        if(!ctr.err())
        {
            this->countries.push_back(ctr);
        }
    }

    Country err_ctr;
    this->countries.push_back(err_ctr);

    ctrs.close();
}

const Country& Countries::operator[](const int& i)
{
    if(i < 0)
    {
        return this->countries[0];
    }
    if(i > 232)
    {
        return this->countries[232];
    }

    return this->countries[i];
}

Country Countries::getCountry(string str) const
{
    for(int i = 0; i < 233; i++)
    {
        if(this->countries[i].refersTo(str))
        {
            return this->countries[i];
        }
    }

    return this->countries[233];
}

Country Countries::getCountry(const int& ind) const
{
    if(ind < 0 || ind > 624)
    {
        return this->countries[233];
    }

    for(int i = 0; i < 233; i++)
    {
        if(this->countries[i].getIndex() == ind)
        {
            return this->countries[i];
        }
    }
    return this->countries[233];
}

Country* Countries::getCountryAdd(string str) const
{
    for(int i = 0; i < 233; i++)
    {
        if(this->countries[i].refersTo(str))
        {
            Country* result_ctr = new Country;
            (*result_ctr) = this->countries[i];
            return result_ctr;
        }
    }

    return NULL;
}

Country* Countries::getCountryAdd(const int& ind) const
{
    if(ind < 0 || ind > 624)
    {
        return NULL;
    }

    for(int i = 0; i < 233; i++)
    {
        if(this->countries[i].getIndex() == ind)
        {
            Country* result_ctr = new Country;
            (*result_ctr) = this->countries[i];
            return result_ctr;
        }
    }

    return NULL;
}

vector<Country> Countries::suggestions(string typed, const int& max_elem, const double& lower_bound) const
{
    vector<CountrySim> ctr_vec;
    vector<Country> suggest;

    CountrySim ctr;
    for(int i = 0; i < 233; i++)
    {
        ctr.set(&(this->countries[i]), string_sim(typed.c_str(), this->countries[i].getName().c_str()));
        ctr_vec.push_back(ctr);
    }

    sort(ctr_vec.begin(), ctr_vec.end(), [](CountrySim a, CountrySim b) { return a < b; });

    for(int i = 0; i < max_elem; i++)
    {
        if(ctr_vec[i].getSim() > lower_bound)
        {
            suggest.push_back(ctr_vec[i].getCountry());
        }
        else
        {
            break;
        }
    }

    return suggest;
}

int presentSuggestions(const vector<Country>& suggestions)
{
    if(!suggestions.size())
    {
        return 0;
    }

    cout << "Did you mean ";
    for(int i = 0; i < suggestions.size(); i++)
    {
        cout << suggestions[i].getName();
        if(i < suggestions.size() - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << "?";
        }
    }

    return suggestions.size();
}

Country Countries::getCountry(const char* before_sugg, bool suggest, const char* after_sugg)
{
    string my_country;
    Country* country;
    vector<Country> suggests;
    do{
        getline(cin, my_country);
        country = this->getCountryAdd(my_country);
        if(country == NULL)
        {
            if(before_sugg != NULL)
            {
                cout << before_sugg;
            }
            if(suggest)
            {
                suggests = this->suggestions(my_country, 5, 80.0);
                presentSuggestions(suggests);
                cout << endl;
            }
            if(after_sugg != NULL)
            {
                cout << after_sugg;
            }
        }
    }while(country == NULL);
    
    return (*country);
}