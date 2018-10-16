
//
//  Created by Mega Putra on 3/2/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

unsigned DaysPerMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const string NAMES[] =
{
    "Joshua","Kyle","Yuxi","Anthony","Michael","Samuel","Karlen","Seyed Nima",
    "Mega","Tamuz","Ali","Ting","Khang","Quang","Rafael","David",
    "Shenghao","Shealtiel","Johnny","Coriena","Minh Quan","Hong Yip","Robert",
    "Yingqi","Manxin","Shun","Dekel","Yash","Shuo","Shiyu","Jiayi",
    "Tristan","Carlo","Jason","Thao","Joe"
};

/*-------------------------------------------------------
 ----------------- DATE CLASS ---------------------------
 -------------------------------------------------------*/
class Date
{
    unsigned month;
    unsigned day;
    unsigned year;
    bool isALeapYr() const;
public:
    Date();
    Date(unsigned,unsigned,unsigned);
    void increment(Date &tempDate);
    int calcAge(); //measured in number of days old
    void letTimePass();
    void display() const;
};

Date TODAY;

Date::Date(unsigned m,unsigned d,unsigned y) : month(m), day(d), year(y)
{
    
}

Date::Date()
{
    time_t now = time(0);
    tm* ptr2tm = localtime(&now);
    
    day = ptr2tm->tm_mday;
    month = ptr2tm->tm_mon + 1;
    year = ptr2tm->tm_year+1900;
}

void Date::increment(Date &tempDate) //pass by reference
{
    if (tempDate.isALeapYr())
        DaysPerMonth[2] = 29;
    else
        DaysPerMonth[2] = 28;

    tempDate.day++;
    
    if (tempDate.day > DaysPerMonth[month])
    {
        tempDate.month++;
        tempDate.day = 1;
    }
    if (tempDate.month > 12)
    {
        tempDate.year++;
        tempDate.month = 1;
    }
}

bool Date::isALeapYr() const
{
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

void Date::display() const
{
    cout << setw(2) << setfill('0') << month << '/'
    << setw(2) << setfill('0') << day << '/'
    << setw(2) << setfill('0') << year % 100;
}

int Date::calcAge() //gets how many DAYS old a person is and divide by 365.25
{
 
    int numDays = 0, age = 0;
    Date tempDate(month, day, year);
    
    while (tempDate.year != TODAY.year || tempDate.month != TODAY.month|| tempDate.day!= TODAY.day)
    {
        increment(tempDate);
        numDays++;
    }
    age = numDays / 365.25;
    return age;
}

void Date::letTimePass()
{
    Date tempDate(month, day, year);
    int numDaysPassed = rand() % 365 + 1;
    for (int i = 0; i < numDaysPassed; i++)
    {
        increment(tempDate);
    }
    day = tempDate.day;
    month = tempDate.month;
    year = tempDate.year;
}

Date createBday(); //function prototype

/*-------------------------------------------------------
 ---------------- HUMAN CLASS ---------------------------
 -------------------------------------------------------*/
class Human
{
private:
    string name;
    Date birthday;
    bool alive;
public: //constructor
    Human(const string& n, const Date& b);
    int getAge(){return birthday.calcAge();}
    string getName() {return name;}
    Date getBday() {return birthday;}
    void die() {alive = false;}
    bool isAlive() {return alive;}
    void display(); //cannot put const here
};

Human::Human(const string& n, const Date& b) : name(n), birthday(createBday()), alive(true)
{
}

void Human::display()
{
    cout << name << " was born on ";
    birthday.display();
    cout << " is " << getAge() << endl;
}
/*-------------------------------------------------------
 ---------------- POPULATION CLASS ----------------------
 -------------------------------------------------------*/
class Population
{
private:
    Human** people;
    unsigned size;
public:
    Population(int);
    ~Population();
    void examinePopulation();
    void display() const;
    float rollTheDice(unsigned short age) {return static_cast<float>(age)*(rand()%100)/10000;}
    int getNumberLiving() const;
};

Population::Population(int size): people(new Human*[size])
{
    this->size = size;
    for (int i = 0; i < size;i++)
    {
        people[i] = new Human(NAMES[i], createBday());
    }
}

Population::~Population() //destructor: release dynamically allocated memory
{
    for (int i = 0; i < size; i++)
    {
        delete people[i];
        people[i] = nullptr;
    }
    delete[] people;
    people = nullptr;
}

int Population::getNumberLiving() const
{
    int numDead, numLiving = 0;
    for (int i = 0; i < size; i++)
    {
        if (people[i]->isAlive() == false)
        {
            numDead++;
        }
    }
    numLiving = size - numDead;
    return numLiving;
}

void Population::examinePopulation()
{
    int tempAge = 0;
    for (int i = 0; i < size; i++)
    {
        if (people[i]->isAlive() == true)
        {
            tempAge = people[i]->getAge();
            if (rollTheDice(tempAge) > 0.5)
            {
                (people[i]->getBday()).display(); cout << ' ';
                people[i]->die(); // make alive false
                cout << people[i]->getName() << " died at age of " << tempAge << endl;
            }
        }
    }
}

void Population::display() const
{
    cout << "-------------------------------------------------" << endl;
    cout << "Today is "; TODAY.display(); cout << endl;
    for (int i = 0; i < size; i ++)
    {
        if(people[i]->isAlive() == 1)
        {
            people[i]->display();
        }
    }
    cout << "-------------------------------------------------" << endl;
}

int main()
{
    const int OriginalPopulationSize = 36;
    srand(unsigned(time(NULL)));
    Population World(OriginalPopulationSize);
    World.display();
    do
    {
        TODAY.letTimePass();
        World.examinePopulation();
    }
    while (World.getNumberLiving() > OriginalPopulationSize/2);

    World.display();
}

//non-class function definition
Date createBday()
{
    unsigned d, m, y = 0;
    d = rand()% 31+1;
    m = rand()% 12+1;
    y = rand()% 100+1917;
    
    if (d == 29 && y % 4 == 0)
    {
        m = 2;
    }
    Date temp(m,d,y);
    
    return temp;
}
