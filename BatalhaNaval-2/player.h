#ifndef PLAYER_H	// impede que inclua varias vezes as mesmas header files
#define PLAYER_H

#include <string>
#include "board.h"
#include "bomb.h"

using namespace std;

class Player
{
public:
	Player();
	Player(string playerName, string boardFilename);
  void showBoard() const; // shows the player’s board
  Bomb getBomb() const;	// asks bomb target coordinates and creates the bomb
  bool attackBoard(const Bomb &b);
	void setName(string playerName);
	void setBoard(string boardFilename);
	string getName();
	string getBoardFileName();
	bool gameOver();
private:
	string name;//name of the player
	string boardFileName;
	Board board;// board of the player
};
#endif