#pragma once

char* replace_chars(const char* s, const char good_char, const char* bad_chars);

template<typename type>
type* Resize(type*& old,long int length,long int resize_to)
{
    type* new_ptr;
    new_ptr = new type[ resize_to ];
    long int least = ( length < resize_to ) ? length : resize_to;
    for(long int i = 0;i < least ; ++i)
        new_ptr [i] = old[i];
    delete [] old;
    old = nullptr;
    return new_ptr;
}

int get_int_secure(int greater_than_or_equal_to, int lower_than_or_equal_to, const char *range_error, const char *no_number_error);

char getche();

char option(const char*, const char* = NULL);

int wrand(int *chances, int count);

template<typename type>
void swapelem(type& elem1, type& elem2)
{
    type aux;
    aux = elem1;
    elem1 = elem2;
    elem2 = aux;
}

template<typename type>
void sort(type* array, int count, bool ordered(type, type))
{
    int sch = 1;
    while(sch)
    {
        sch = 0;
        for(int i = 0; i < count - 1; i++)
        {
            if(!ordered(array[i], array[i + 1]))
            {
                swapelem<type>(array[i], array[i + 1]);
                sch = 1;
            }
        }
    }
}

bool happen(int fav, int pos);

char getch();

char pasche();

char getchen();

bool is_digit(char);

void fillSpaces(int);