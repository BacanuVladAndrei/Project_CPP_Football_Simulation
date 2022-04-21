#include <iostream>
#include <string>
#include <vector>
#pragma once
using namespace std;

class Country {
    protected:
        int index;
        string code;
        string name;
        vector<string> alternative_names;

    public:
        Country();
        Country(const int&, const string&, const string&, const vector<string>&);
        Country(const Country&);
        Country& operator=(const Country&);
        friend ostream& operator<<(ostream&, const Country&);
        ~Country();

        const string altName(const int&) const;

        // Logical operators
        friend bool operator==(const Country&, const Country&);
        friend bool operator!=(const Country&, const Country&);
        friend bool operator>(const Country&, const Country&);
        friend bool operator<(const Country&, const Country&);
        friend bool operator>=(const Country&, const Country&);
        friend bool operator<=(const Country&, const Country&);

        int setCountry(string);
        int getIndex() const;
        string getCode() const;
        string getName() const;
        int getContinent() const;
        bool err() const;

        bool refersTo(string) const;

        friend Country* getCountries();
        friend const Country getCountry(Country*, const int&);
        friend const Country getCountry(Country*, string);
        friend Country* getCountryadd(Country*, const int&);
        friend Country* getCountryadd(Country*, string);
        friend Country* countrySuggestions(Country*, string, int&, const double&);
};

class Countries {
    protected:
        vector<Country> countries;

    public:
        Countries();
        ~Countries() {};

        const Country& operator[](const int&);

        inline int number() const { return 233; };
        Country getCountry(string) const; 
        Country getCountry(const int&) const;
        Country* getCountryAdd(string) const; 
        Country* getCountryAdd(const int&) const;
        vector<Country> suggestions(string, const int&, const double&) const;
        Country getCountry(const char* = NULL, bool = false, const char* = NULL);
};

int presentSuggestions(const vector<Country>&);

class CountrySim {
    protected:
        const Country* country;
        double similarity;
    public:
        void set(const Country* ctr, double sim)
        {
            this->country = ctr;
            this->similarity = sim;
        }

        Country getCountry()
        {
            return (*country);
        }

        double getSim()
        {
            return this->similarity;
        }

        friend bool operator<(const CountrySim& c1, const CountrySim& c2)
        {
            return c1.similarity < c2.similarity;
        }
};