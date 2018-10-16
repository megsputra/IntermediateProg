// Assignment 7 Solution 3/2017

#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

const double DaysPerYear = 365.25f;

class Date
{
    unsigned month, day, year;
public:
    // assume any two-digit year reference < 17 refers to years between 2000-2016
    // assume any two-digit year reference > 16 refers to years between 1917-1999
    Date ();
    Date(unsigned, unsigned, unsigned);
    void increment(void);
    bool isGreaterThan(const Date&) const;
    bool isEqualTo(const Date&) const;
    void display() const;
    void letTimePass();
};

Date getBirthday();

class Human
{
    string  name;
    Date	birthday;
    bool	alive;
public:
    Human(const string& n, const Date& b);
    string get_name() const
    {
        return name;
    }

    const Date& get_birthday() const
    {
        return birthday;
    }

    bool is_alive() const
    {
        return alive;
    }

    unsigned short age() const;
    double decimal_age() const;
    void die()
    {
        alive = false;
    }
    void display() const;
};

class Population
{
    Human**	people;
    unsigned size;
    void determine_oldest() const;
public:
    Population(int size);
    ~Population();
    void display() const;
    void examinePopulation();
    unsigned getNumberLiving() const;
};

float roll_the_dice(unsigned short age);

Date TODAY;
unsigned DaysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const string NAMES[] =
{
    "Joshua","Kyle","Yuxi","Anthony","Michael","Samuel","Karlen","Seyed Nima",
    "Mega","Tamuz","Ali","Ting","Khang","Quang","Rafael","David",
    "Shenghao","Shealtiel","Johnny","Coriena","Minh Quan","Hong Yip","Robert",
    "Yingqi","Manxin","Shun","Dekel","Yash","Shuo","Shiyu","Jiayi",
    "Tristan","Carlo","Jason","Thao","Joe"
};

int main()
{
    const int OriginalPopulationSize = 36;

    srand(time(0));
    Population World(OriginalPopulationSize);
    World.display();

    // let time pass until half of the world's Population dies
    do
    {
        TODAY.letTimePass();
        World.examinePopulation();
    }
    while (World.getNumberLiving() > OriginalPopulationSize / 2);

    World.display();
}



// Creates today's date
Date::Date()
{
    time_t timer = time(NULL);
    tm* NOW = localtime(&timer);
    month = NOW->tm_mon + 1;	// note  NOW->tm mon is current month% -1
    day = NOW->tm_mday;
    year = NOW->tm_year + 1900;
}

Date::Date(unsigned m, unsigned d, unsigned y)
: month(m), day(d),year(y)
{
    if (y < 100) year += (year < 17) ? 2000 : 1900;
}

void Date::increment(void)
{
    day++;

    // Leap year correction
    if (year%4 == 0) DaysPerMonth[2] = 29;
    else if (year%400 == 0) DaysPerMonth[2] = 29;
    else if (year%100 == 0) DaysPerMonth[2] = 28;
    else DaysPerMonth[2] = 28;

    if (day > DaysPerMonth[month])
    {
        day = 1;
        month++;
    }
    if (month > 12)
    {
        month = 1;
        year++;
    }
}

bool Date::isGreaterThan(const Date& d) const
{
    return 10000*year+100*month+day>10000*d.year+100*d.month+d.day;
}

bool Date::isEqualTo(const Date& d) const
{
    return 10000*year+100*month+day==10000*d.year+100*d.month+d.day;
}

void Date::display() const
{
    cout << setfill('0');
    cout << setw(2) << month << '/' << setw(2) << day << '/' << setw(2) << year%100;
    cout << setfill(' ');
}

void Date::letTimePass()
{
    int random = rand() % 365+1;
    int i;
    for (i = 0; i < random; i++) increment();
}

// returns the number of days between d1 and d2 (same as d1 - d2)
int difference_between_2_Dates(Date d1,Date d2)
{
    int days = 0;
    if (d1.isGreaterThan(d2))
    {
        do
        {
            days++;
            d2.increment();
        }
        while (!d1.isEqualTo(d2));
        return days;
    }
    else
    {
        do
        {
            days++;
            d1.increment();
        }
        while (!d2.isEqualTo(d1));
        return -days;
    }
}

Human::Human(const string& n,const Date& b) : name(n), birthday(b), alive(true)
{
}

unsigned short Human::age() const
{
    return static_cast<unsigned short> (difference_between_2_Dates(TODAY,birthday)/DaysPerYear);
}

double Human::decimal_age() const
{
    return (difference_between_2_Dates(TODAY,birthday)/DaysPerYear);
}

void Human::display() const
{
    cout << name << " was born on ";
    birthday.display();
    cout << " is " << age() << endl;
}

Population::Population(int sz) : people(new Human*[sz]), size(sz)
{
    for (unsigned long i = 0; i < size; ++i)
    {
        people[i] = new Human(NAMES[i],getBirthday());
    }
}


Population::~Population()
{
    unsigned long i;
    for (i = 0; i < size; ++i) delete people[i];
    delete [] people;
}


void Population::display() const
{
    cout << "-----------------------------------------------\n";
    cout << "Today is ";
    TODAY.display();
    cout << endl;
    for (unsigned i = 0; i< size; ++i)
    {
        if (people[i] -> is_alive()) people[i] -> display();
    }
    cout << "-------------------------------------------------\n";
}


void Population::examinePopulation()
{
    unsigned long i;

    for (i = 0; i < size; i++)
    {
        // who lives and who dies?
        if (people[i]->is_alive())
        {
            if (roll_the_dice(people[i]->age())>.5)
            {
                people[i] ->die();
                TODAY.display();
                cout << " " << people[i]->get_name() <<
                     " died at the age of " << people[i] -> age() << endl;
            }
        }
    }
}


unsigned Population::getNumberLiving() const
{
    unsigned count = 0;
    for (unsigned long i = 0; i < size; i++)
    {
        if (people[i]->is_alive()) count++;
    }
    return count;
}


float roll_the_dice(unsigned short age)
{
    float temp = (rand() % 100 * age) / 10000.0f;
    return temp;
}


Date getBirthday()
{
    const int number_of_days_in_100_years = 35625;
    int number_of_days_after_birthdate;
    Date temp_birthday(1,1,1917);

    // generate a random number between 0 and 36524
    number_of_days_after_birthdate = rand() % number_of_days_in_100_years;

    // increment the temp_birthday a random number of days
    for (int j = 0; j < number_of_days_after_birthdate; ++j)
    {
        temp_birthday.increment();
    }
    return temp_birthday;
}
