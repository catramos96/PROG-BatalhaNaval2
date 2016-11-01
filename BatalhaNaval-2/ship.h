#ifndef SHIP_H	
#define SHIP_H

#include <string>
#include "auxiliary.h"

using namespace std;

class Ship
{
public:
	Ship(char symbol, Position<char> position, char orientation, unsigned int size, unsigned int color);
	bool move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax);
	bool moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax);
	bool attack(size_t partNumber);
	bool isDestroyed() const;
  bool Ship::overBoard(Position<int> position, char orientation, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax);
	char getSymbol() const;
	Position<int> getPosition() const;
	unsigned int getSize() const;
	char getOrientation() const;
	unsigned int getColor() const;
  string getStatus() const;
  void setPosition(int lin, int col);
  void setOrientation(char ori);
	void show() const;

private:
	char symbol;
	Position<int> position;
	char orientation;
	unsigned int size;
	unsigned int color;
	string status;

};
#endif