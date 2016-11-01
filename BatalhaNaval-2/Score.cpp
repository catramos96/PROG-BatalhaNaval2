#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Score.h"
#include "auxiliary.h"

using namespace std;

//=================================================================//
/*
FUNCTION MEANING:

constructor.
open the text file "scores.txt" and extracts the information to 'top10' vector.
calls the function scoreCalculation and bublesort.
cleans the text file "scores.txt" and then rewrite the information stored in 'top10' vector

FUNCTION PARAMETERS:

- timeElapsed: time that the game tajes to finish
- playerName: name of the winner
- boardFile: name of the board file that the winner choose i the beginning of the game
*/

Score::Score(time_t timeElapsed, Player &player)
{
	ofstream fileout;
	ifstream filein;
	string information, trash;
	string fileScore = "Scores.txt";
	top10.clear();

	//______________________________________________________________

	filein.open(fileScore);		//tries to open the file "Scores.txt"

	if (!filein.fail())		// extract information, just in case of file exists
	{
		playerScore temp;
		getline(filein, information);		// ignores first information (col header)

		while (!filein.eof())
		{
			getline(filein, information);	//next line of information (first with scores)
			istringstream InString(information);
			string name;
			double score, dimTab, shipsArea;

			InString >> trash >> name >> score >> dimTab >> shipsArea;
	
			// extract the information and store's it at the struct playerScore
			temp.name = name;
			temp.score = score;
			temp.dimTab = dimTab;
			temp.areaOfShips = shipsArea;
			//store this information in the vector
			top10.push_back(temp);
		}
	}
	filein.close();

	//______________________________________________________________
	// erase the file
	fileout.open(fileScore);

	fileout.close();
	//______________________________________________________________
	

	// rewrite update version of scores
	fileout.open(fileScore);

	scoreCalculation(timeElapsed, player);	// score of the atual game
	bublesort(top10);	// sort the vector and erase the last score

	int n = 1;
	fileout << setw(15) << "Position" << setw(15) << "Player Name" << setw(15) << "Score" << setw(15) << "Board Area" << setw(15) << "Ships Area";
	
	for (size_t i = 0; i < top10.size(); i++)
	{
		fileout << endl;
		fileout << setw(15) << n << setw(15) << top10.at(i).name << setw(15) << top10.at(i).score << setw(15) << top10.at(i).dimTab << setw(15) << top10.at(i).areaOfShips;
		n++;
	}

	fileout.close();
}

//=================================================================//
/*
FUNCTION MEANING:

This method open's the board file associated with the player and extracts the dimensions of the board and the total area ocupied by the ships.
Then, make the calculations of the score, and save all the information at 'playerScore' struct.
this struct it's added to 'top10' vector.
This method returns the actual score of the winner.

FUNCTION PARAMETERS:

- timeElapsed: time that the game tajes to finish
- playerName: name of the winner
- boardFile: name of the board file that the winner choose i the beginning of the game
*/

double Score::scoreCalculation(time_t timeElapsed, Player &player)
{
	fstream file;
	string information, trash;
	double shipsArea = 0, tabArea = 0, numLines, numColumns, length;
	
	playerScore newScore;

	//______________________________________________________________

	file.open(player.getBoardFileName()); // open board file

	getline(file, information);

	istringstream InString(information);

	// information about board size
	InString >> numLines >> trash >> numColumns;

	tabArea = numColumns * numLines;

	//calculate area occupied by the ships
	while (!file.eof())
	{
		getline(file, information); //next line
		istringstream InString(information);

		// get information from stringstream
		InString >> trash >> length >> trash >> trash >> trash;

		shipsArea = shipsArea + length;
	}

	file.close(); // close board file

	//new information about our player score
	newScore.dimTab = tabArea;
	newScore.name = player.getName();
	newScore.areaOfShips = shipsArea;
	newScore.score = (timeElapsed * (shipsArea / tabArea));

	top10.push_back(newScore);

	return newScore.score;
}
/*
FUNCTION MEANING:

method that sorts the vector of scores and erase the last score (if vector > 10)

FUNCTION PARAMETERS:

-vector top10: private member that stores all the scores
*/

void Score::bublesort(vector<playerScore> &top10)
{
	bool flag = true; // avoid uncessary iteractions

	for (size_t k = top10.size() - 1; k >= 1; k--) // runs the vector from the last element to the first
	{
		for (size_t i = 0; i < k; i++)	// swaps disordely elements until reach that element
		{
			if (top10.at(i).score > top10.at(i + 1).score) // swap 2 elements
			{
				flag = false; // flag is false when we swap 2 elements

				playerScore temp = top10.at(i);
				top10.at(i) = top10.at(i + 1);
				top10.at(i + 1) = temp;
			}
		}
		if (flag)
			break;
	}
	if (top10.size() > 10)		// if the length of the vector is > 10, erase the last element
		top10.erase(top10.end() - 1);
}