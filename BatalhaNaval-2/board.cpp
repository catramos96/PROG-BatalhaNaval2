#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "board.h"
#include "ship.h"
#include "bomb.h"
#include "auxiliary.h"

using namespace std;

//=================================================================//
/*
FUNCTION MEANING:

default constructor
*/

Board::Board()
{
}

//=================================================================//
/*
FUNCTION MEANING:

constructor
open the text file with all the information about the board and save it at vector ships.
then vector board is filed in with '-1'

FUNCTION PARAMETERS:

- filename: name of the board file introduced
*/

Board::Board(const string &filename)
{
	//open text file ang gets information with stringstreams
	fstream file;
	string shipInformation;
	string trash;
	int k = 0;

	file.open(filename); // open board file

	getline(file, shipInformation);
	istringstream InString(shipInformation);

	// information about board size
	InString >> numLines >> trash >> numColumns;

	// save information about ships in ships vector
	while (!file.eof())
	{
		getline(file, shipInformation); //next line
		istringstream InString(shipInformation);

		char letter, orientation;
		unsigned int length, color;
		Position<char> coordinates;

		// get information from stringstream
		InString >> letter >> length >> coordinates.lin >> coordinates.col >> orientation >> color;

		Ship boat(letter, coordinates, orientation, length, color);	// calls constructor ship
		ships.push_back(boat);	// puts the information about ship in vector ships

		k++;
	}

	file.close(); // close board file

	vector<int> aux; // auxiliar vector that will act like a line of the vector board

	for (int j = 0; j < numColumns; j++) // fill the vector aux with -1
		aux.push_back(-1);

	for (int i = 0; i < numLines; i++) // fill the vector board with vector aux
		board.push_back(aux);

	for (size_t i = 0; i < ships.size(); i++)
		assert(putShip(ships.at(i))); // teminates the program if it's impossible to allocate ships in board
}

//=================================================================//
/*
FUNCTION MEANING:

- returns a struct Position<int> with the boards dimension
*/

Position<int> Board::getBoardDim() const
{
	Position<int> boardDim;

	boardDim.lin = numLines;
	boardDim.col = numColumns;

	return boardDim;
}

//=================================================================//
/*
FUNCTION MEANING:

verifies if ship is in side of bounds and returns false if it does not;
verifies if ship colides with another ship and returns false;

FUNCTION PARAMETERS:

- line: 2D vector 'board' line
- column: 2D vector 'board' column
- shipNumber: ships position in vector 'ships'
*/

bool Board::validateBoatPosition(int line, int column, int shipNumber)
{
	unsigned int size = ships.at(shipNumber).getSize(); // size of the ship
	char ori = toupper(ships.at(shipNumber).getOrientation());
	int outCol = column + size; // last position of the ship (horizontaly)
	int outLin = line + size; // last position of the ship (verticaly)

	if (ori == 'H')
	{
		for (unsigned int i = 0; i < size; i++)
			if (board.at(line).at(column + i) != -1) // verifies if the ship doesn't colide with others (horizontaly)
				return true;

		if (outCol > numColumns) // verifies if ships is out of bounds
			return true;

		else
			return false;
	}

	if (ori == 'V')
	{
		for (unsigned int j = 0; j < size; j++)
			if (board.at(line + j).at(column) != -1) // verifies if the ship doesn't colide with others (verticaly)
				return true;

		if (outLin > numLines)	// verifies if ships is out of bounds
			return true;

		else
			return false;
	}
	else
		return false;
}
//=================================================================//
/*
FUNCTION MEANING:

Finds the ship in vector ships, then calls outOfBounds and return true if outOfBounds also returns true.
Returns false if putInBoard returns false.

FUNCTION PARAMETERS:

- s: object that represents the ship;
*/

bool Board::putShip(const Ship &s)
{
	int newLin = s.getPosition().lin; // line of ship  introduced
	int newCol = s.getPosition().col; // column of ship  introduced

	if (newCol < 0 || newLin < 0 || newCol >= numColumns || newLin >= numLines)// verifies if the ship is out of bounds
		return false;

	for (size_t n = 0; n < ships.size(); n++)	// loop that runs along the vector
	{
		if (newLin == ships.at(n).getPosition().lin && newCol == ships.at(n).getPosition().col) // equivalent positions were found
		{
			if (validateBoatPosition(newLin, newCol, n))
				return false;

			if (s.getOrientation() == 'V')
			{
				for (unsigned int j = 0; j < s.getSize(); j++)
					board.at(newLin + j).at(newCol) = n; // puts ship in the board
				return true;
			}

			else
			{
				for (unsigned int i = 0; i < s.getSize(); i++)
					board.at(newLin).at(newCol + i) = n; // puts ship in the board
				return true;
			}
		}
	}
	return false;
}
//=================================================================//
/*
FUNCTION MEANING:

remove ship from the board

FUNCTION PARAMETERS:

- s: object that represents the ship;

*/

void Board::removeShip(Ship &s)
{
	if (s.getOrientation() == 'V')
		for (unsigned int i = 0; i < s.getSize(); i++)
			board.at(s.getPosition().lin + i).at(s.getPosition().col) = -1; // exchange the number of the boat by '-1'

	else
		for (unsigned int j = 0; j < s.getSize(); j++)
			board.at(s.getPosition().lin).at(s.getPosition().col + j) = -1; // exchange the number of the boat by '-1'
}

//=================================================================//
/*
FUNCTION MEANING:

Moves the fleet randomly
*/

void Board::moveShips()
{
	for (size_t i = 0; i < ships.size(); i++)
	{
		Ship shipAux(ships.at(i)); // object that will save the information about the ship that will be modified

		if (ships.at(i).moveRand(0, 0, numLines, numColumns)) // position is modified
			if (putShip(ships.at(i))) // put the ship on the board
				removeShip(shipAux); // removes the ship with the old position
			
			else // if we can't put ship on the board
			{
				ships.at(i).setPosition(shipAux.getPosition().lin, shipAux.getPosition().col); // old position
				ships.at(i).setOrientation(shipAux.getOrientation()); // old orientation
			}
	}
}

//=================================================================//
/*

FUNCTION MENAING:

this member function receives a bomb and return true if the bomb hit a ship;
this method returns false if the bomb is out of Bounds or hits the sea;

FUNCTION PARAMETERS:

- b: object that represents a bomb
*/

bool Board::attack(const Bomb &b)
{
	int targetLin = b.getTargetPosition().lin - 'A';
	int targetCol = b.getTargetPosition().col - 'a';

	if (targetLin < 0 || targetLin >= numLines || targetCol < 0 || targetCol >= numColumns) // verifies if is out of bounds
		return false;

	int n = board.at(targetLin).at(targetCol); // position of the ship in the vector 'ships'

	if (n != -1) // hits a boat
	{
		size_t partNum = 0; // part of the boat that was hit by a bomb

		if (ships.at(n).getOrientation() == 'V')
		{
			partNum = targetLin - ships.at(n).getPosition().lin;

			if (ships.at(n).isDestroyed())
				return false;
			else
			{
				ships.at(n).attack(partNum);
				return true;
			}
		}
		else
		{
			partNum = targetCol - ships.at(n).getPosition().col;

			if (ships.at(n).isDestroyed())
				return false;
			else
			{
				ships.at(n).attack(partNum);
				return true;
			}
			ships.at(n).attack(partNum);
		}
	}
	else
		return false;
}

//=================================================================//
/*
FUNCTION MEANING:

checks if that position of the board is a ship destroyed (verifies status of that ship);
returns a character in lowe or upper case;

FUNCTION PARAMETERS:

- line: 2D vector 'board' line
- column: 2D vector 'board' column
- shipNumber: ships position in vector 'ships'
*/

char Board::isLow(int line, int column, int shipNumber) const 
{
	int partNumber = 0; // part of ship we want to analize the status
	string status;
	status = ships.at(shipNumber).getStatus();

	if (ships.at(shipNumber).getOrientation() == 'V')
	{
		partNumber = line - ships.at(shipNumber).getPosition().lin; // to know the partNumber we subtract the first position of the ship with the atual position on the board
																	// if orientation is vertical, subtract lines
		if (islower(status[partNumber])) // verifies if status on that position is lower case
			return tolower(ships.at(shipNumber).getSymbol()); // put symbol in lower case
		
		else
			return ships.at(shipNumber).getSymbol();
	}
	
	else
	{
		partNumber = column - ships.at(shipNumber).getPosition().col; // to know the partNumber we subtract the first position of the ship with the atual position on the board
																	//if orientation is horizontal, subtract columns
		if (islower(status[partNumber])) // verifies if status on that position is lower case
			return tolower(ships.at(shipNumber).getSymbol());// put symbol in lower case
		else
			return ships.at(shipNumber).getSymbol();
	}
}

//=================================================================//
/*
FUNCTION MEANING:

this method checks if the fleet is all destroyed
*/

bool Board::allDestroyed()
{
	for (size_t i = 0; i < ships.size(); i++)
		if (!(ships.at(i).isDestroyed()))
			return false;
	return true;
}

//=================================================================//
/*
FUNCTION MEANING:

displays colored board
*/

void Board::display() const
{
	int dec_A = 65;	// code ascii to 'A'
	int dec_a = 97;	// code ascii to 'a'

	cout << setw(2) << " ";

	for (int k = 1; k <= numColumns; k++)	// first line of letters
	{
		char lower = dec_a;	// converts ascii to char
		setcolor(GREEN, BLACK);
		cout << setw(2) << lower; // letters of the columns
		setcolor(LIGHTGRAY, BLACK);
		dec_a++;
	}
	cout << endl;

	for (int i = 0; i < numLines; i++)
	{
		char upper = dec_A;	// ascii to char
		setcolor(GREEN, BLACK);
		cout << setw(2) << upper; //letters of the lines
		setcolor(LIGHTGRAY, BLACK);
		dec_A++;

		for (int j = 0; j < numColumns; j++)
		{
			if (board.at(i).at(j) == -1) // in case of sea, puts '.'
			{
				setcolor(BLUE, LIGHTGRAY);
				cout << setw(2) << '.';
				setcolor(LIGHTGRAY, BLACK);
			}
			else // replace the number by the correspondent symbol
			{
				int n = board.at(i).at(j);

				setcolor(ships.at(board.at(i).at(j)).getColor(), LIGHTGRAY);
				cout << setw(2) << isLow(i,j,n); // calls function 'isLow' that returns the character with lower or upper case in case the boat was attacked
				setcolor(LIGHTGRAY, BLACK);
			}
		}
		cout << endl;
	}
}

//=================================================================//
/*
FUNCTION MEANING:

shows atributes of board (for debugging)
*/

void Board::show() const
{
	cout << "Board: " << numLines << " x " << numColumns << endl; // displays dimension of the board

	for (int i = 0; i < numLines; i++) // displays board with numbers
	{
		cout << endl;
		for (int j = 0; j < numColumns; j++)
			cout << setw(2) << board.at(i).at(j);
	}

	cout << endl;

	for (size_t k = 0; k < ships.size(); k++) // displays atributes of each ship of vector 'ships'
	{
		cout << "Ship " << k << " :" << endl;
		ships.at(k).show();
		cout << endl;
	}
}