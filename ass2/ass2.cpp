
//
//  Created by Mega Putra on 1/18/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const unsigned short DICTIONARY_WORDS = 16000;
const unsigned short NUM_KEYWORDS = 84;

void welcome();
void readFromFile (ifstream& file, string* array, int sz);
void selectionSort(string a[], int size);
void swap (int& a, int& b);
bool binarySearch(string searchValue, string* a, int sz);
void write2File(string* keywords, string* dictionary, int NUM_KEYWORDS, int DICTIONARY_WORDS);
void farewell();

int main()
{
    string dictionary[DICTIONARY_WORDS], keywords[NUM_KEYWORDS];
    ifstream dictionaryFile, keywordsFile;
    
    welcome();
    dictionaryFile.open("unsorted_dictionary.txt");
    keywordsFile.open("keywords.txt");
    if (!dictionaryFile)
    {
        cerr << "Unable to open the Dictionary file. " << endl;
        exit(1);
    }
    else cout << "Dictionary file successfully opened" << endl;
        
    if (!keywordsFile)
    {
        cerr << "Unable to open the Keyword file.\n" << endl;
        exit(1);
    }
    else cout << "Keyword file successfully opened" << endl;
    
    readFromFile(dictionaryFile, dictionary, DICTIONARY_WORDS);
    readFromFile(keywordsFile, keywords, NUM_KEYWORDS);
    
    selectionSort(dictionary, DICTIONARY_WORDS);
    cout << "Dictionary words are now sorted" << endl;
    selectionSort(keywords, NUM_KEYWORDS);
    cout << "Keywords are now sorted" << endl;
    
    write2File(keywords, dictionary, NUM_KEYWORDS, DICTIONARY_WORDS);
    farewell();
    return 0;
}

/* ~~~~~~~~~~~~~~~~~FUNCTION DEFINITIONS~~~~~~~~~~~~~~~~~ */
//this function displays a welcome file
void welcome()
{
    cout << "Hello and welcome to my program for Assignment 2!" << endl;
    cout << "This program searches various C++ keywords and matches them with a list of dictionary words." << endl;
    cout << "This program will use the selection sort and the binary search algorithm to match the words." << endl;
    cout << "Both algorithms are chosen because they require the least amount of swaps compared to other relevant algorithms. " << endl;
    cout << "There will be an output file generated showing words that are not found.\nLets Start!\n" << endl;
}

//This function reads data from files
void readFromFile (ifstream& file, string* array, int sz)
{
    for (int i = 0; i < sz; i++)
    {
        file >> array[i];
        if (file.eof())
            break;
    }
}

//selection sort function
void selectionSort(string a[], int size)
{
    int minIndex;
    for (int i = 0; i < size - 1; i++)
    {
        minIndex = i;
        for (int j = i+1; j < size; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            swap(a[i],a[minIndex]);
        }
    }
}

//swap function has a purpose, which is to do the swaps on the sorting function
void swap (int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

//this is the binary Search Function
bool binarySearch(string searchValue, string* a, int sz)
{
    int low, high, middle;
    low = 0;
    high = sz - 1;
    
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (searchValue < a[middle])
        {
            high = middle - 1;
        }
        else if (searchValue > a[middle])
        {
            low = middle + 1;
        }
        else
            return true;
    }
    return false;
}

//this function writes the results to an output file
void write2File(string* keywords, string* dictionary, int NUM_KEYWORDS, int DICTIONARY_WORDS)
{
    ofstream outFile("outfile.txt");
    if (!outFile)
        cerr << "Error opening the output file!" << endl;
    else
        cout << "Summary report created\n" << endl;
    
    bool wordFound;
    int notFound = 0;
    for (int j = 0; j < NUM_KEYWORDS; j++)
    {
        wordFound = binarySearch(keywords[j], dictionary, DICTIONARY_WORDS);
        if (!wordFound)
        {
            outFile << "keyword not found: " << keywords[j] << endl;
            notFound++;
        }
    }
    cout << "Number of keywords not found = " << notFound << endl;
    outFile.close();
}

//this function prints a farewell message
void farewell()
{
    cout << "\nThank you for using my program. Good bye!" << endl;
}




