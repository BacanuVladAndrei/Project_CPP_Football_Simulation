#include <iostream>
#include <string>
#include <fstream>
#include "Event.h"
#include "Administrative_functions.h"
using namespace std;

Event::Event()
{
    this->half = 0;
    this->min = 0;
    this->team = 0;
}

Event::Event(int half, int min, bool team)
{
    this->half = half;
    this->min = min;
    this->team = team;
}

Event** Event::queueEvent(Event** events, int& count)
{
    if(this == NULL)
    {
        return events;
    }
    events = Resize<Event*>(events, count, count + 1);
    events[count] = this;

    return events;
}

bool Event::operator<(const Event& event)
{
    if(this->half != event.half)
    {
        return this->half < event.half;
    }
    else
    {
        return this->min < event.min;
    }
}

void transferEvent(Event*** dest, int& count_dest, Event*** src, int& count_src)
{
    Event* trans = (*src)[count_src - 1];
    if(count_src == 1)
    {
        delete[] (*src);
        (*src) = NULL;
        count_src = 0;
    }
    else
    {
        (*src) = Resize<Event*>(*src, count_src, count_src - 1);
        count_src--;
    }
    
    (*dest) = Resize<Event*>(*dest, count_dest, count_dest + 1);
    (*dest)[count_dest] = trans;
    count_dest++;
}

bool itHappens(int expected, int so_far, int mins_left)
{
    /* if(mins_left < 1)
    {
        return 0;
    }
    expected = so_far >= expected ? so_far + 1 : expected;
    mins_left = mins_left < 3 ? 3 : mins_left;
    return (rand() % mins_left < (expected - so_far)); */

    return (rand() % 90 < expected);
}

bool Event::Who(const Team& home, const Team& away)
{
    return 0;
}

void Event::printMinute()
{
    switch(this->half) {
        case 1:
        {
            if(min < 46)
            {
                cout << this->min;
            }
            else
            {
                cout << "45 + " << this->min - 45;
            }
            break;
        }
        case 2:
        {
            if(min < 46)
            {
                cout << this->min + 45;
            }
            else
            {
                cout << "90 + " << this->min - 45;
            }
            break;
        }
        case 3:
        {
            if(min < 16)
            {
                cout << this->min + 90;
            }
            else
            {
                cout << "105 + " << this->min - 15;
            }
            break;
        }
        case 4:
        {
            if(min < 16)
            {
                cout << this->min + 105;
            }
            else
            {
                cout << "120 + " << this->min - 15;
            }
            break;
        }
        default:
        {
            cout << 0;
            break;
        }
    }
}