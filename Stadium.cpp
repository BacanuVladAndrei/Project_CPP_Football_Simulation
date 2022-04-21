#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <math.h>
#include "Stadium.h"
#include "Country.h"
#include "Administrative_functions.h"
using namespace std;

Country* countrySuggestions(Country*, const char*, int&, const double&);

Stadium* Resize(Stadium*& old,long int length,long int resize_to)
{
    Stadium* new_ptr;
    new_ptr = new Stadium[ resize_to ];
    long int least = ( length < resize_to ) ? length : resize_to;
    for(long int i = 0;i < least ; ++i)
        new_ptr [i] = old[i];
    delete [] old;
    old = nullptr;
    return new_ptr;
}

Stadium::Stadium()
{
    country = NULL;
    cap = 0;
    att = 0;
    type = false;
    cl = '\0';
    strcpy(code, "000000000\0");
}

Stadium::Stadium(string name, string location, Country *country, const int &cap, const int &att, bool &type, const double& lowest_price, const double& highest_price, const char *unique_code)
{
    this->name = name;
    this->location = location;
    this->country = country;
    this->cap = cap;
    this->att = att;
    this->type = type;
    this->pricing.low = lowest_price;
    this->pricing.high = highest_price;
    this->makeClass();
    this->makeCode(unique_code);
}

Stadium::Stadium(const Stadium &stad)
{
    this->name = stad.name;
    this->location = stad.location;
    this->country = stad.country;
    this->cap = stad.cap;
    this->att = stad.att;
    this->type = stad.type;
    this->cl = stad.cl;
    this->pricing = stad.pricing;
    strncpy(this->code, stad.code, 10);
}

Stadium& Stadium::operator=(const Stadium &stad)
{
    this->name = stad.name;
    this->location = stad.location;
    this->country = stad.country;
    this->cap = stad.cap;
    this->att = stad.att;
    this->type = stad.type;
    this->cl = stad.cl;
    this->pricing = stad.pricing;
    strncpy(this->code, stad.code, 10);

    return *this;
}

ostream& operator<<(ostream &devo, const Stadium &stad)
{
    cout << "Name: " << stad.name << endl;
    cout << "Location: " << stad.location << ", " << stad.country->getName() << endl;
    cout << "Capacity: " << stad.cap << endl;
    cout << "Class: " << stad.cl << endl;
    cout << "Code: " << stad.code << endl;
    cout << "Ticket Price Range: " << stad.pricing.low << "$ - " << stad.pricing.high << "$" << endl;

    return devo;
}

Stadium::~Stadium() {}

char* Stadium::makeCode(const char* unique_code)
{
    const char *ctr_cd = this->country->getCode().c_str();
    for(int i=0; i<3; i++)
    {
        this->code[i] = ctr_cd[i];
    }
    this->code[3] = '-';
    this->code[4] = this->cl;
    this->code[5] = '-';
    for(int i=0; i<3; i++)
    {
        this->code[i + 6] = unique_code[i];
    }
    this->code[9] = '\0';

    return this->code;
}

char Stadium::makeClass()
{
    char c;
    if(this->cap > 59999)
    {
        c = 'A';
    }
    else
        if(this->cap > 49999)
        {
            c = 'B';
        }
        else
            if(this->cap > 34999)
            {
                c = 'C';
            }
            else
                if(this->cap > 19999)
                {
                    c = 'D';
                }
                else
                    if(this->cap > 9999)
                    {
                        c = 'E';
                    }
                    else
                        if(this->cap > 4999)
                        {
                            c = 'F';
                        }
                        else
                            if(this->cap > 999)
                            {
                                c = 'G';
                            }
                            else
                            {
                                c = 'L';
                            }
    this->cl = c;
    return c;
}

void Stadium::setStadium(Countries countries, const char* l)
{
    // Fill code ...
}

string Stadium::getName() const
{
    return this->name;
}

string Stadium::getLocation() const
{
    return this->location;
}

Country* Stadium::getCountry() const
{
    return this->country;
}

int Stadium::getCapacity() const
{
    return this->cap;
}

int Stadium::getAttendance() const
{
    return this->att;
}

bool Stadium::getType() const
{
    return this->type;
}

char Stadium::getClass() const
{
    return this->cl;
}

char* Stadium::getCode() const
{
    char* cd = new char[10];
    strncpy(cd, this->code, 10);
    return cd;
}

double Stadium::getLowestPrice() const
{
    return this->pricing.low;
}

double Stadium::getHighestPrice() const
{
    return this->pricing.high;
}

// Stadium* getStadiums(Country* countries, int &count, char* file_name)
// {
//     string name = "stadiums/";
//     name += file_name;
//     name += ".txt";
//     fstream stadiums;
//     stadiums.open(name, ios::in);
//     Stadium *stads = NULL;
//     count = 0;
//     int success = 0;
//     if(stadiums.is_open())
//     {
//         string line;
//         while(getline(stadiums, line))
//         {
//             stads = Resize(stads, count, count + 1);
//             stads[count].setStadium(countries, line.c_str());
//             if(getStadiumadd(stads, count, stads[count].name) != NULL)
//             {
//                 cout << "Error! Duplicate stadium on line " << count + 1 << endl;
//                 delete[] stads;
//                 return NULL;
//             }

//             stads[count].getFilename();
//             // success = stads[count].makeFile();
//             // if(!success)
//             // {
//             //     cout << "Could not make file on line " << count << endl;
//             //     exit(1);
//             // }
//             count++;
//         }
//         stadiums.close();
//         return stads;
//     }
//     else
//     {
//         return NULL;
//     }
// }

int Stadium::getHomesupport() const
{
    return 5 * (this->type) * (this->att) / (this->cap);
}

char* rand_char(int n)
{
    char *code = new char[n + 1];
    for(int i=0; i<n; i++)
    {
        code[i] = 65 + rand() % 26;
    }
    code[n] = '\0';

    return code;
}

int Stadium::computeTicketPrice(const double& rating_average, const double& rating_difference)
{
    double real_rat_avg = rating_average > 100 ? 100 : rating_average;
    real_rat_avg = real_rat_avg < 1 ? 1 : real_rat_avg;
    double real_rat_diff = real_rat_avg + rating_difference / 2 > 100 ? 2 * (100 - real_rat_avg) : rating_difference;
    double average_price = (50 / (25 + real_rat_diff)) * exp((real_rat_avg / 5.5) - 12) + 1;
    this->pricing.low = average_price / 2;
    this->pricing.high = 3 * average_price / 2;

    return average_price;
}

int Stadium::getTicketPrice(const double& rating_average, const double& rating_difference)
{
    cout << "Price Range (low - high): ";
    string low_price;
    string high_price;
    char c = '\0';

    // Low Price
    while(low_price.length() < 5 && c != '\n')
    {
        c = getchen();
        if(c == '\n')
        {
            if(low_price.length() < 1)
            {
                c = '\0';
            }
        }
        else
        {
            if(c < 58 && c > 47)
            {
                low_price += c;
            }
        }
    }

    cout << " - ";
    // Convert low price
    this->pricing.low = stod(low_price);

    c = '\0';

    // High Price
    while(high_price.length() < 5 && c != '\n')
    {
        c = getchen();
        if(c == '\n')
        {
            if(high_price.length() < 1)
            {
                c = '\0';
            }
        }
        else
        {
            if(c < 58 && c > 47)
            {
                high_price += c;
            }
        }
    }

    cout << endl;
    // Convert high price
    this->pricing.high = stod(high_price);

    if(this->pricing.high < this->pricing.low)
    {
        swap<double>(this->pricing.low, this->pricing.high);
    }
    
    if(this->pricing.high == 0.0)
    {
        this->computeTicketPrice(rating_average, rating_difference);
        return 1;
    }
    else
    {
        return 0;
    }
}

int Stadium::read(Countries countries, const double& rating_home, const double& rating_away)
{
    // Name
    do{
        cout << "Name: ";
        getline(cin, this->name);
        if(this->name.length() < 4)
        {
            cout << "The stadium's name must be at least 4 characters long!" << endl;
        }
    }while(this->name.length() < 4);

    // Location
    do{
        cout << "Location: ";
        getline(cin, this->location);
        if(this->location.length() < 1)
        {
            cout << "Invalid location!" << endl;
        }
    }while(this->location.length() < 1);

    // Country
    string nation;
    do{
        cout << "Country: ";
        getline(cin, nation);
        this->country = countries.getCountryAdd(nation);
        if(this->country == NULL)
        {
            cout << "Country not found!" << endl;
        }
    }while(this->country == NULL);

    // Capacity
    string line_read;
    string capacity;
    do{
        cout << "Capacity: ";
        getline(cin, line_read);
        capacity.clear();
        for(int i = 0; i < line_read.length(); i++)
        {
            if(line_read[i] > 47 && line_read[i] < 58)
            {
                capacity += line_read[i];
            }
        }
        if(capacity.length() > 6)
        {
            cout << "Capacity of the stadium must be at most 999,999 seats!" << endl;
        }
        if(capacity.length() == 0)
        {
            cout << "Invalid capacity!" << endl;
        }
        if(capacity.length() && capacity.length() < 7)
        {
            this->cap = stoi(capacity);
            break;
        }
    }while(1);

    // Ticket Pricing
    this->getTicketPrice((rating_home + rating_away) / 2.0, abs(rating_home - rating_away));

    // Class
    this->makeClass();

    // Code
    char* rand_code = rand_char(3);
    this->makeCode(rand_code);

    // Type
    cout << "Type (Home/Neutral): ";
    char o = option("HhNn");
    this->type = (o == 'H' || o == 'h');
    cout << endl;

    return 0;
}