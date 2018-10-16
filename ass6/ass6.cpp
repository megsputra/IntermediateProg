
//
//  Created by Mega Putra on 2/24/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//constants
const int NUM_FILES = 300; //only read 300 files

//class
class MutualFund
{
private:
    string ticker;
    int *date = new int [NUM_FILES];
    string *close = new string[NUM_FILES];
public:
    double getMinLastYear() const;
    double getMaxLastYear() const;
    void assignTicker(string tickerName);
    void readHistoryFile(string fileName);
    void report() const;
    double getLast50() const;
    double getLast200() const;
    double gain() const;
    string recommend() const;
};

//function prototypes
string get5thColumn(string line);
int getDay(string line);
int getMonth(string line);
int getYear(string line);
int getDate(string line);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                MEMBER FUNCTIONS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* This function Assigns Ticket to Mutual Fund */
void MutualFund::assignTicker(string tickerName)
{
    ticker = tickerName;
}
/* This functiono reads data from file and stores it in the class*/
void MutualFund::readHistoryFile(string fileName)
{
    ifstream fin;
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Error opening the file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << fileName << " is opened successfully" << endl;
    }
    
    string buffer;
    int i =0;
    while(i < NUM_FILES)
    {
        getline(fin,buffer);
        if (buffer.length() < 42)
        {
            buffer.clear();
            continue;
        }
        else
        {
            date[i] = getDate(buffer);
            close[i] = get5thColumn(buffer);
            i++;
        }
    }
    fin.close();
}
/* This function gets the minimum closing price starting 2/24/16 */
double MutualFund::getMinLastYear() const
{
    int today = date[0];
    int yearAgo = today - 10000;
    int tempDate = yearAgo;
    int stopIndex = 0;
    for(int i = 0; i < NUM_FILES; i++)
    {
        if (date[i] < yearAgo)
        {
            stopIndex = i;
        }
    }
    string minClose = close[stopIndex]; //start at last year's index
    int i = stopIndex;
    while (tempDate >= yearAgo && i >= 0)
    {
        if (minClose > *(close+i))
        {
            minClose = *(close+i);
        }
        i--;
        tempDate++;
    }
       return stod(minClose);
}
/* This function gets the maximum closing price starting 2/24/16 */
double MutualFund::getMaxLastYear() const
{
    int today = date[0];
    int yearAgo = today - 10000;
    int tempDate = yearAgo;
    int stopIndex = 0;
    for(int i = 0; i < NUM_FILES; i++)
    {
        if (date[i] < yearAgo)
        {
            stopIndex = i;
        }
    }
    string maxClose = close[stopIndex];
    int i = stopIndex;
    while (tempDate >= yearAgo && i >= 0)
    {
        if (maxClose < *(close+i))
        {
            maxClose = *(close+i);
        }
        i--;
        tempDate++;
    }
    return stod(maxClose);
}
/* This function calculates the average for the last 50 days */
double MutualFund::getLast50() const
{
    double average50, sumLast50Days =0;
    double closeDouble[NUM_FILES];
    
    for (int i = 0; i < 50; i++)
    {
        closeDouble[i] = stod(close[i]);
        sumLast50Days += closeDouble[i];
    }
    average50 = sumLast50Days/50;
    
    return average50;
}
/* This function calculates the average for the last 200 days */
double MutualFund::getLast200() const
{
    double average200, sumLast200Days =0;
    double closeDouble[NUM_FILES];
    
    for (int i = 0; i < 200; i++)
    {
        closeDouble[i] = stod(close[i]);
        sumLast200Days += closeDouble[i];
    }
    average200 = sumLast200Days/200;
    
    return average200;
}
/* This function calculates whether it's a gain or a loss over  200 days*/
double MutualFund::gain() const
{
    double movingAvg;
    movingAvg = (stod(close[0]) / getLast200()) *100 - 100;
    
    return movingAvg;
}

/* This function gives user recommendation based on ratio between gain and 200 day moving average*/
string MutualFund::recommend() const
{
    double gainOrLoss = gain();
    string recommendation;
    if (gainOrLoss < -3)
    {
        recommendation = "Buy";
    }
    else if (gainOrLoss > 3)
    {
        recommendation = "Sell";
    }
    else
    {
        recommendation = "Hold";
    }
    return recommendation;
}

/* This function prints the report*/
void MutualFund::report() const
{
    int mo, year, day; double closeVar = stod(*close);
    mo = (date[0] / 100)%100;
    year = (date[0] /10000)% 100;
    day = date[0] % 100;

    cout <<"Fund: " << ticker << endl;
    cout <<"Analysis Date: " << setfill('0') << setw(2) << mo << '/'<< day << '/' << year << endl;
    cout <<"Latest Close: $" << setprecision(2) << fixed << closeVar << endl;
    cout <<"Minimum for the last year = $" << setprecision(2) << fixed << getMinLastYear() << endl;
    cout <<"Maximum for the last year = $" << setprecision(2) << fixed << getMaxLastYear() << endl;
    cout <<"50 day moving average = $" << getLast50() << endl;
    cout <<"200 day moving average = $" << setprecision(2) << fixed << showpoint << getLast200() << endl;
    cout <<"% gain over 200 Day Moving Avg: "<< setprecision(1) <<fixed << gain()<< '%'<< endl;
    cout <<"Recommendation: " << recommend() << endl << endl;
    
    //release memory
    delete [] date; //date = nullptr; or it can't be const!
    delete [] close; //close = nullptr;
}

int main()
{
    MutualFund vbmfx;
    vbmfx.assignTicker("VBMFX");
    vbmfx.readHistoryFile("vbmfx.txt");
    vbmfx.report();

    MutualFund vtsmx;
    vtsmx.assignTicker("VTSMX");
    vtsmx.readHistoryFile("vtsmx.txt");
    vtsmx.report();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            NON-MEMBER FUNCTIONS
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* This function parses the closing price*/
string get5thColumn(string line)
{
    size_t posOf4thComma, posOf5thComma, pos;
    string closeString;
    
    pos = line.find(',');
    pos = line.find(',',pos+1);
    pos = line.find(',',pos+1);
    posOf4thComma = line.find(',',pos+1);
    posOf5thComma = line.find(',',posOf4thComma+1);
    closeString = line.substr(posOf4thComma+1,posOf5thComma-posOf4thComma-1);
    
    return closeString;
}
/*these functions parses the dd/mm/yyyy on the buffer*/
int getYear(string line)
{
    size_t pos = line.find_first_of("-");
    return stoi(line.substr(0,pos));
}
int getMonth(string line)
{
    return stoi(line.substr(5,2));
}
int getDay(string line)
{
    size_t pos;
    pos = line.find(',');
    
    return stoi(line.substr(pos-2, 2));
}
int getDate(string line)
{
    int day, month, year = 0;
    day = getDay(line);
    month = getMonth(line);
    year = getYear(line);
    return year * 10000 + month * 100 + day;
}
