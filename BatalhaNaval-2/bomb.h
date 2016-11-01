#ifndef BOMB_H	// prevents add several times the same header files
#define BOMB_H

#include "auxiliary.h"

using namespace std;

class Bomb
{
public:
  Bomb();
	Bomb(Position<char> targetPosition);
	Position<char> getTargetPosition() const;
	void show() const; // shows the atributes of the bomb
private:
	char targetLine, targetColumn;
};
#endif