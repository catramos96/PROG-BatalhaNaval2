#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h> 
#include "auxiliary.h"

//=================================================================//
/*
FUNCTION MEANING:
This function modifies the console's dimensions.
*/

void windowSize()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 800, 600, TRUE); // 800 width, 600 height
}

//=================================================================//
/*
FUNCTION MEANING:
This function choose a number randomly between 2 numbers (min and max)
*/

int random(int min, int max)
{
	return min + rand() % (max - min + 1);
}

//=================================================================//
/*
FUNCTION MEANING:
This function verifies if the file is a text file. Displays an error message if the file does not have a '.txt' extension or
if the extension is poorly written, adds the extension '.txt'.
*/

void isFileText(string &fileName)
{
	int point; // position of '.'
	string txt; // substring

	point = fileName.find_last_of(".");

	if (point == string::npos) // '.' isn´t reached
	{
    warningMsg("The text file does not have the extension '.txt' so it has been automatically added."); 
    fileName = fileName + ".txt"; // return text file with the '.txt' extension
	}
	else
	{
		txt = fileName.substr(point, fileName.length() - 1); // this string contains the extension of the file the user wrote

		if (txt != ".txt") //checks if the extension is not equals to '.txt'
		{
			fileName.erase(point); // removes that extension
      warningMsg("The text file does not have the extension '.txt' so it has been automatically added."); 
      fileName = fileName + ".txt"; // return text file with the '.txt' extension
		}
	}
}

//=================================================================//
/*
FUNCTION MEANING:

Recieves a file name and verify if it can be open. If not, calls the function 
isFileText and adds ".txt" if it's missing. Then check if the file can be open
again. If not, asks the player to input another file name until is a valid name.

PARAMETERS:

- fileName (string)
*/

void fileFail(string &fileName)
{
	fstream file;

  isFileText(fileName);
  file.open(fileName);

	while (file.fail()) // verifies if file is open 
	{
    file.close();
    warningMsg("The file does not exist!");
    cout << "Introduce your choice again : ";
    cin.clear();
    getline(cin, fileName); // Introduce the new file text
    isFileText(fileName);
    file.open(fileName); // open it again
	}

	file.close();
}

//=================================================================//
/*
FUNCTION MEANING:
- Change the color of the letter and the background.
*/

void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

//=================================================================//
/*
FUNCTION MEANING:
Clears the screen
*/

void clrscr(void)
{
  COORD coordScreen = { 0, 0 }; // upper left corner
  DWORD cCharsWritten;
  DWORD dwConSize;
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hCon, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  // fill with spaces
  FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
  GetConsoleScreenBufferInfo(hCon, &csbi);
  FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
  // cursor to upper left corner
  SetConsoleCursorPosition(hCon, coordScreen);
}

//=================================================================//
/*
FUNCTION MEANING:
Displays in the screen a warning mensage
*/

void warningMsg(string msg)
{
  displayColorMsg("\nWARNING", BLACK, RED);
  cout << msg << endl;
}

//=================================================================//
/*
FUNCTION MEANING:
Displays the text file containt.
*/

void displayTextFile(string textfile)
{
  fstream file;
  string information;

  file.open(textfile);

  //If the file does not exist or is in another folder
  if (file.fail())
  {
    setcolor(RED, BLACK);
    warningMsg("");
    cout << textfile << " is missing!" << endl;
    setcolor(LIGHTGRAY, BLACK);
    exit(1);
  }

  while (!file.eof())
  {
    getline(file, information);
    cout << information << endl;
  }
}

//=================================================================//
/*
FUNCTION MEANING:
Displays in the screen a colorful mensage

NOTES:
- setcolor --> Change the background and letter color (defined in auxiliary.cpp)
*/

void displayColorMsg(string msg, const int backgroundColor, const int letterColor)
{
  setcolor(letterColor, backgroundColor);
  cout << msg << endl;
  setcolor(LIGHTGRAY, BLACK);
}

//=================================================================//
/*
FUNCTION MEANING:
Displays in the screen the game header

NOTES:
- setcolor --> Change the background and letter color (defined in auxiliary.cpp)
*/

void gameHeader()
{
  setcolor(LIGHTCYAN, BLACK);
  displayTextFile("gameHeader.txt");
  setcolor(LIGHTGRAY, BLACK);
}