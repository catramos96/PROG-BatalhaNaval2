#include <iostream>
#include "auxiliary.h"
#include "bomb.h"

using namespace std;

//=================================================================//
/*
FUNCTION MEANING:

Default Constructor
*/

Bomb::Bomb()
{
}

//=================================================================//
/*
FUNCTION MEANING:

Constructor.
receives the coordinates and choose randomly the new target 
*/

Bomb::Bomb(Position<char> targetPosition)
{
	int line = targetPosition.lin - 'A';
	int column = targetPosition.col - 'a';

	line = line + random(-1, 1);
	column = column + random(-1, 1);

	targetColumn = column + 'a';
	targetLine = line + 'A';
}

//=================================================================//
/*
FUNCTION MEANING:

get the position of the target
*/

Position<char> Bomb::getTargetPosition() const
{
	Position<char> bomb;

	bomb.lin = targetLine;
	bomb.col = targetColumn;

	return bomb;
}

//=================================================================//
/*
FUNCTION MEANING:

Shows the new coordinates of the bomb 
*/

void Bomb::show() const
{
	cout << targetLine << " " << targetColumn << endl;
}