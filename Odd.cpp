#include <iostream>
#include <iomanip>
#include <string>
#include "Betting_Application.h"
using namespace std;

Odd::Odd()
{
    this->odd = 0.0;
}

Odd::Odd(double odd)
{
    this->odd = odd;
}

Odd::Odd(const Odd& o)
{
    this->odd = o.odd;
}

Odd& Odd::operator=(const Odd& o)
{
    this->odd = o.odd;
    return *this;
}

void Odd::set(const double new_odd)
{
    this->odd = new_odd;
}

double Odd::get() const
{
    return this->odd;
}

double Odd::chance() const
{
    return (1.0 / this->odd);
}

istream& operator>>(istream& devi, Odd& o)
{
    string line;
    getline(devi, line);
    o.odd = stod(line);
    return devi;
}

ostream& operator<<(ostream& devo, const Odd& o)
{
    return (o.odd < 1000.0) ? (devo << o.odd) : (devo << "-");
}

fstream& operator<<(fstream& stro, const Odd& o)
{
    if(stro.is_open() && o.odd < 1000.0)
    {
        stro << o.odd;
    }

    return stro;
}

void Odd::print(int column_width, int precision) const
{
    if(this->odd > 999.9999999999999)
    {
        for(int i = 0; i < column_width / 2; i++)
        {
            cout << " ";
        }
        cout << "-";
        for(int i = 0; i < column_width / 2 - 1; i++)
        {
            cout << " ";
        }
        return;
    }
    cout << setw(column_width) << setprecision(precision) << fixed << this->odd;
}

fstream& Odd::print(fstream& stro, int column_width, int precision) const
{
    if(column_width < 0 || precision < 0 || !stro.is_open())
    {
        return stro;
    }

    if(this->odd >= 1000.0)
    {
        for(int i = 0; i < column_width / 2; i++)
        {
            stro << " ";
        }
        stro << "-";
        for(int i = (column_width / 2) + 1; i < column_width; i++)
        {
            stro << " ";
        }
    }
    else
    {
        int places_necessary = 0;
        if(this->odd >= 100.0)
        {
            places_necessary = 3;
        }
        else
        {
            if(this->odd >= 10.0)
            {
                places_necessary = 2;
            }
            else
            {
                places_necessary = 1;
            }
        }
        if(column_width < places_necessary)
        {
            column_width = places_necessary;
        }
        if(precision > column_width - places_necessary - 1)
        {
            precision = column_width - places_necessary - 1;
        }
        if(column_width < places_necessary + 2)
        {
            stro << setw(column_width);
            stro << (int)(this->odd);
        }
        else
        {
            stro << setw(column_width);
            stro << setprecision(precision);
            stro << fixed;
            stro << this->odd;
        }
    }

    return stro;
}

Odd operator+(const Odd& odd1, const Odd& odd2)
{
    return Odd(1.0 / (odd1.chance() + odd2.chance()));
}

Odd operator-(const Odd& odd1, const Odd& odd2)
{
    return Odd(1.0 / (odd1.chance() - odd2.chance()));
}

Odd operator*(const Odd& odd1, const Odd& odd2)
{
    return Odd(1.0 / (odd1.chance() * odd2.chance()));
}

Odd operator/(const Odd& odd1, const Odd& odd2)
{
    return Odd(1.0 / (odd1.chance() / odd2.chance()));
}

Odd& Odd::operator+=(const Odd& o)
{
    (*this) = (*this) + o;
    return *this;
}

Odd& Odd::operator-=(const Odd& o)
{
    (*this) = (*this) - o;
    return *this;
}

Odd& Odd::operator*=(const Odd& o)
{
    (*this) = (*this) * o;
    return *this;
}

Odd& Odd::operator/=(const Odd& o)
{
    (*this) = (*this) / o;
    return *this;
}

bool operator==(const Odd& odd1, const Odd& odd2)
{
    return (odd1.odd == odd2.odd);
}

bool operator!=(const Odd& odd1, const Odd& odd2)
{
    return !(odd1 == odd2);
}

bool operator<(const Odd& odd1, const Odd& odd2)
{
    return (odd1.odd < odd2.odd);
}

bool operator>(const Odd& odd1, const Odd& odd2)
{
    return (odd1.odd > odd2.odd);
}

bool operator<=(const Odd& odd1, const Odd& odd2)
{
    return (odd1 == odd2 || odd1 < odd2);
}

bool operator>=(const Odd& odd1, const Odd& odd2)
{
    return (odd1 == odd2 || odd1 > odd2);
}

