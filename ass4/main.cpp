
//  Created by Mega Putra on 2/2/17.
//  Copyright � 2017 Mega Putra. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>

using namespace std;

unsigned const int DictionarySize = 23907;
const int MAX_LETTERS_PER_WORD = 30, NUM_WORDS = 550;
const char *DELIMTERS = ".,- \r";

//function prototypes
void openFile(ifstream& inFile, string fileName);
void processDictionary(ifstream& inFile, char dictionary[DictionarySize][MAX_LETTERS_PER_WORD]);
void processGetty(ifstream& inFileGetty, char paragraph[NUM_WORDS][MAX_LETTERS_PER_WORD], char dictionary[DictionarySize][MAX_LETTERS_PER_WORD]);
void selectionSort(char dictionary[DictionarySize][MAX_LETTERS_PER_WORD], const int DictionarySize);
int countRowsInParagraph(ifstream& inFile);
int binarySearch(char *word, char dictionary[DictionarySize][MAX_LETTERS_PER_WORD], const int DictionarySize);

int main()
{
    ifstream inFileDictionary, inFileGetty;
    char dictionary[DictionarySize][MAX_LETTERS_PER_WORD];
    char paragraph[NUM_WORDS][MAX_LETTERS_PER_WORD];
    
    openFile(inFileDictionary, "unsorted_words.txt"); //test file with 18 elements
    processDictionary(inFileDictionary, dictionary);
    inFileDictionary.close();
    
    openFile(inFileGetty, "gettysburg.txt");
    processGetty(inFileGetty, paragraph, dictionary);
    inFileGetty.close();
    
    return 0;
}

/*~~~~~~~~~~~~~ F U N C T I O N  D E F I N I T I O N S ~~~~~~~~~~~~~~~*/
/*------------------openFile ------------------*/
void openFile(ifstream& inFile, string fileName)
{
    inFile.open(fileName.c_str());
    if (!inFile)
    {
        cerr << "Error opening the file." << endl;
        exit(1);
    }
    else
    {
        cout << "File is opened successfully" << endl;
    }
    
}
/*------------------allocateDynamic ------------------*/
void processDictionary(ifstream& inFile, char dictionary[DictionarySize][MAX_LETTERS_PER_WORD])
{
    cout << "Processing file..." << endl;
    char lower = ' ';
    char *word = new char[25];
    for (int wordNum = 0; wordNum < DictionarySize; wordNum++)
    {
        inFile >> word;
        int letterNum = 0;
        for (letterNum = 0; word[letterNum] != '\0'; letterNum++)
        {
            lower = tolower(word[letterNum]);
            dictionary[wordNum][letterNum] = lower;
        }
        *(*(dictionary+wordNum)+letterNum) = '\0';
    }
    selectionSort(dictionary, DictionarySize);
}
//~~~~~~~~~~~~~~~~~~~Populate~~~~~~~~~~~~~~~~~~~~~~~~
//this openFile function reads in the student data file
void processGetty(ifstream& inFileGetty, char paragraph[NUM_WORDS][MAX_LETTERS_PER_WORD], char dictionary[DictionarySize][MAX_LETTERS_PER_WORD])
{
    int wordNum = 0, binaryChecker = 0;
    int lineCount = 0;
    while(!inFileGetty.eof())
    {
        lineCount++;
        char buf[NUM_WORDS];
        char* tok;
        char lower = ' ';
        
        inFileGetty.getline(buf, NUM_WORDS);
        tok = strtok(buf, DELIMTERS);
        
        while(tok != NULL)
        {
            int sn;
            for (sn = 0; tok[sn] != '\0'; sn++)
            {
                lower = tolower(tok[sn]);
                paragraph[wordNum][sn] = lower;
            }
            paragraph[wordNum][sn] = '\0';
            char* word = paragraph[wordNum];
            binaryChecker = binarySearch(word, dictionary, DictionarySize);
            if (binaryChecker == -1) // if word not found
            {
                cout << "Misspelled word, " << word << " on line  " << lineCount << endl;
            }
            tok = strtok(NULL, DELIMTERS);
            wordNum++;
        }
        
    }
}
/*~~~~~~~~~~~~~~~~~~~selectionSort~~~~~~~~~~~~~~~~~~~~~~~~*/
//selection sort function
void selectionSort(char dictionary[DictionarySize][MAX_LETTERS_PER_WORD], const int DictionarySize)
{
    char temp[20];
    int minWordIndex =0;
    
    for (int wordNum = 0; wordNum < DictionarySize; wordNum++)
    {
        minWordIndex = wordNum;
        
        for (int inner = wordNum+1; inner < DictionarySize ;inner++)
        {
            if (strcmp(*(dictionary+minWordIndex), *(dictionary+inner)) > 0)
            {
                minWordIndex = inner;
            }
        }
        strcpy(temp, *(dictionary+wordNum));
        strcpy(*(dictionary+wordNum), *(dictionary+minWordIndex));
        strcpy(*(dictionary+minWordIndex), temp);
    }
}
//~~~~~~~~~~~~~~~~~~binarySearch~~~~~~~~~~~~~~~~~~~~~~~~
//Binary Seach Function

int binarySearch(char *word, char dictionary[DictionarySize][MAX_LETTERS_PER_WORD], const int DictionarySize)
{
    int low, high, middle,  stringCompareIndex = 0;
    low = 0;
    high = DictionarySize - 1;
    
    while (low <= high)
    {
        middle = (low + high) / 2;
        stringCompareIndex = strcmp(word, dictionary[middle]);
        
        if (stringCompareIndex < 0)
        {
            high = middle - 1;
        }
        else if (stringCompareIndex > 0)
        {
            low = middle + 1;
        }
        else
            return middle;
    }
    return -1; // Return -1 if word is not found
}
