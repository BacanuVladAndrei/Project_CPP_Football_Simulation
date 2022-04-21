#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Referees.h"
#include "Administrative_functions.h"
using namespace std;

Referees::Referees() {}

Referees::Referees(Referee mainRef, Referee ass1Ref, Referee ass2Ref, Referee sideRef, Referee var1Ref, Referee var2Ref)
{
    this->mainRef = mainRef;
    this->ass1Ref = ass1Ref;
    this->ass2Ref = ass2Ref;
    this->sideRef = sideRef;
    this->var1Ref = var1Ref;
    this->var2Ref = var2Ref;
}

bool validNationality(Country* nationality, const int& country1, const int& country2)
{
    if(nationality == NULL)
    {
        return false;
    }

    if(country1 == country2)
    {
        return true;
    }
    else
    {
        return !(nationality->getIndex() == country1 || nationality->getIndex() == country2);
    }
}

int Referees::readReferees(Countries countries, const int& country1, const int& country2)
{
    string name;
    string nationality;
    Country* nat;
    bool valid = 1;

    // Main Referee
    cout << "MAIN REFEREE" << endl;

    do{
        cout << "Name: ";
        getline(cin, name);
        if(name.length() < 4)
        {
            cout << "Name too short!" << endl;
        }
    }while(name.length() < 4);

    do{
        cout << "Nationality: ";
        getline(cin, nationality);
        nat = countries.getCountryAdd(nationality.c_str());
        if(nat == NULL)
        {
            cout << "Nationality does not exist! Try again." << endl;
        }
        else
        {
            if(!validNationality(nat, country1, country2))
            {
                cout << "Referee's nationality can not coincide with one of the teams'!" << endl;
            }
        }
    }while(nat == NULL || !validNationality(nat, country1, country2));

    if(this->mainRef.setReferee(name, nat, 100))
    {
        return 1;
    }

    // Assistant 1
    cout << "ASSISTANT 1" << endl;

    do{
        cout << "Name: ";
        getline(cin, name);
        if(name.length() < 4)
        {
            cout << "Name too short!" << endl;
        }
    }while(name.length() < 4);

    do{
        cout << "Nationality: ";
        getline(cin, nationality);
        nat = countries.getCountryAdd(nationality.c_str());
        if(nat == NULL)
        {
            cout << "Nationality does not exist! Try again." << endl;
        }
        else
        {
            if(!validNationality(nat, country1, country2))
            {
                cout << "Referee's nationality can not coincide with one of the teams'!" << endl;
            }
        }
    }while(nat == NULL || !validNationality(nat, country1, country2));

    if(this->ass1Ref.setReferee(name, nat, 010))
    {
        return 1;
    }

    // Assistant 2
    cout << "ASSISTANT 2" << endl;

    do{
        cout << "Name: ";
        getline(cin, name);
        if(name.length() < 4)
        {
            cout << "Name too short!" << endl;
        }
    }while(name.length() < 4);

    do{
        cout << "Nationality: ";
        getline(cin, nationality);
        nat = countries.getCountryAdd(nationality.c_str());
        if(nat == NULL)
        {
            cout << "Nationality does not exist! Try again." << endl;
        }
        else
        {
            if(!validNationality(nat, country1, country2))
            {
                cout << "Referee's nationality can not coincide with one of the teams'!" << endl;
            }
        }
    }while(nat == NULL || !validNationality(nat, country1, country2));

    if(this->ass2Ref.setReferee(name, nat, 010))
    {
        return 1;
    }

    // 4th Official
    cout << "4th OFFICIAL" << endl;

    do{
        cout << "Name: ";
        getline(cin, name);
        if(name.length() < 4)
        {
            cout << "Name too short!" << endl;
        }
    }while(name.length() < 4);

    do{
        cout << "Nationality: ";
        getline(cin, nationality);
        nat = countries.getCountryAdd(nationality.c_str());
        if(nat == NULL)
        {
            cout << "Nationality does not exist! Try again." << endl;
        }
        else
        {
            if(!validNationality(nat, country1, country2))
            {
                cout << "Referee's nationality can not coincide with one of the teams'!" << endl;
            }
        }
    }while(nat == NULL || !validNationality(nat, country1, country2));

    if(this->sideRef.setReferee(name, nat, 010))
    {
        return 1;
    }

    // VAR 1
    cout << "VAR 1" << endl;

    do{
        cout << "Name: ";
        getline(cin, name);
        if(name.length() < 4)
        {
            cout << "Name too short!" << endl;
        }
    }while(name.length() < 4);

    do{
        cout << "Nationality: ";
        getline(cin, nationality);
        nat = countries.getCountryAdd(nationality.c_str());
        if(nat == NULL)
        {
            cout << "Nationality does not exist! Try again." << endl;
        }
        else
        {
            if(!validNationality(nat, country1, country2))
            {
                cout << "Referee's nationality can not coincide with one of the teams'!" << endl;
            }
        }
    }while(nat == NULL || !validNationality(nat, country1, country2));

    if(this->var1Ref.setReferee(name, nat, 001))
    {
        return 1;
    }

    // VAR 2
    cout << "VAR 2" << endl;

    do{
        cout << "Name: ";
        getline(cin, name);
        if(name.length() < 4)
        {
            cout << "Name too short!" << endl;
        }
    }while(name.length() < 4);

    do{
        cout << "Nationality: ";
        getline(cin, nationality);
        nat = countries.getCountryAdd(nationality.c_str());
        if(nat == NULL)
        {
            cout << "Nationality does not exist! Try again." << endl;
        }
        else
        {
            if(!validNationality(nat, country1, country2))
            {
                cout << "Referee's nationality can not coincide with one of the teams'!" << endl;
            }
        }
    }while(nat == NULL || !validNationality(nat, country1, country2));

    if(this->var2Ref.setReferee(name, nat, 001))
    {
        return 1;
    }

    return 0;
}

int Referees::autoReferees(Countries countries, const int& country1, const int& country2)
{
    Country* pitch_nationality = NULL;
    Country* var_nationality = NULL;
    string pnat;
    bool randomize_pitch = false;
    string vnat;
    bool randomize_var = false;

    do{
        cout << "Pitch referees' nationality (enter to randomize): ";
        getline(cin, pnat);
        if(pnat.length())
        {
            pitch_nationality = countries.getCountryAdd(pnat.c_str());
            if(pitch_nationality == NULL)
            {
                cout << "Nationality does not exist! Try again." << endl;
            }
            else
            {
                if(!validNationality(pitch_nationality, country1, country2))
                {
                    cout << "Referees' nationality can not coincide with one of the teams'!" << endl;
                }
            }
        }
        else
        {
            randomize_pitch = true;
        }
    }while(!randomize_pitch && !validNationality(pitch_nationality, country1, country2));
    
    do{
        cout << "VAR nationality (enter to randomize): ";
        getline(cin, vnat);
        if(vnat.length())
        {
            var_nationality = countries.getCountryAdd(vnat.c_str());
            if(var_nationality == NULL)
            {
                cout << "Nationality does not exist! Try again." << endl;
            }
            else
            {
                if(!validNationality(var_nationality, country1, country2))
                {
                    cout << "Referees' nationality can not coincide with one of the teams'!" << endl;
                }
            }
        }
        else
        {
            randomize_var = true;
        }
    }while(!randomize_var && !validNationality(var_nationality, country1, country2));

    if(randomize_pitch || randomize_var)
    {
        // Decide random countries
        Country* random_pitch_nationality = new Country;
        Country* random_var_nationality = new Country;
        this->decideCountries(countries, country1, country2, *random_pitch_nationality, *random_var_nationality);
        if(pitch_nationality == NULL)
        {
            pitch_nationality = random_pitch_nationality;
        }
        if(var_nationality == NULL)
        {
            var_nationality = random_var_nationality;
        }
    }

    this->findReferees(countries, pitch_nationality, var_nationality);

    return 0;
}

int Referees::findReferees(Countries countries, Country* nat_pitch, Country* nat_var)
{
    if(nat_pitch == NULL || nat_var == NULL)
    {
        return 1;
    }

    vector<Referee> main;
    vector<Referee> assistants;
    vector<Referee> var;
    int rand_main;
    int rand_ass;
    int rand_var;
    bool done = false;

    fstream referees;
    string refs;
    refs = "referees/";
    refs += replace_chars(nat_pitch->getName().c_str(), '_', " -");
    refs += ".txt";
    referees.open(refs, ios::in);
    if(referees.is_open())
    {
        Referee referee;
        while(getline(referees, refs))
        {
            referee.setReferee(countries, refs);
            if(referee.isMain())
            {
                main.push_back(referee);
            }
            if(referee.isAss())
            {
                assistants.push_back(referee);
            }
            if(referee.isVAR() && nat_pitch->getIndex() == nat_var->getIndex())
            {
                var.push_back(referee);
            }
        }

        // Choose Main Referee
        rand_main = rand() % main.size();
        this->mainRef = main[rand_main];

        // Choose Assistants
        rand_ass = rand() % assistants.size();
        this->ass1Ref = assistants[rand_ass];

        do{
            rand_ass = rand() % assistants.size();
        }while(assistants[rand_ass].getName() != "Unknown" && this->ass1Ref.getName() == assistants[rand_ass].getName());
        this->ass2Ref = assistants[rand_ass];

        do{
            rand_ass = rand() % assistants.size();
        }while(assistants[rand_ass].getName() != "Unknown" && (this->ass1Ref.getName() == assistants[rand_ass].getName() || this->ass2Ref.getName() == assistants[rand_ass].getName()));
        this->sideRef = assistants[rand_ass];

        // If necessary
        if(nat_pitch->getIndex() == nat_var->getIndex())
        {
            // Choose VAR
            do{
                rand_var = rand() % var.size();
            }while(var[rand_var].getName() != "Unknown" && (this->ass1Ref.getName() == var[rand_var].getName() || this->ass2Ref.getName() == var[rand_var].getName() || this->sideRef.getName() == var[rand_var].getName() || this->mainRef.getName() == var[rand_var].getName()));
            this->var1Ref = var[rand_var];

            do{
                rand_var = rand() % var.size();
            }while(var[rand_var].getName() != "Unknown" && (this->ass1Ref.getName() == var[rand_var].getName() || this->ass2Ref.getName() == var[rand_var].getName() || this->sideRef.getName() == var[rand_var].getName() || this->mainRef.getName() == var[rand_var].getName() || this->var1Ref.getName() == var[rand_var].getName()));
            this->var2Ref = var[rand_var];

            done = true;
        }

        referees.close();
        if(done)
        {
            return 0;
        }
    }
    else
    {
        return 2;
    }

    // Choose VAR from another country
    refs = "referees/";
    refs += replace_chars(nat_var->getName().c_str(), '_', " -");
    refs += ".txt";
    referees.open(refs, ios::in);
    if(referees.is_open())
    {
        Referee referee;
        while(getline(referees, refs))
        {
            referee.setReferee(countries, refs);
            if(referee.isVAR())
            {
                var.push_back(referee);
            }
        }

        rand_var = rand() % var.size();
        this->var1Ref = var[rand_var];

        do{
            rand_var = rand() % var.size();
        }while(this->var1Ref.getName() == var[rand_var].getName() && var[rand_var].getName() != "Unknown");
        this->var2Ref = var[rand_var];

        referees.close();
    }
    else
    {
        return 3;
    }

    return 0;
}

int decideEurope(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[61] = {};
    int var[61] = {};

    referees.open("referees/Chances_Europe.txt", ios::in);
    if(referees.is_open())
    {
        string line;
        int ind;

        // Filling chances vectors
        for(int i = 0; i < 60; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            ind = ind - 100;
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        // Reglementations
        pitch[country1 - 100] = 0;
        var[country1 - 100] = 0;
        pitch[country2 - 100] = 0;
        var[country2 - 100] = 0;

        // Selection
        int pitch_index = wrand(pitch, 61) + 100;
        int var_index = wrand(var, 61) + 100;

        // Conversion to countries
        pitch_nationality = countries.getCountry(pitch_index);
        var_nationality = countries.getCountry(var_index);

        referees.close();
        return (pitch_nationality.err() || var_nationality.err());
    }
    else
    {
        return 1;
    }
}

int decideAsia(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[71] = {};
    int var[71] = {};

    referees.open("referees/Chances_Asia.txt", ios::in);
    if(referees.is_open())
    {
        string line;
        int ind;

        // Filling chances vectors
        for(int i = 0; i < 47; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            ind = ind - 200;
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        // Reglementations
        pitch[country1 - 200] = 0;
        var[country1 - 200] = 0;
        pitch[country2 - 200] = 0;
        var[country2 - 200] = 0;

        // Selection
        int pitch_index = wrand(pitch, 71) + 200;
        int var_index = wrand(var, 71) + 200;

        // Conversion to countries
        pitch_nationality = countries.getCountry(pitch_index);
        var_nationality = countries.getCountry(var_index);

        referees.close();
        return (pitch_nationality.err() || var_nationality.err());
    }
    else
    {
        return 1;
    }
}

int decideAfrica(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[76] = {};
    int var[76] = {};

    referees.open("referees/Chances_Africa.txt", ios::in);
    if(referees.is_open())
    {
        string line;
        int ind;

        // Filling chances vectors
        for(int i = 0; i < 57; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            ind = ind - 300;
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        // Reglementations
        pitch[country1 - 300] = 0;
        var[country1 - 300] = 0;
        pitch[country2 - 300] = 0;
        var[country2 - 300] = 0;

        // Selection
        int pitch_index = wrand(pitch, 76) + 300;
        int var_index = wrand(var, 76) + 300;

        // Conversion to countries
        pitch_nationality = countries.getCountry(pitch_index);
        var_nationality = countries.getCountry(var_index);

        referees.close();
        return (pitch_nationality.err() || var_nationality.err());
    }
    else
    {
        return 1;
    }
}

int decideNorthAmerica(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[52] = {};
    int var[52] = {};

    referees.open("referees/Chances_North_America.txt", ios::in);
    if(referees.is_open())
    {
        string line;
        int ind;

        // Filling chances vectors
        for(int i = 0; i < 42; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            ind = ind - 400;
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        // Reglementations
        pitch[country1 - 400] = 0;
        var[country1 - 400] = 0;
        pitch[country2 - 400] = 0;
        var[country2 - 400] = 0;

        // Selection
        int pitch_index = wrand(pitch, 52) + 400;
        int var_index = wrand(var, 52) + 400;

        // Conversion to countries
        pitch_nationality = countries.getCountry(pitch_index);
        var_nationality = countries.getCountry(var_index);

        referees.close();
        return (pitch_nationality.err() || var_nationality.err());
    }
    else
    {
        return 1;
    }
}

int decideSouthAmerica(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[11] = {};
    int var[11] = {};

    referees.open("referees/Chances_South_America.txt", ios::in);
    if(referees.is_open())
    {
        string line;
        int ind;

        // Filling chances vectors
        for(int i = 0; i < 10; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            ind = ind - 500;
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        // Reglementations
        pitch[country1 - 500] = 0;
        var[country1 - 500] = 0;
        pitch[country2 - 500] = 0;
        var[country2 - 500] = 0;

        // Selection
        int pitch_index = wrand(pitch, 11) + 500;
        int var_index = wrand(var, 11) + 500;

        // Conversion to countries
        pitch_nationality = countries.getCountry(pitch_index);
        var_nationality = countries.getCountry(var_index);

        referees.close();
        return (pitch_nationality.err() || var_nationality.err());
    }
    else
    {
        return 1;
    }
}

int decideOceania(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[25] = {};
    int var[25] = {};

    referees.open("referees/Chances_Oceania.txt", ios::in);
    if(referees.is_open())
    {
        string line;
        int ind;

        // Filling chances vectors
        for(int i = 0; i < 17; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            ind = ind - 600;
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        // Reglementations
        pitch[country1 - 600] = 0;
        var[country1 - 600] = 0;
        pitch[country2 - 600] = 0;
        var[country2 - 600] = 0;

        // Selection
        int pitch_index = wrand(pitch, 25) + 600;
        int var_index = wrand(var, 25) + 600;

        // Conversion to countries
        pitch_nationality = countries.getCountry(pitch_index);
        var_nationality = countries.getCountry(var_index);

        referees.close();
        return (pitch_nationality.err() || var_nationality.err());
    }
    else
    {
        return 1;
    }
}

int decideWorld(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality)
{
    fstream referees;
    int pitch[625] = {};
    int var[625] = {};
    string line;
    int ind;

    referees.open("referees/Chances_Europe.txt", ios::in);
    if(referees.is_open())
    {
        // Filling chances vectors Europe
        for(int i = 0; i < 60; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        referees.close();
    }
    else
    {
        return 1;
    }

    referees.open("referees/Chances_Asia.txt", ios::in);
    if(referees.is_open())
    {
        // Filling chances vectors Asia
        for(int i = 0; i < 47; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }

        referees.close();
    }
    else
    {
        return 2;
    }

    referees.open("referees/Chances_Africa.txt", ios::in);
    if(referees.is_open())
    {
        // Filling chances vectors Africa
        for(int i = 0; i < 57; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }
        
        referees.close();
    }
    else
    {
        return 3;
    }

    referees.open("referees/Chances_North_America.txt", ios::in);
    if(referees.is_open())
    {
        // Filling chances vectors North America
        for(int i = 0; i < 42; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }
        
        referees.close();
    }
    else
    {
        return 4;
    }

    referees.open("referees/Chances_South_America.txt", ios::in);
    if(referees.is_open())
    {
        // Filling chances vectors South America
        for(int i = 0; i < 10; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }
        
        referees.close();
    }
    else
    {
        return 5;
    }

    referees.open("referees/Chances_Oceania.txt", ios::in);
    if(referees.is_open())
    {
        // Filling chances vectors Oceania
        for(int i = 0; i < 17; i++)
        {
            getline(referees, line);
            ind = stoi(line.substr(0, 3));
            line = line.substr(4);
            pitch[ind] = stoi(line.substr(0, line.find(' ')));
            line = line.substr(line.find(' ') + 1);
            var[ind] = stoi(line.substr(0, line.find(' ')));
        }
        
        referees.close();
    }
    else
    {
        return 6;
    }

    // Reglementations
    pitch[country1] = 0;
    var[country1] = 0;
    pitch[country2] = 0;
    var[country2] = 0;

    // Selection
    int pitch_index = wrand(pitch, 625);
    int var_index = wrand(var, 625);

    // Conversion to countries
    pitch_nationality = countries.getCountry(pitch_index);
    var_nationality = countries.getCountry(var_index);

    return 7 * (pitch_nationality.err() || var_nationality.err());
}

int Referees::decideCountries(Countries countries, const int& country1, const int& country2, Country& pitch_nationality, Country& var_nationality) const
{
    if(country1 == country2)
    {
        pitch_nationality = countries.getCountry(country1);
        var_nationality = countries.getCountry(country1);
        if(pitch_nationality.err() || var_nationality.err())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(country1 / 100 == country2 / 100)
    {
        switch(country1 / 100){
            case 1:
            {
                decideEurope(countries, country1, country2, pitch_nationality, var_nationality);
                break;
            }
            case 2:
            {
                decideAsia(countries, country1, country2, pitch_nationality, var_nationality);
                break;
            }
            case 3:
            {
                decideAfrica(countries, country1, country2, pitch_nationality, var_nationality);
                break;
            }
            case 4:
            {
                decideNorthAmerica(countries, country1, country2, pitch_nationality, var_nationality);
                break;
            }
            case 5:
            {
                decideSouthAmerica(countries, country1, country2, pitch_nationality, var_nationality);
                break;
            }
            case 6:
            {
                decideOceania(countries, country1, country2, pitch_nationality, var_nationality);
                break;
            }
            default:
            {
                return 2;
            }
        }
        return 0;
    }

    decideWorld(countries, country1, country2, pitch_nationality, var_nationality);
    return 0;
}

int Referees::getReferees(Countries countries, const int& country1, const int& country2)
{
    cout << "Select an option:" << endl;
    cout << "    E - enter referees by hand" << endl;
    cout << "    R - get random referees" << endl;
    cout << "Option: ";
    char o = option("ErRr");
    cout << endl << endl;

    if(o == 'E' || o == 'e')
    {
        this->readReferees(countries, country1, country2);
    }
    else
    {
        this->autoReferees(countries, country1, country2);
    }

    cout << endl;
    this->printReferees();

    return 0;
}

void Referees::printReferees() const
{
    cout << "Central: " << this->mainRef.getName() << " (" << this->mainRef.getNationality()->getCode() << ")" << endl;
    cout << "Assistant 1: " << this->ass1Ref.getName() << " (" << this->ass1Ref.getNationality()->getCode() << ")" << endl;
    cout << "Assistant 2: " << this->ass2Ref.getName() << " (" << this->ass2Ref.getNationality()->getCode() << ")" << endl;
    cout << "4th Official: " << this->sideRef.getName() << " (" << this->sideRef.getNationality()->getCode() << ")" << endl;
    cout << "VAR 1: " << this->var1Ref.getName() << " (" << this->var1Ref.getNationality()->getCode() << ")" << endl;
    cout << "VAR 2: " << this->var2Ref.getName() << " (" << this->var2Ref.getNationality()->getCode() << ")" << endl;
}

bool Referees::editReferees(Countries countries, const char c)
{
    switch(c)
    {
        case '1':
        {
            cout << "Central: " << this->mainRef.getName() << " (" << this->mainRef.getNationality()->getCode() << ")" << endl;
            break;
        }
    }
}