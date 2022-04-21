#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <vector>
#include <limits.h>
#include <termios.h>
using namespace std;

char* replace_chars(const char* s, const char good_char, const char* bad_chars)
{
    string str = s;
    char *good = new char[2];
    good[0] = good_char;
    good[1] = '\0';
    for(int i = 0; i < str.length(); i++)
    {
        if(strchr(bad_chars, str[i]))
        {
            str.replace(i, 1, good);
        }
    }

    char *str_ret = new char[str.length() + 1];
    strcpy(str_ret, str.c_str());

    return str_ret;
}

int get_int_secure(int greater_than_or_equal_to, int lower_than_or_equal_to, const char *range_error, const char *no_number_error)
{
	size_t chestie;
	char *line;
	char *line_after;
	int i;
	int negative;
	int included=0;
	int number=0;
	int mult;
	size_t size;
	int j;

	if(greater_than_or_equal_to>=lower_than_or_equal_to)
	{
		printf("Error! Range incompatible!\n");
		return INT_MIN;
	}
	do{
		number=0;
		mult=1;
		size=0;
		line=NULL;
		line_after=NULL;
		getline(&line, &chestie, stdin);
		if(line[0]=='-')
		{
			negative=1;
			//printf("Negative number\n");
			i=1;
		}
		else
		{
			negative=0;
			//printf("Positive number\n");
			i=0;
		}
		while(1)
		{
			if(line[i]<48 || line[i]>57)
			{
				line_after=(char*)calloc(strlen(line)-i+1, sizeof(char));
				for(j=0;j<strlen(line)-i;j++)
				{
					line_after[j]=line[i+j+1];
				}
				//printf("shit: %s\n", line_after);
				line[i]='\0';
				free(line_after);
				break;
			}
			i++;
		}
		size=strlen(line);
		if(size>8)
		{
			if(negative)
			{
				printf("Number too small!\n");
				goto x;
			}
			else
			{
				printf("Number too large!\n");
				goto x;
			}
		}
		if(line[0]=='-')
		{
			size--;
		}
		if(size==0)
		{
			included=0;
			if(no_number_error==NULL)
			{
				printf("Error! No number found!\n");
			}
			else
			{
				printf("%s", no_number_error);
			}
			goto x;
		}
		for(i=0;i<size;i++)
		{
			mult=10*mult;
		}
		if(negative)
		{
			for(i=1;i<size+1;i++)
			{
				mult=mult/10;
				number=number+mult*(line[i]-48);
			}
		}
		else
		{
			for(i=0;i<size;i++)
			{
				mult=mult/10;
				number=number+mult*(line[i]-48);
			}
		}
		
		//printf("Number: %d\n", number);
		if(negative)
		{
			number=0-number;
		}
		if(number<=lower_than_or_equal_to && number>=greater_than_or_equal_to)
		{
			included=1;
		}
		else
		{
			if(range_error==NULL)
			{
				printf("Error! Number not between %d and %d!\n", greater_than_or_equal_to, lower_than_or_equal_to);
			}
			else
			{
				printf("%s", range_error);
			}
		}
		x:
		free(line);
	}while(!included);
	
	return number;
}

int random(int limit)
{
	return rand() % limit;
}

int randbetween(int bottom, int top)
{
	return bottom + rand() % (top - bottom + 1);
}

char getche()
{
	char c;
	struct termios t1, t2;

	tcgetattr(0, &t1);

	t2 = t1;

	t2.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(0, TCSAFLUSH, &t2);

	c = getchar();
	putchar(c);

	tcsetattr(0, TCSAFLUSH, &t1);

	return c;
}

char getchen()
{
	char c;
	struct termios t1, t2;

	tcgetattr(0, &t1);

	t2 = t1;

	t2.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(0, TCSAFLUSH, &t2);

	c = getchar();
	if(c != '\n')
		putchar(c);

	tcsetattr(0, TCSAFLUSH, &t1);

	return c;
}

char option(const char* options, const char* error_message)
{
	char o = '\0';
	if(error_message == NULL)
	{
		do{
			o = getche();
		}while(strchr(options, o) == NULL);
	}
	else
	{
		do{
			o = getche();
			if(strchr(options, o) == NULL)
			{
				cout << error_message;
			}
		}while(strchr(options, o) == NULL);
	}

	return o;
}

int wrand(int *chances, int count)
{
    if(count<=0)
    {
        printf("Invalid second argument of 'wrand'!\n");
        return count;
    }
    int sum=0;
    int i;
    for(i=0;i<count;i++)
    {
        if(chances[i]>0)
            sum+=chances[i];
    }
    if(!sum)
    {
        printf("No chance of an event happening!\n");
        return count;
    }
    int r=rand()%sum;
    sum=0;
    for(i=0;i<count;i++)
    {
        if(chances[i]>0)
            sum+=chances[i];
        if(r<sum)
        {
            return i;
            break;
        }
    }
    return 0;
}

bool happen(int fav, int pos)
{
	return (rand() % pos) < fav;
}

char getch()
{
	char c;
	struct termios old, n;

	tcgetattr(0, &old);

	n = old;

	n.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(0, TCSAFLUSH, &n);

	c = getchar();

	tcsetattr(0, TCSAFLUSH, &old);

	return c;
}

char pasche()
{
	char c;
	struct termios old, n;

	tcgetattr(0, &old);

	n = old;

	n.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(0, TCSAFLUSH, &n);

	c = getchar();
	if(c!='\n')
		putchar('*');

	tcsetattr(0, TCSAFLUSH, &old);

	return c;
}

bool is_digit(char c)
{
	return (c > 47 && c < 58);
}

void fillSpaces(int nr)
{
	for(int i = 0; i < nr; i ++)
	{
		cout << " ";
	}
}