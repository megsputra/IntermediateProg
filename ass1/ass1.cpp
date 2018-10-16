//
//  Assignment1 / Mega Putra
//
//  Created by Mega Putra on 1/10/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

//constants
const int ASS_MAX = 10, STUDENT_MAX = 50;

//function prototypes
void welcome();
bool openFile(ifstream &inFile);
bool readData(ifstream&, int& id, int& ex, int ass[], int& midterm, int& fin, int& codeLab);
int assTotal(int assignments[], int size);
int findLowest(int a[], int size);
int calcPoints(int assTotal, int ex, int mid, int fin, int codeLab);
int calcPercentage(int totalPts);
string calcLetterGrade(int totalPct, int& numA, int& numB, int& numC, int& numD, int& numF);
int writeData(int id, int ex, int ass[], int subTotalAss, int mid, int fin, int codeLab, int pts, int pct, string grade);
double calcAvgPct(int studentPct[]);
void findHighest(int totalPts, int& maxPts);
void writeSummary(int numA, int numB, int numC, int numD, int numF, double percentAvg, int maxPts);
void farewell();

int main()
{
    ifstream inFile;
    int id, ex, midterm, fin, codeLab, ass[ASS_MAX], subTotalAss, totalPts, totalPct, student, studentPct[STUDENT_MAX], count = 0, maxPts = 0, numA = 0, numB = 0, numC = 0, numD = 0, numF = 0;
    double percentAvg;
    string letterGrade;
    bool end = false; //eof indicator
    
    welcome();
    if(!openFile(inFile))
        exit(1);
    
    while (!end)
    {
        end = readData(inFile, id, ex, ass, midterm, fin, codeLab);
        
        if (!end)
        {
            subTotalAss = assTotal(ass, ASS_MAX);
            totalPts = calcPoints(subTotalAss, ex, midterm, fin, codeLab);
            totalPct = calcPercentage(totalPts);
            letterGrade = calcLetterGrade(totalPct, numA, numB, numC, numD, numF);
            student = writeData(id, ex, ass, subTotalAss, midterm, fin, codeLab, totalPts, totalPct, letterGrade);
            
            //creating pct array
            studentPct[count] = totalPct;
            count++;
            
            //finding max point
            findHighest(totalPts, maxPts);
        }
    }
    percentAvg = calcAvgPct(studentPct);
    writeSummary(numA, numB, numC, numD, numF, percentAvg, maxPts);
    farewell();
    return 0;
}

/*_____________________________________________________
 
                    FUNCTION DEFINITIONS
 ______________________________________________________
 */
/*~~~~~~~~~~~~~~~~~~~welcome~~~~~~~~~~~~~~~~~~~~~~~~*/
//this welcome function prints the opening message of the program
void welcome()
{
    cout << "Hello and welcome to My Program for Assignment 1 \n"
         << "This program reads the student data and creates a new file containing calculated scores.\n"
         << "This program also shows student's final letter grade for the course.\n" << endl;
}

/*~~~~~~~~~~~~~~~~~~~openFile~~~~~~~~~~~~~~~~~~~~~~~~*/
//this openFile function reads in the student data file
bool openFile(ifstream &inFile)
{
    //opening file via constructor
    inFile.open("studentdata.txt");
    if (!inFile)
    {
        cerr << "Error! Fail to open file!" << endl;
        return 0;
    }
        cout << "File successfully opened." << endl;
    return 1;
}
/*~~~~~~~~~~~~~~~~~~~readData~~~~~~~~~~~~~~~~~~~~~~~~*/
//this readData function reads data from the student file
bool readData(ifstream &inFile, int& id, int& ex, int ass[], int& midterm, int& fin, int& codeLab)
{
    if(inFile.eof())
        return true;
    
    //reading variables
    inFile >> id >> ex;
    for (int i = 0; i < 10; i++)
    {
        inFile >> ass[i];
    }
    inFile >> midterm >> fin >> codeLab;

    return false;
}
/*~~~~~~~~~~~~~~~~~~~assTotal~~~~~~~~~~~~~~~~~~~~~~~~*/
//assTotal function gives total points of the assignments with the lowest grade dropped
int assTotal(int assignments[], int ASS_MAX)
{
    int total = 0; //lowest = assignment[0];
    for (int i = 0; i < ASS_MAX; i++)
    {
        total += assignments[i];
    }
    total -= findLowest(assignments, ASS_MAX); //return total - min(assignments, size)
    
    return total;
}
/*~~~~~~~~~~~~~~~~~~~findLowest~~~~~~~~~~~~~~~~~~~~~~~~*/
//findLowest function finds the lowest score out of all assignments
int findLowest(int a[], int ASS_MAX)
{
    int lowest = a[0];
    for (int i = 1; i < ASS_MAX; i++)
    {
        if (a[i] < lowest)
            lowest = a[i];
    }
    return lowest;
}
/*~~~~~~~~~~~~~~~~~~~calcPoints~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcPoints function calculates the total accumulated points for the course
int calcPoints(int assTotal, int ex, int mid, int fin, int codeLab)
{
    int totalPts = 0;
    totalPts = assTotal + ex + mid + fin + codeLab;
    
    return totalPts;
}
/*~~~~~~~~~~~~~~~~~~~calcPercentage~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcPercentage function calculates the percentage of points out of 400
int calcPercentage(int totalPts)
{
    int totalPct = 0;
    totalPct = round(totalPts / 400.0 * 100.0);
    
    return totalPct;
}
/*~~~~~~~~~~~~~~~~~~~calcLetterGrade~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcLetterGrade function shows the letter grade for the class, also tracks
//how many times each letter grade appears.
string calcLetterGrade(int totalPct, int& numA, int& numB, int& numC, int& numD, int& numF)
{
    string grade;
    int divGrade = totalPct/10; //evaluate the percentage by tenths
    
    switch(divGrade)
    {
        case 10:
        case 9: grade = 'A';
            numA++; //count number of A's
            break;
        case 8: grade = 'B';
            numB++;
            break;
        case 7: grade = 'C';
            numC++;
            break;
        case 6: grade = 'D';
            numD++;
            break;
        default: grade = 'F';
            numF++;
    }
    //+ or - added within 2% of grade boundary
    if (totalPct % 10 < 2)
        grade += ('-');
    if (totalPct% 10 > 8)
        grade += ('+');
    
        return grade;
}
/*~~~~~~~~~~~~~~~~~~~writeData~~~~~~~~~~~~~~~~~~~~~~~~*/
//the writeData function writes the student report output to a file
int writeData(int id, int ex, int ass[], int subTotalAss, int mid, int fin, int codeLab, int pts, int pct, string grade)
{
    int static student = 0;
    
    if (student == 0)
    {
        ofstream outFile ("reportcard.txt");
        if (!outFile)
            cerr << "Error opening the report card!" << endl;
        else
            cout << "Student report created." << endl;
        
        outFile << "Stdnt Id " << " Ex " << " ------- Assignments --------- " << " Tot " << " Mi " << " Fin " << " CL " << " Pts " << " Pct " << " Gr " << endl;
        outFile << "-------- " << " -- " << " ----------------------------- " << " --- " << " -- " << " --- " << " -- " << " --- " << " --- " << " -- " << endl;
    }
    student++;
    
    ofstream outFile ("reportcard.txt", ios::app);
    
    outFile << setfill('0') << setw(8) << id << setfill(' ') << setw(4) << ex << " " << setw(5);
    for (int i = 0; i < 10; i++)
    {
        outFile << setw(3) << ass[i];
    }
    outFile << setw(5) << subTotalAss << setw(4) << mid << setw(5) << fin << setw(4) << codeLab << setw(5) << pts << setw(5) << pct << "  " << left << grade << endl;
    
    outFile.close();
    
    return student;
}
/*~~~~~~~~~~~~~~~~~~~calcAvgPct~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcAvgPct function calculates the average percentage achieved by student
double calcAvgPct(int studentPct[])
{
    double subtotal, avgPct = 0.0;
    
    for (int i = 0; i < STUDENT_MAX; i++)
    {
        subtotal += studentPct[i];
    }
    avgPct = subtotal / 50.0;
    
    return avgPct;
}
/*~~~~~~~~~~~~~~~~~~~findHighest~~~~~~~~~~~~~~~~~~~~~~~~*/
//findHighest function finds the highest number of points achieved by student
void findHighest(int totalPts, int& maxPts)
{
    if (totalPts > maxPts)
        maxPts = totalPts;
}
/*~~~~~~~~~~~~~~~~~~~writeSummary~~~~~~~~~~~~~~~~~~~~~~~~*/
//writeSummary function writes a summary report to a file
void writeSummary(int numA, int numB, int numC, int numD, int numF, double percentAvg, int maxPts)
{
    ofstream summaryFile("summaryreport.txt");
    if (!summaryFile)
        cerr << "Error opening the summary report!" << endl;
    else
        cout << "Summary report created." << endl;
    
    summaryFile << "Number of A's = " << numA << endl;
    summaryFile << "Number of B's = " << numB << endl;
    summaryFile << "Number of C's = " << numC << endl;
    summaryFile << "Number of D's = " << numD << endl;
    summaryFile << "Number of F's = " << numF << endl;
    summaryFile << "Average percent = " << setprecision(1) << fixed << percentAvg << endl;
    summaryFile << "Maximm points = " << maxPts << endl;
}
/*~~~~~~~~~~~~~~~~~~~farewell~~~~~~~~~~~~~~~~~~~~~~~~*/
//farewell function prints end message
void farewell()
{
    cout << "\nThank you for using my program. \n" <<
    "Data for " << STUDENT_MAX << " students has been generated.\n" <<
    "Please check two output files for part 1 and part 2." << endl;
}


