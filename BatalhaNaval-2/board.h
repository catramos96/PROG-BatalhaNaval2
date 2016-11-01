#ifndef BOARD_H	
#define BOARD_H

#include <vector>
#include <string>
#include "ship.h"
#include "bomb.h"

using namespace std;

class Board
{
public:
	Board();
	Board(const string &filename); // loads board from file 'filename'
	vector<Ship> getShips() const;
	bool validateBoatPosition(int line, int column, int shipNumber);		//NEW
	char isLow(int line, int column, int shipNumber) const;		//NEW
	bool putShip(const Ship &s); // adds ship to the board, if possible
	void removeShip(Ship &s);		//NEW
	void moveShips();// tries to randmonly move all the ships of the fleet
	bool attack(const Bomb &b);
	bool allDestroyed();
	void display() const;//  displays the colored board during the game
	Position<int> getBoardDim() const;
	void show()const;// shows the attributes of the board(for debugging)
private:
	int numLines, numColumns;
	vector<Ship> ships;// ships that are placed on the board
	vector<vector<int>> board;	// each element indicates the index of a ship in the 'ships'
								// -1 is the sea
};
#endif