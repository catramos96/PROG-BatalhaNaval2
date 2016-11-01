#include <string>
#include <iostream>
#include "bomb.h"
#include "board.h"
#include "player.h"
#include "auxiliary.h"

using namespace std;

//=================================================================//
/*
FUNCTION MEANING:
Default constructor of the class Player.
*/

Player::Player()
{
}

//=================================================================//
/*
FUNCTION MEANING:
This function is a constructor of the class Player;
*/

Player::Player(string playerName, string boardFilename) 
{
  name = playerName;
  this->boardFileName = boardFilename;
  Board b(boardFilename);
  board = b;
}

//=================================================================//
/*
FUNCTION MEANING:
This function shows the player's board.
*/

void Player::showBoard() const
{
  board.display();
}

//=================================================================//
/*
FUNCTION MEANING:
This function asks bomb target coordinates and if they are between the board's limits it creates the bomb aiming at those coordinates.

NOTES:
- board.getBoardDim() --> returns Position<int> with the board's dimension (defined in board.cpp)
*/

Bomb Player::getBomb() const
{
  Position<char> bombTarget;
  Position<int> boardDim = board.getBoardDim();

  //Limits of the board
  int lineMin = 65;	// code ascii to 'A'
  int colMin = 97;	// code ascii to 'a'
  int lineMax = 64 + boardDim.lin;
  int colMax = 96 + boardDim.col;

  do
  {
    cout << "Target Coordinates (line, column): ";
    cin >> bombTarget.lin >> bombTarget.col;

    bombTarget.lin = toupper(bombTarget.lin); //just in case ... 
    bombTarget.col = tolower(bombTarget.col);

    int bombLin = bombTarget.lin;
    int bombCol = bombTarget.col;

    if (!(
      (bombLin >= lineMin) &&
      (bombLin <= lineMax) &&
      (bombCol >= colMin) &&
      (bombCol <= colMax)
      ))//validate the bomb between board's limits
      warningMsg("The coordinates you choose are not valid!");
    else
      break;

  } while (true);

  Bomb bomb(bombTarget);

  return bomb;
}

//=================================================================//
/*
FUNCTION MEANING:
This function recieves a bomb from the oponent and before attack, the player moves his/her ships in a random way.

NOTES:
- board.moveShips(...) --> moves the ships of the player's board in a random way (defined
in board.cpp)
- board.attack(...= --> attacks the board with the bomb and returns a bool about if the bomb
hit a ship (defined in board.cpp)
*/

bool Player::attackBoard(const Bomb &b)
{
  board.moveShips();
  return board.attack(b);
}

//=================================================================//
/*
FUNCTION MEANING:
This function change the player's name.
*/

void Player::setName(string playerName)
{
  name = playerName;
}

//=================================================================//
/*
FUNCTION MEANING:
This function change the player's board.
*/

void Player::setBoard(string boardFilename)
{
	this->boardFileName = boardFilename;
	Board b(boardFilename);
	board = b;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the player's name.
*/

string Player::getName()
{
  return name;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the player's board file.
*/

string Player::getBoardFileName()
{
	return boardFileName;
}

//=================================================================//
/*
FUNCTION MEANING:
This method returns true if the fleet is all destroyed
*/

bool Player::gameOver()
{
	if (board.allDestroyed())
		return true;
	else
		return false;
}



//Testing Class Player
/*
string name1, board1, name2, board2;

cout << "Player's 1 name: ";
cin >> name1;
cout << "BoardFile name: ";
cin >> board1;

cout << endl;

cout << "Player's 2 name: ";
cin >> name2;
cout << "BoardFile name: ";
cin >> board2;
cout << endl;

Player player1(name1, board1);
Player player2(name2, board2);

cout << "Player 1" << endl;
player1.showBoard();
cout << endl;
cout << "Player 2" << endl;
player2.showBoard();


cout << "Player 1" << endl;
Bomb b = player1.getBomb();
player2.attackBoard(b);
cout << "Player 2 board" << endl;
player2.showBoard();

return 0;
*/