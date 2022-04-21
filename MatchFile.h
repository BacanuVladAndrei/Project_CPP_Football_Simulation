#include <iostream>
#include <string>
#include <fstream>
#include "Referees.h"
#include "Stadium.h"
#include "Weather.h"
#include "Team.h"
using namespace std;

class MatchFile {
    protected:
        fstream stream;
        string stream_name;

    public:
        MatchFile();
        MatchFile(const string&);
        MatchFile(const string&, const char);
        ~MatchFile() {};

        // Administrative functions
        string makeName(string, string /*current date and time*/); // Home team name, away team name, current date and time
        string getName() const;
        bool open(const char = 'w');
        bool open(const string&, const char = 'w');
        bool is_open() const;
        void write(const string&);
        bool close();

        // Filling functions
        bool writeTableofContents();
        bool writeReferees(const Referees&);
        bool writeStadium(const Stadium&);
        bool writeWeather(const Weather&);
        bool writeTeamOverview(const Team&);
};