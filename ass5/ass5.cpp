//  Mega Putra / CIS 22B / Assignment 5
//  Compiler : Xcode on MacBook Pro
//
//  Created by Mega Putra on 2/8/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//structure
struct NBA_Team
{
    string name;
    string conference;
    string division;
    unsigned short wins;
    unsigned short losses;
    float pct;
};

//constants
const int NUM_TEAMS = 30;

//function prototypes
void openFile(ifstream&fin, string fileName);
void getScores (ifstream&scoresFile, int&score1, int& score2, string& team1, string& team2, NBA_Team* teamStats);
void getTeamID(ifstream& namesFile, NBA_Team* teamStats);
float calcPct(NBA_Team& teamStats);
float sortKey(NBA_Team& t);
void selectionSort(float* keyArray, const int NUM_TEAMS);
void sortStruct(NBA_Team* teamStats, const int NUM_TEAMS);
void printResults(NBA_Team* teamStats);

int main()
{
    NBA_Team teamStats[NUM_TEAMS];
    ifstream scoresFile, namesFile;
    int score1, score2 = 0;
    string winner = "", loser = "", bufferName, team1, team2;
    
    openFile(scoresFile, "scores.txt");
    getScores(scoresFile, score1, score2, team1, team2, teamStats);
    for (int team = 0; team < NUM_TEAMS; team++){
        teamStats[team].pct = calcPct(teamStats[team]);
    }
    sortStruct(teamStats,NUM_TEAMS);
    printResults(teamStats);
}
/*~~~~~~~~~~~~~ F U N C T I O N  D E F I N I T I O N S ~~~~~~~~~~~~~~~*/
/*---------------------------openFile---------------------------
 This function opens a text file contained in the working directory*/
void openFile(ifstream& fin, string fileName)
{
    fin.open(fileName.c_str());
    if (!fin){
        cerr << "Error opening the file: " << fileName << endl;
        exit(1);
    }
    else{
        cout << fileName << " is opened successfully." << endl;
    }
    
}
/*---------------------------getWinLoseScores---------------------------
 parses the last data of the score and gets the winner and loser scores*/
void getScores (ifstream&scoresFile, int& score1, int& score2, string& team1, string& team2, NBA_Team* teamStats)
{
    ifstream namesFile;
    openFile(namesFile, "team_name.txt");
    getTeamID(namesFile, teamStats);
    
    string buffer, scoreBuffer, winner, loser;
    size_t pos, pos1, tieGame, namePos;
    int i = 0;
    while (!scoresFile.eof())
    {
        if (buffer[buffer.size()-1] == '\r') buffer.resize(buffer.size()-1); //Prof's suggestion
        getline(scoresFile, buffer);
        
        //ignores the tie game
        scoreBuffer = buffer.substr(61, 70);
        if ((tieGame = scoreBuffer.find_first_of('(')) < 70){
            buffer.clear();
            continue; //resets the loop
        }
        //get team names
        team1 = buffer.substr(13,buffer.length());
        namePos = team1.find("  ");
        team1 = team1.substr(0, namePos);
        team2 = buffer.substr(36,buffer.length());
        namePos =team2.find("  ");
        team2 = team2.substr(1, namePos-1);
        
        //get scores
        pos = scoreBuffer.find_first_of(',');
        if (pos <= 3){
            score1 = stoi((scoreBuffer.substr(0,pos)));
        }
        pos1 = scoreBuffer.find_first_of(' ');
        score2 = stoi(scoreBuffer.substr((pos+1),(pos1-1)));
        
        if (score1 > score2){
            winner = team1;
            loser = team2;
        }
        else if(score1<score2){
            winner = team2;
            loser = team1;
        }
        for(int team= 0; team< NUM_TEAMS; team++){
            if(teamStats[team].name == winner){
                teamStats[team].wins++;
            }
            if(teamStats[team].name == loser){
                teamStats[team].losses++;
            }
        }i++;
    }
    scoresFile.close();
}

/*---------------------------getTeamNames---------------------------
 read from file, get the team names and categorize them to divisions*/
void getTeamID(ifstream& namesFile, NBA_Team* teamStats)
{
    string buffer, conference, division;
    size_t pos = 0;
    string conf = "Conference";
    string div = "Division";
    if (buffer[buffer.size()-1] == '\r') buffer.resize(buffer.size()-1);
    int i = 0;
    
    while (!namesFile.eof()){
        getline(namesFile, buffer);
        if((pos = buffer.find(conf)) != string::npos) {
            conference = buffer.substr(0, pos + buffer.length()-1);
        }
        else if((pos = buffer.find(div))!= string::npos) {
            division = buffer.substr(0, pos + buffer.length()-1);
        }
        else if(isalpha(buffer[0])) {
            teamStats[i].name = buffer;
            teamStats[i].conference = conference;
            teamStats[i].division = division;
            teamStats[i].wins = 0;
            teamStats[i].losses = 0;
            teamStats[i].pct = 0.000;
            i++;
        }
    }
    namesFile.close();
}
/*---------------------------sortKey---------------------------
get the key values for each team*/
float sortKey (NBA_Team& t)
{
    int Conf = t.conference[0];
    int Div = t.division[0];
    float pct = t.pct;
    
    return Conf * 100 + Div + pct;
}
/*---------------------------sortStruct---------------------------
sorts the struct for printing*/
void sortStruct(NBA_Team* teamStats, const int NUM_TEAMS)
{
    for (int i = 0; i < NUM_TEAMS - 1; i++){
        for(int j = i + 1; j < NUM_TEAMS; j++){
            if (sortKey(teamStats[i]) < sortKey(teamStats[j])){
                swap(teamStats[i], teamStats[j]);
            }
        }
    }
}
/*--------------------------calcPct---------------------------
calculates the winning percentage of the whole team in the conference*/
float calcPct(NBA_Team& teamStats)
{
    float totalGamesPlayed = 0.0, pct= 0.000;
    totalGamesPlayed =teamStats.wins+teamStats.losses;
    pct = teamStats.wins/totalGamesPlayed;
    
    return pct;
}
/*-------------------------printResults---------------------------
 this function prints the final output*/
void printResults(NBA_Team* teamStats)
{
    int teamPrintCount = 0;

    for(int conf= 0; conf < 2; conf++){
        cout << teamStats[teamPrintCount].conference << "\n\n";
        for (int div = 0; div < 3; div++){
            cout <<  left << setw(23) << teamStats[teamPrintCount].division;
            cout << right << setfill(' ') << setw(2) <<"W";
            cout << right << setfill(' ') << setw(6) << "L";
            cout << right << showpoint << setw(8) << setprecision(3) << "Pct" << endl;
            for (int team = 0; team < 5; team++){
                cout <<  left << setw(23) << teamStats[teamPrintCount].name;
                cout << right << setfill(' ') << setw(2) << teamStats[teamPrintCount].wins;
                cout << right << setfill(' ') << setw(6) << teamStats[teamPrintCount].losses;
                cout << right << showpoint << setw(8) << setprecision(3) << teamStats[teamPrintCount].pct << endl;
                teamPrintCount++;
            }cout << endl;
        }
    }
}
