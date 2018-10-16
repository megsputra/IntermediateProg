// Assignment 4: Spell Check Program Solution
// 10/2016

#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

const int DictionarySize = 23907;

void getDictionary(const char* filename,char**);
void spellCheckLine(char* line, int lineNumber, char** dictionary);
bool wordIsInDictionary(const char* word, char** dictionary);
void toLowerCase(char* text);
void sort(char** list);

int main()
{
    const char* wordfile = "c:/temp/unsorted_words.txt";
    const char* testfile = "c:/temp/gettysburg.txt";
    char buffer[128];

    char* dictionary[DictionarySize];
    getDictionary(wordfile, dictionary);

    // sort the dictionary
    sort(dictionary);

    int lineNumber = 0;

    // read a process file to be spell checked
    ifstream fin(testfile);
    if (!fin)
    {
        cerr << "Unable to open word file " << testfile << endl;
        exit(2);
    }

    while (!fin.eof())
    {
        lineNumber++;
        fin.getline(buffer,sizeof(buffer));
        if (fin.eof()) break;
        toLowerCase(buffer);
        spellCheckLine(buffer,lineNumber, dictionary);
    }
    for (int i = 0; i < DictionarySize; i++)
        delete [] dictionary[i];
}

void spellCheckLine(char* line, int lineNumber,  char** dictionary)
{
    char* ptr = line;

    strtok(line,"\r");

    ptr = strtok(line," ,.-\r");
    while (ptr != NULL)
    {
        if (!wordIsInDictionary(ptr, dictionary))
        {
            cout << "Misspelled word, " << ptr << " on  line " << lineNumber << endl;
        }

        ptr = strtok(NULL," ,.-\r");
    }
}


void getDictionary(const char* filename, char* dictionary[])
{
    char temp[32];
    ifstream fin(filename);
    if (!fin)
    {
        cerr << "Unable to open word file " << filename << endl;
        exit(1);
    }

    cout << "Reading the Dictionary File ..." << endl;

    for (int i = 0; i < DictionarySize; i++)
    {
        fin >> temp;
        toLowerCase(temp);
        dictionary[i] = new char[strlen(temp)+1];
        strcpy(dictionary[i],temp);
    }
}

bool wordIsInDictionary(const char* word,  char** dictionary)
{
    int low, high, middle;
    low = 0;
    high = DictionarySize - 1;

    char middleWord[32];

    int compare;

    while (low <= high)
    {
        middle = (low + high) / 2;
        strcpy(middleWord,dictionary[middle]);
        compare = strcmp(word,middleWord);
        if (compare < 0)
        {
            high = middle - 1;
        }
        else if (compare > 0)
        {
            low = middle + 1;
        }
        else
        {
            return true;
        }
    }
    return false;
}


void toLowerCase(char* text)
{
    for (size_t i = 0; i < strlen(text); i++)
        if (isupper(text[i])) text[i] = tolower(text[i]);
}

void toLowerCase(string& text)
{
    for (size_t i = 0; i < text.size(); i++)
        text[i] = tolower(text[i]);
}

void sort(char* a[])
{
    int minIndex;
    for (int i = 0; i < DictionarySize - 1; i++)
    {
        minIndex = i;
        for (int j = i+1; j < DictionarySize; j++)
        {
            if (strcmp(a[j],a[minIndex]) < 0)
            {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            swap(a[i],a[minIndex]);
        }
    }
}
