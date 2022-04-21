#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "Administrative_functions.h"
#include "Country.h"
#include "Referee.h"
#include "Stadium.h"
#include "Formation.h"
#include "Player.h"
#include "Goalkeeper.h"
#include "Defender.h"
#include "Midfielder.h"
#include "Forward.h"
#include "Goal.h"
#include "Team.h"
#include "Penalty.h"
#include "Match.h"
#include "Betting_Application.h"
#include "Referees.h"
#include "Weather.h"
#include <time.h>
using namespace std;

int RegularMatch(Countries);

int main()
{
    srand(time(0));
    Countries countries;

    RegularMatch(countries);

    return 0;
}

int RegularMatch(Countries countries)
{
    Match current;
    Stadium stadium;
    Team home;
    Team away;
    Referees referees;

    cout << "HOME TEAM" << endl;
    home.read(countries, false);
    cout << endl;

    cout << "AWAY TEAM" << endl;
    away.read(countries, true);
    cout << endl;

    cout << "STADIUM" << endl;
    stadium.read(countries, home.getRatingTotal(), away.getRatingTotal());
    cout << endl;

    Weather weather(*(stadium.getCountry()));

    cout << "REFEREES" << endl;
    referees.getReferees(countries, home.getNationality()->getIndex(), away.getNationality()->getIndex());
    cout << endl;

    current.prepareMatch(&home, &away, &stadium, &referees, &weather);
    
    char edit;
    do{
        current.preview();
        cout << "Press E to edit match details! " << endl;
        edit = getche();
        if(edit == 'E' || edit == 'e')
        {
            current.editMatch(countries);
        }
    }while(edit == 'E' || edit == 'e');
    


    current.match();

    return 0;
}