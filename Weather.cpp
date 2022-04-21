#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <ctime>
#include "Administrative_functions.h"
#include "Weather.h"
using namespace std;

int write_weather_files(Countries countries)
{
	fstream temperature, precipitation;
	temperature.open("weather/temperature.txt", ios::in);
	precipitation.open("weather/precipitation.txt", ios::app);

	int left_at = 0;
    string buffer;
    while(getline(temperature, buffer))
    {
        left_at ++;
    }
    temperature.close();
    temperature.open("weather/temperature.txt", ios::app);

    if(left_at >= 233)
    {
        cout << "Finished!" << endl;
        return 0;
    }

    double max_temp = 0.0;
    double min_temp = 0.0;
    double precip = 0.0;
    char c = '\n';
    while(c == '\n')
    {
        cout << " --- " << countries[left_at].getName() << " --- " << endl;
        temperature << countries[left_at].getIndex() << " |";
        precipitation << countries[left_at].getIndex() << " |";
        for(int i = 0; i < 12; i++)
        {
            cout << "Month " << i + 1 << endl;
            cout << "Minimum temperature: ";
            cin >> min_temp;
            getchar();
            cout << "Maximum temperature: ";
            cin >> max_temp;
            getchar();
            cout << "Precipitation: ";
            cin >> precip;
            getchar();

            temperature << setw(5) << setprecision(1) << fixed << min_temp << "-" << setw(5) << setprecision(1) << fixed << max_temp << "|";
            precipitation << setw(5) << precip << "|";
        }
        temperature << endl;
        precipitation << endl;
        cout << "Enter to continue, X to exit. ";
        c = option("\nXx");
        if(c == 'X' || c == 'x')
        {
            cout << endl;
        }
        cout << endl;
        left_at ++;
    }

    temperature.close();
    precipitation.close();

    return 0;
}

Weather::Weather()
{
    this->clock = 0;
    this->month = 0;
    this->day_night = false;
    this->cloudy = false;
    this->temperature = 0.0;
    this->precipitation = 0;
}

Weather::Weather(int clock, int month, double temp, int prec, bool dn, bool cld)
{
    this->clock = clock;
    this->month = month;
    this->temperature = temp;
    this->precipitation = prec;
    this->day_night = dn;
    this->cloudy = cld;
}

Weather::Weather(const Country& country)
{
    this->Clock();
    this->currentMonth();
    this->decideDayNight(country);
    this->computePrecipitation(country);
    this->computeTemperature(country);
}

int Weather::currentMonth()
{
    time_t now = time(0);
    tm* gmtm = gmtime(&now);
    string dt = asctime(gmtm);
    string m = dt.substr(4, 3);
    if(m == "Jan")
    {
        this->month = 1;
        return this->month;
    }
    else if(m == "Feb")
    {
        this->month = 2;
        return this->month;
    }
    else if(m == "Mar")
    {
        this->month = 3;
        return this->month;
    }
    else if(m == "Apr")
    {
        this->month = 4;
        return this->month;
    }
    else if(m == "May")
    {
        this->month = 5;
        return this->month;
    }
    else if(m == "Jun")
    {
        this->month = 6;
        return this->month;
    }
    else if(m == "Jul")
    {
        this->month = 7;
        return this->month;
    }
    else if(m == "Aug")
    {
        this->month = 8;
        return this->month;
    }
    else if(m == "Sep")
    {
        this->month = 9;
        return this->month;
    }
    else if(m == "Oct")
    {
        this->month = 10;
        return this->month;
    }
    else if(m == "Nov")
    {
        this->month = 11;
        return this->month;
    }
    else if(m == "Dec")
    {
        this->month = 12;
        return this->month;
    }
    else
    {
        this->month = 0;
        return this->month;
    }
}

int Weather::Clock()
{
    time_t now = time(0);
    tm* gmtm = gmtime(&now);
    string dt = asctime(gmtm);
    string h = dt.substr(11, 2);
    string m = dt.substr(14, 2);

    this->clock = 60 * stoi(h) + stoi(m);

    return this->clock;
}

bool Weather::decideDayNight(const Country& country)
{
    fstream sunrise_sunset;
    fstream time_zone;

    sunrise_sunset.open("weather/sunrise_sunset.txt", ios::in);
    time_zone.open("weather/timezones.txt", ios::in);

    if(!(sunrise_sunset.is_open()) || !(time_zone.is_open()))
    {
        return false;
    }

    // Compute local time
    double local_mins = 0.0;
    string timezone = "000";
    while(stoi(timezone.substr(0, 3)) != country.getIndex())
    {
        getline(time_zone, timezone);
    }
    local_mins = (double)(this->clock) + 60.0 * stod(timezone.substr(4));
    if(local_mins < 0)
    {
        local_mins = local_mins + 1440;
    }
    if(local_mins > 1440)
    {
        local_mins = local_mins - 1440;
    }

    // Get daylight interval
    string interval;
    for(int i = 0; i < this->month; i++)
    {
        getline(sunrise_sunset, interval);
    }

    // Decide
    this->day_night = (local_mins < stod(interval.substr(3, 3)) || local_mins > stod(interval.substr(7)));

    sunrise_sunset.close();
    time_zone.close();

    return this->day_night;
}

double Weather::computeTemperature(const Country& country)
{
    fstream temp;
    string t;
    string temp_min;
    string temp_max;

    temp.open("weather/temperature.txt", ios::in);
    if(!temp.is_open())
    {
        return 0.0;
    }

    // Read min and max
    double min_temp = 0.0;
    double max_temp = 0.0;
    string line = "000";
    while(stoi(line.substr(0, 3)) != country.getIndex())
    {
        getline(temp, line);
    }
    t = line.substr(12 * (this->month - 1) + 5, 11);
    temp_min = t.substr(t.find_first_not_of(' '), 5 - t.find_first_not_of(' '));
    temp_max = t.substr(t.find_first_not_of(' ', 6));
    min_temp = stod(temp_min);
    max_temp = stod(temp_max);
    temp.close();

    // Get T0
    double t0 = (min_temp + max_temp) / 2;


    // Get Sr & Ss
    fstream sunrise_sunset;
    sunrise_sunset.open("weather/sunrise_sunset.txt", ios::in);
    if(!sunrise_sunset.is_open())
    {
        return 0.0;
    }
    string srss;
    for(int i = 0; i < this->month; i++)
    {
        getline(sunrise_sunset, srss);
    }
    int Sr = stoi(srss.substr(3, 3));
    int Ss = stoi(srss.substr(7));
    sunrise_sunset.close();

    // Get final temperature
    double phi = 3.1415 / 3 - (Sr + Ss) * 3.1415 / 1440;
    this->temperature = 10 * sin((this->clock) * 3.1415 / 720.0 + phi) - 10 * sin(3.1415 / 2.0 + (Sr - Ss) * 3.1415 / 1440.0) + t0;

    return this->temperature;
}

int Weather::computePrecipitation(const Country& country)
{
    fstream precs;
    string precip = "000";

    precs.open("weather/precipitation.txt", ios::in);
    if(!precs.is_open())
    {
        return 0.0;
    }

    // Get precipitation chance
    while(stoi(precip.substr(0, 3)) != country.getIndex())
    {
        getline(precs, precip);
    }
    precip = precip.substr(6 * (this->month - 1) + 5, 5);
    precip = precip.substr(precip.find_first_not_of(' '));
    double precip_chance = stoi(precip);

    // Does it rain/snow?
    bool does_precip = (rand() % 501) < precip_chance;

    // How heavy is the precipitation?
    if(does_precip)
    {
        int hvy[] = { 5, 12, 18, 25, 18, 12, 5, 3, 1, 1};
        this->precipitation = 1 + wrand(hvy, 10);
        this->cloudy = true;
    }
    else
    {
        this->precipitation = 0;
        this->cloudy = (rand() % 501) < precip_chance;
    }
    
    precs.close();

    return this->precipitation;
}

string Weather::describeWeather() const
{
    string description;
    if(this->day_night)
    {
        if(this->cloudy)
        {
            if(this->precipitation)
            {
                if(this->temperature < 0.0)
                {
                    string snow[] = { "A few snowflakes", "Light snow", "Light snow", "Light snow", "Sleet", "Heavy snow", "Heavy snow", "Heavy snow", "Snowstorm", "Blizzard"};
                    description = snow[this->precipitation];
                }
                else
                {
                    string rain[] = { "A drizzle", "Gentle rain", "Light rain", "A shower", "Constant rain", "Steady rain", "Heavy rain", "Pouring rain", "A downpour", "A rainstorm"};
                    description = rain[this->precipitation];
                }
            }
            else
            {
                description = "Covered sky";
            }
        }
        else
        {
            description = "Clear sky";
        }
    }
    else
    {
        if(this->cloudy)
        {
            if(this->precipitation)
            {
                if(this->temperature < 0.0)
                {
                    string snow[] = { "A few snowflakes", "Light snow", "Light snow", "Light snow", "Sleet", "Heavy snow", "Heavy snow", "Heavy snow", "Snowstorm", "Blizzard"};
                    description = snow[this->precipitation];
                }
                else
                {
                    string rain[] = { "A drizzle", "Gentle rain", "Light rain", "A shower", "Constant rain", "Steady rain", "Heavy rain", "Pouring rain", "A downpour", "A rainstorm"};
                    description = rain[this->precipitation];
                }
            }
            else
            {
                description = "Cloudy";
            }
        }
        else
        {
            description = "Sunny";
        }
    }

    description += " with ";

    if(this->temperature < -15.0)
    {
        description += "frigid temperatures";
    }
    else
    {
        if(this->temperature < -10.0)
        {
            description += "freezing temperatures";
        }
        else
        {
            if(this->temperature < -5.0)
            {
                description += "cold temperatures";
            }
            else
            {
                if(this->temperature < 0.0)
                {
                    description += "sub-zero temperatures";
                }
                else
                {
                    if(this->temperature < 4.0)
                    {
                        description += "chilly temperatures";
                    }
                    else
                    {
                        if(this->temperature < 8.0)
                        {
                            description += "brisk temperatures";
                        }
                        else
                        {
                            if(this->temperature < 13.0)
                            {
                                description += "cool temperatures";
                            }
                            else
                            {
                                if(this->temperature < 18.0)
                                {
                                    description += "mild temperatures";
                                }
                                else
                                {
                                    if(this->temperature < 25.0)
                                    {
                                        description += "perfect temperatures";
                                    }
                                    else
                                    {
                                        if(this->temperature < 32.0)
                                        {
                                            description += "warm temperatures";
                                        }
                                        else
                                        {
                                            if(this->temperature < 38.0)
                                            {
                                                description += "hot temperatures";
                                            }
                                            else
                                            {
                                                if(this->temperature < 45.0)
                                                {
                                                    description += "roasting temperatures";
                                                }
                                                else
                                                {
                                                    description += "blazing temperatures";
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return description;
}

void Weather::print() const
{
    cout << "---WEATHER---" << endl;
    cout << "Description: " << this->describeWeather() << endl;
    cout << "Temperature: " << setprecision(1) << fixed << this->getTemperature() << "*C" << endl;
    cout << "Cloudy: " << (this->isCloudy() ? "Yes" : "No") << endl;
    cout << "Level of precipitation (0 - 10): " << this->getPrecipitation() << endl;
    cout << "Clock value (minutes after UTC midnight): " << this->getClock() << endl;
    string m[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    cout << "Month: " << m[this->getMonth() - 1] << endl;
}