#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>
#include <ctime>

const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int BROWN = 6;
const int LIGHTGRAY = 7;
const int DARKGRAY = 8;
const int LIGHTBLUE = 9;
const int LIGHTGREEN = 10;
const int LIGHTCYAN = 11;
const int LIGHTRED = 12;
const int LIGHTMAGENTA = 13;
const int YELLOW = 14;
const int WHITE = 15;

using namespace std;
template <class T>

struct Position
{
	T lin, col;
};

struct playerScore
{
	string name;
	double score;
	double dimTab;
	double areaOfShips;
};

void windowSize();
int random(int min, int max);
void fileFail(string &filename);
void isFileText(string &filename);
void setcolor(unsigned int color, unsigned int background_color);
void clrscr(void);
void warningMsg(string msg);
void displayTextFile(string textfile);
void displayColorMsg(string msg, const int backgroundColor, const int letterColor);
void gameHeader();

#endif