#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Country.h"
#pragma once
using namespace std;

struct TicketPrice {
    double low;
    double high;
};

class Stadium {
    protected:
        string name;
        string location;
        Country *country;
        int cap;
        int att;
        bool type; // 1 - home, 0 - neutral
        char cl;
        TicketPrice pricing;
        char code[10];

    public:
        Stadium();
        Stadium(string, string, Country*, const int&, const int&, bool&, const double&, const double&, const char*);
        Stadium(const Stadium&);
        Stadium& operator=(const Stadium&);
        friend ostream& operator<<(ostream&, const Stadium&);
        ~Stadium();

        char* makeCode(const char*);
        char makeClass();
        void setStadium(Countries, const char*);
        string getName() const;
        string getLocation() const;
        Country* getCountry() const;
        int getCapacity() const;
        int getAttendance() const;
        bool getType() const;
        char getClass() const;
        char* getCode() const;
        double getLowestPrice() const;
        double getHighestPrice() const;
        int getHomesupport() const;

        int computeTicketPrice(const double&, const double& = 0);
        int getTicketPrice(const double&, const double& = 0);

        int read(Countries, const double&, const double&);
};