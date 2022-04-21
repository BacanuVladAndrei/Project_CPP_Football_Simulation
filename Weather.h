#include <iostream>
#include "Country.h"
#pragma once
using namespace std;

int write_weather_files(Countries countries);

class Weather {
    protected:
        int clock;
        int month;
        double temperature;
        int precipitation;
        bool day_night;
        bool cloudy;

    public:
        Weather();
        Weather(int, int, double, int, bool, bool);
        Weather(const Country&);
        ~Weather() {};

        inline int getClock() const { return this->clock; };
        inline int getMonth() const { return this->month; };
        inline double getTemperature() const { return this->temperature; };
        inline int getPrecipitation() const { return this->precipitation; };
        inline bool isDay() const { return !(this->day_night); };
        inline bool isNight() const { return this->day_night; };
        inline bool isCloudy() const { return this->cloudy; };

        int currentMonth();
        int Clock();
        bool decideDayNight(const Country&);
        double computeTemperature(const Country&);
        int computePrecipitation(const Country&);
        string describeWeather() const;
        void print() const;
};