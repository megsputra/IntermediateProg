
//  Created by Mega Putra on 1/24/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

//constants
const unsigned int ASS_MAX = 10;
const unsigned int Rows = 50, STUDENT_MAX = 50;
const unsigned int Cols = 20;

//function prototypes
void welcome();
bool openFile(ifstream &inFile);
void populate(ifstream &inFile, int (*p)[Cols]);
void selectionSort(int (*a)[Cols], int selectCol, string sortStyle);
void swap (int* a, int* b);
int assTotal(int *assignments, int size);
int findLowest(int *a, int size);
int calcPoints(int *pointPointer);
int calcPercentage(int *totalPts);
char calcLetterGrade(int totalPct, char* plusMin);
int writeData(int (*A)[Cols], string fileName, int student);
void print2dArray(int (*A)[Cols]);
void farewell();

int main()
{
    ifstream inFile;
    int array_2d[Rows][Cols];
    
    welcome();
    if(!openFile(inFile))
        exit(92);
    populate(inFile, array_2d);
    
    selectionSort(array_2d, 0, "Ascending");
    cout << "File is sorted: Ascending" << endl;
    writeData(array_2d, "ascending_id.txt", 0);
    
    selectionSort(array_2d, 16, "Descending");
    cout << "File is sorted: Descending" << endl;
    writeData(array_2d, "descending_pts.txt", 0);
    
    farewell();
}

/*_____________________________________________________
 
 FUNCTION DEFINITIONS
 ______________________________________________________
 */
/*~~~~~~~~~~~~~~~~~~~welcome~~~~~~~~~~~~~~~~~~~~~~~~*/
//this welcome function prints the opening message of the program
void welcome()
{
    cout << "Hello and welcome to My Program for Assignment 3 \n"
    << "This program reads the student data and creates a new file containing calculated scores.\n"
    << "It also sorts by student ID (ascending) and Total Points (descending). \n"
    << "This program mainly features the use of pointers and 2-dimensional array.\n " << endl;
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

/*~~~~~~~~~~~~~~~~~~~Populate~~~~~~~~~~~~~~~~~~~~~~~~*/
//this openFile function reads in the student data file
void populate(ifstream &inFile, int (*p)[Cols])
{
    int r = 0, c = 0, totalPts = 0, totalPct = 0;
    char grade = ' ', plusMin = ' ';
    char *plusMin_ptr = nullptr;
    plusMin_ptr = &plusMin;
    
    for (r = 0; r < STUDENT_MAX; r++)
    {
        for (c = 0; c < 12; c++)
        {
            inFile >> *(*(p + r)+c);
        }
    
        *(*(p + r)+c) = assTotal((*(p + r)+c-1), ASS_MAX);
        
        for (c = 13; c < 16; c++)
        {
            inFile >> *(*(p + r)+c);
        }
        totalPts = calcPoints((*(p + r)+(c-1)));
        *(*(p + r)+c) = totalPts;
        
        totalPct = calcPercentage((*(p + r)+(c)));
        *(*(p + r)+(++c)) = totalPct;
          
        grade = calcLetterGrade(*(*(p + r)+c), plusMin_ptr);
        *(*(p + r)+(++c)) = static_cast<int>(grade);
        *(*(p + r)+(++c)) = static_cast<int>(plusMin);
    }
}

/*~~~~~~~~~~~~~~~~~~~assTotal~~~~~~~~~~~~~~~~~~~~~~~~*/
//assTotal function gives total points of the assignments with the lowest grade dropped
int assTotal(int *ass, int ASS_MAX)
{
    int total = 0, low = 0;
    int *lowptr = nullptr;
    
    low = findLowest(ass, ASS_MAX);
    lowptr = &low;
    
    for (int i = 0; i < ASS_MAX; i++)
    {
        total += *(ass-i);
    }
    total -= (*lowptr);
    return total;
}
/*~~~~~~~~~~~~~~~~~~~findLowest~~~~~~~~~~~~~~~~~~~~~~~~*/
//findLowest function finds the lowest score out of all assignments
int findLowest(int *a, int ASS_MAX)
{
    int lowest = *a;
    for (int i = 0; i < ASS_MAX; i++)
    {
        if (*(a-i) < lowest)
            lowest = *(a-i);
    }
    return lowest;
}
/*~~~~~~~~~~~~~~~~~~~calcPoints~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcPoints function calculates the total accumulated points for the course
int calcPoints(int *pointPointer)
{
    int totalPts = 0;
    for (int j = 0; j<4; j++)
    {
        totalPts += *(pointPointer -j);
    }
    totalPts += *(pointPointer - 14);
    
    return totalPts;
}
/*~~~~~~~~~~~~~~~~~~~calcPercentage~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcPercentage function calculates the percentage of points out of 400
int calcPercentage(int *totalPts)
{
    int totalPct = 0;
    totalPct = round((*totalPts)/ 400.0 * 100.0);
    
    return totalPct;
}
/*~~~~~~~~~~~~~~~~~~~calcLetterGrade~~~~~~~~~~~~~~~~~~~~~~~~*/
//calcLetterGrade function shows the letter grade for the class, also tracks
//how many times each letter grade appears.
char calcLetterGrade(int totalPct, char *plusMin)
{
    char grade;
    int divGrade = totalPct/10;
    
    switch(divGrade)
    {
        case 10:
        case 9: grade = 'A';
            break;
        case 8: grade = 'B';
            break;
        case 7: grade = 'C';
            break;
        case 6: grade = 'D';
            break;
        default: grade = 'F';
    }
    //+ or - added within 2% of grade boundary
    if (totalPct % 10 < 2)
        *plusMin = ('-');
    if (totalPct% 10 > 8)
        *plusMin = ('+');
    
    return grade;
}
/*~~~~~~~~~~~~~~~~~~~writeData~~~~~~~~~~~~~~~~~~~~~~~~*/
//the writeData function writes the output to a specified file
int writeData(int (*A)[Cols], string fileName, int student)
{
    int col = 0; student = 0;
    
    if (student == 0)
    {
        ofstream outFile (fileName.c_str());
        if (!outFile)
            cerr << "Error opening file!" << endl;
        else
            cout << "Output file created.";
        
        outFile << "Stdnt Id  Ex  ------- Assignments ---------  Tot  Mi  Fin  CL  Pts  Pct  Gr" << endl;
        outFile << "--------  --  -----------------------------  ---  --  ---  --  ---  ---  --" << endl;
    }
    student++;
    ofstream outFile (fileName.c_str(), ios::app);
    
    for (int row = 0; row < Rows; row ++)
    {
        col = 0;
        //studentID - 1
        outFile << setw(8) << setfill('0') << *(*(A+row) + col) << setfill(' ');
        //exam - 2
        outFile << setw(4) << *(*(A+row) + (++col)) << " ";
        //assignments - 12
        for (int ass = 0; ass < 10; ass++)
        {
            outFile << setw(3) << *(*(A+row) + (++col));
        }
        //total - 13
        outFile << setw(5) << *(*(A+row) + (++col));
        //midterm - 14
        outFile << setw(4) << *(*(A+row) + (++col));
        //final - 15
        outFile << setw(5) << *(*(A+row) + (++col));
        //codelab - 16
        outFile << setw(4) << *(*(A+row) + (++col));
        //totalpts -17
        outFile << setw(5) << *(*(A+row) + (++col));
        //total pct - 18
        outFile << setw(5) << *(*(A+row) + (++col));
        //letter grade
        outFile << setw(3) << right << static_cast<char>(*(*(A+row) + (++col)));
        outFile << static_cast<char>(*(*(A+row) + (++col))) << endl;
    }
    outFile.close();
    cout << " Data is now written.\n" << endl;
    return student;
}
/*~~~~~~~~~~~~~~~~~~~selectionSort~~~~~~~~~~~~~~~~~~~~~~~~*/
//selection sort function
void selectionSort(int (*a)[Cols], int selectCol, string sortStyle)
{
    int minMax;
    for (int destinationRow = 0; destinationRow < Rows -1; destinationRow++)
    {
        minMax = destinationRow;
        for( int row = destinationRow + 1; row < Rows; row++)
        {
            if (sortStyle == "Ascending")
            {
                if ( *(*(a+row)+ selectCol) < *(*(a+minMax) + selectCol))
                {
                    minMax = row;
                }
            }
            else
            {
                if ( *(*(a+row)+ selectCol) > *(*(a+minMax) + selectCol))
                {
                    minMax = row;
                }
            }
        }
        swap((*(a +destinationRow)), (*(a + minMax)));
    }
}
/*~~~~~~~~~~~~~~~~~~~swap~~~~~~~~~~~~~~~~~~~~~~~~*/
//swap function has a purpose, which is to do the swaps on the sorting function
void swap (int* a, int* b)
{
    int temp;
    for (int col = 0; col < Cols; col++)
    {
        temp = *(a + col);
        *(a + col) = *(b + col);
        *(b + col) = temp;
    }
    
}
/*~~~~~~~~~~~~~~~~~~~farewell~~~~~~~~~~~~~~~~~~~~~~~~*/
//farewell function prints end message
void farewell()
{
    cout << "Thank you for using my program. \n" <<
    "Data for " << STUDENT_MAX << " students has been generated.\n" <<
    "Please check two output files for part 1 and part 2." << endl;
}

//print array function is for testing purposes only :)
/*void print2dArray(int (*A)[Cols])
{
    for (int r = 0; r < Rows; r++)
    {
        int c = 0;
        for (c = 0; c < (18); c++)
        {
            cout << *(*(A + r)+c) << " ";
        }
        for (c = 18; c < Cols; c++)
        {
            cout << static_cast<char>(*(*(A + r) + c));
        }
        cout << endl;
    }
}*/
