// CIS22B Assignment 1 Solution - Winter 2017

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

const string InputFilename = "c:/temp/ass1data.txt";
const string OutputFilename = "c:/temp/ass1output.txt";
const string SummaryFilename = "c:/temp/ass1summary.txt";

const unsigned short NumberOfStudents = 50;
const unsigned short PointsPossible = 400;
const unsigned short NumberOfAssignments = 10;

// Function prototypes
bool readPointsFromFile(ifstream& fin,int& studentId, int& exercisePoints, int* assPoints,int& midtermPoints, int& finalPoints,int &codelabPoints);
int calculateAssTotalPoints(int* ass);
char getGradeFromPercent(int percent);
char getPlusMinusFromPercent(int percent);
void    printSummary(ofstream& fout, int * gradeCount, double avgPercent, int maxPoints);

int main()
{
    int studentId, assPoints[NumberOfAssignments], midtermPoints, finalPoints, exercisePoints, codelabPoints, totalAssPoints, totalPoints, maxPoints = 0;
    int gradeCount[6] = {0};
    int sumPercent  = 0;
    char grade, plusOrMinus;
    double avgPercent;

    int pointsPercent;
    ifstream fin(InputFilename.c_str());

    if (!fin)
    {
        cerr << "Unable to open file, " << InputFilename << endl;
        exit(1);
    }
    ofstream fout(OutputFilename.c_str());

    if (!fout)
    {
        cerr << "Unable to open file, " << OutputFilename << endl;
        exit(2);
    }
    ofstream sumout(SummaryFilename.c_str());

    if (!sumout)
    {
        cerr << "Unable to open file, " << SummaryFilename << endl;
        exit(3);
    }

    // Print headings
    fout << "Stdnt Id  Ex  ------- Assignments ---------  Tot  Mi  Fin  CL  Pts  Pct  Gr" << endl;
    fout << "--------  --  -----------------------------  ---  --  ---  --  ---  ---  --" << endl;


    while (readPointsFromFile(fin,studentId, exercisePoints, assPoints, midtermPoints, finalPoints, codelabPoints))
    {
        totalAssPoints = calculateAssTotalPoints(assPoints);
        totalPoints = totalAssPoints + midtermPoints + exercisePoints + codelabPoints + finalPoints;
        pointsPercent = static_cast<int>(100.0 * totalPoints / PointsPossible + 0.5);
        grade = getGradeFromPercent(pointsPercent);

        plusOrMinus = getPlusMinusFromPercent(pointsPercent);
        gradeCount[grade-'A']++;
        sumPercent += pointsPercent;
        if (totalPoints > maxPoints) maxPoints = totalPoints;

        fout << setfill('0') << setw(8) << studentId << setfill(' ') << ' ';
        fout << setw(3) << exercisePoints << ' ';
        for (int j = 0 ; j < NumberOfAssignments; j++)
            fout << setw(3) << assPoints[j];
        fout << setw(5) << totalAssPoints
             << setw(4) << midtermPoints
             << setw(5) << finalPoints
             << setw(4) << codelabPoints
             << setw(5) << totalPoints
             << setw(5) << fixed << setprecision(1) << pointsPercent
             << setw(3) << grade << plusOrMinus << endl;
    }

    avgPercent = static_cast<double>(sumPercent) / NumberOfStudents;
    printSummary(sumout, gradeCount, avgPercent, maxPoints);

    return 0;
}

bool readPointsFromFile(ifstream& fin,int& studentId, int& exercisePoints, int* assPoints,int& midtermPoints, int& finalPoints,int& codelabPoints)
{
    // Get student Id
    fin >> studentId;
    if (fin.eof()) return false;

    fin >> exercisePoints;

    // Get assignment grades
    for (int i = 0; i < NumberOfAssignments; i++)
    {
        fin >> assPoints[i];
    }
    // Get midterm, exercise, CodeLab, final
    fin >> midtermPoints >> finalPoints >> codelabPoints ;
    return true;
}

int calculateAssTotalPoints(int* ass)
{
    int min = ass[0];
    int sum = ass[0];
    for (int i = 1; i < NumberOfAssignments; i++)
    {
        if (min > ass[i]) min = ass[i];
        sum += ass[i];
    }
    return sum - min;
}

char getGradeFromPercent(int pct)
{
    switch (pct/10)
    {
    case 6:
        return 'D';
    case 7:
        return 'C';
    case 8:
        return 'B';
    case 9:
    case 10:
        return 'A';
    default:
        ;
    }
    return 'F';
}

char getPlusMinusFromPercent(int percent)
{
    if (percent >97) return '+';
    if (percent > 59)
    {
        if (percent % 10 > 7) return '+';
        if (percent % 10 < 2) return '-';
    }
    return ' ';
}

void    printSummary(ofstream& fout, int * gradeCount, double avgPercent, int maxPoints)
{
    const char letters[] = {"ABCDEF"};
    for (int i = 0; i < 6; i++)
    {
        if (i != 4)
            fout << "Number of " << letters[i] << "'s = " << gradeCount[i] << endl;
    }
    fout << setprecision(1) << fixed;
    fout << "Average percent = " << avgPercent << endl;
    fout << "Maximum points = " << maxPoints << endl;
}
