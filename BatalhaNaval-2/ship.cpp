#include "ship.h"
#include "auxiliary.h"
#include <iostream>
#include <string>

using namespace std;

//=================================================================//
/*
FUNCTION MEANING:
This function is a constructor of the class Ship.
*/

Ship::Ship(char symbol, Position<char> position, char orientation, unsigned int size,
  unsigned int color)
{
	int lin = int(toupper(position.lin)) - 'A'; //to prevent errors
	int col = int(tolower(position.col)) - 'a';

  this->symbol = toupper(symbol);
  this->position.lin = lin;
  this->position.col = col;
  this->orientation = toupper(orientation);
  this->size = size;
  this->color = color;

  //Status
  for (size_t i = 0; i < size; i++)
  {
    status.push_back(symbol);
  }
};

//=================================================================//
/*
FUNCTION MEANING:
This function returns a boolean about if the movement was possible or not. If it's possible, it will return true and moves
the ship, if not, it will not move the ship and returns false.

FUNCTION:
- saves the new atributes of the ship in new variables (to mantain the actual atributes of the ship);
- verify if the ship's new atributes are between the limits (using function overBoard);
- if overboard returns true, the ship's atributes stay the same (ship don't move), if returns false, it will
  replace them for the new atributes (ship moves);
*/

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{
  Position<int> newPosition;
  char newOrientation = orientation;

  direction = toupper(direction);

  //Saves the new position in the struc newPosition, depending on the direction (N/S/E/W)
  switch (direction)
  {
  case 'N':
  {
    newPosition.lin = position.lin - 1;
    newPosition.col = position.col;
    break;
  }
  case 'S':
  {
    newPosition.lin = position.lin + 1;
    newPosition.col = position.col;
    break;
  }
  case 'E':
  {
    newPosition.lin = position.lin;
    newPosition.col = position.col + 1;
    break;
  }
  case 'W':
  {
    newPosition.lin = position.lin;
    newPosition.col = position.col - 1;
    break;
  }
  default: //If we don't want to move it 
  {
    newPosition.lin = position.lin;
    newPosition.col = position.col;
  }
  }

  //If rotate is switch on, we save in newOrientation the contrary of the actual orientation
  if (rotate)
  {
    if (newOrientation == 'V')
      newOrientation = 'H';
    else
      newOrientation = 'V';
  }

  //Calls overBoard to see if the new coordinates don't cross over the board and if they don't, we refresh 
  //the ship's coordinhates with this new ones in the struct newPosition
  if (!overBoard(newPosition,newOrientation,lineMin,columnMin,lineMax,columnMax))
  {
    setPosition(newPosition.lin, newPosition.col);
    setOrientation(newOrientation);
    return true;
  }
  else
	 return false;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns a boolean about if the random movement was possible or not. If it's possible, it will return true and moves
the ship with the random specifications, if not, it will not move the ship and returns false.

FUNCTION:
- Creates two random variables and associate them to the random direction and random rotation variables (without changing the ship's atributes);
- Call's the function move and returns the bool. The move function will be called with the random direction, the random rotation and with the 
  same 4 parameters as the moveRand function (lineMin, columnMin, lineMax, columnMax). 
*/

bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{
  int randDirection = random(0,4);		
  int randRotate = random(0,1);		
  char direction = 'O';
  bool rotate;


  //Choose a random direction
  switch (randDirection)
  {
  case 0:
  {
    direction = 'N';
    break;
  }
  case 1:
  {
    direction = 'E';
    break;
  }
  case 2:
  {
    direction = 'S';
    break;
  }
  case 3:
  {
    direction = 'W';
    break;
  }
  case 4:
  {
    direction = 'O'; //No direction
    break;
  }
  }

  //Choose a random orientation
  if (randRotate == 0)
    rotate = false;
  else
    rotate = true;

  //Calls the move function with the random direction and rotation and returns his value
  return Ship::move(direction, rotate, lineMin, columnMin, lineMax, columnMax);
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns a bool about if the ship was attacked or not. If the partNumber is between [0 , size - 1] it will be considerated
as the ship's cell in the position 'x' (= partNumber). If this condition is verified, the ship will be striked in this position and the 
ship's symbol will be turn to lower also in the same position (we can see this in the ship's status).
*/

bool Ship::attack(size_t partNumber)
{
  if (partNumber >= 0 && partNumber < size)
  {
    if (islower(status[partNumber]))
      return false;    
    status[partNumber] = tolower(symbol);
    return true;
  }
  else
    return false;
 }

//=================================================================//
/*
FUNCTION MEANING:
This function returns a boolean about if at least half of the ship is destroyed (by analysing the ship's status).
*/

bool Ship::isDestroyed() const
{
  double partsDestroyed = 0;//number of destroyed parts of the ship
  double destroyedPercentage; 

  //Count the number of destroyed parts
  for (size_t i = 0; i < size; i++)
  {
    if (islower(status[i]))
      partsDestroyed = partsDestroyed + 1;
  }
  //Verify if at least 50 % of the ship's cells are destroyed
  destroyedPercentage = partsDestroyed / size;
  if (destroyedPercentage >= 0.50)
    return true;
  else
    return false;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns a boolean about if the ship is between the limits (parameters).
*/

bool Ship::overBoard(Position<int> position, char orientation, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{
  unsigned int outLin = size + position.lin;
  unsigned int outCol = size + position.col;

  if (position.lin < lineMin || position.col < columnMin || position.lin >= lineMax || position.col >= columnMax)
    return true;

  if (orientation == 'V' && outLin > lineMax)
    return true;

  if (orientation == 'H' && outCol > columnMax)
    return true;

  else
    return false;
}

//=================================================================//
/*
FUNCTION MEANING:
This function show's the ship's atributes.
*/

void Ship::show() const	
{
	char lin = position.lin + 'A';	
	char col = position.col + 'a';	

  cout <<
    "Symbol: " << symbol << endl <<
    "Line: " << lin << endl <<
    "Column: " << col << endl <<
    "Orientation: " << orientation << endl <<
    "Size: " << size << endl <<
    "Color code: " << color << endl << 
    "Status: " << status << endl;
}

//=================================================================//
/*
FUNCTION MEANING:
This function change the position of the ship
*/

void Ship::setPosition(int lin, int col)
{
	position.lin = lin;
	position.col = col;
}

//=================================================================//
/*
FUNCTION MEANING:
This function change the orientation of the ship
*/

void Ship::setOrientation(char ori)
{
	orientation = ori;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the ship's symbol
*/

char Ship::getSymbol() const
{
	return symbol;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the ship's position struct;
*/

Position<int> Ship::getPosition() const
{
	return position;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the ship's orientation.
*/

char Ship::getOrientation() const
{
	return orientation;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the ship's size.
*/

unsigned int Ship::getSize() const
{
	return size;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the ship's color.
*/

unsigned int Ship::getColor() const
{
	return color;
}

//=================================================================//
/*
FUNCTION MEANING:
This function returns the ship's status.
*/

string Ship::getStatus() const
{
	return status;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TO TEST THE CLASS 
/*

string resp;
char d, symbol, orient;
int color, size, rsp;
bool r = true;
Position<char> positionShip;

cout << "Lets build you a new Ship! " << endl;
cout << "Symbol? ";
cin >> symbol;
cout << "Position Line? ";
cin >> positionShip.lin;
cout << "Position Column? ";
cin >> positionShip.col;
cout << "Orientation? ";
cin >> orient;
cout << "Size? ";
cin >> size;
cout << "Color code? ";
cin >> color;

Ship ship(symbol, positionShip, orient, size, color);
ship.show();
cout << endl;
do
{
cout << "(1) - Move \n(2) - Attack \n(2)" << endl;
cin >> rsp;

switch (rsp)
{
case 1:
{
cout << "Move ou moverand?" << endl;
cin >> resp;
if (resp == "move")
{
cout << "direction: ";
cin >> d;
cout << "rotate: ";
cin >> resp;
if (resp == "yes")
r = true;
else
r = false;
ship.move(d, r, 0, 0, 20, 20);
}
else
ship.moveRand(0, 0, 20, 20);
cout << endl;
break;
}
case 2:
{
cout << "Select a part number: ";
cin >> rsp;
ship.attack(rsp);
if (ship.isDestroyed())
cout << "Ship destroyed! " << endl;
break;
}
}

ship.show();
cout << endl;
cout << "So you want to exit ?";
cin >> resp;
} while (resp != "yes");

return 0;
*/