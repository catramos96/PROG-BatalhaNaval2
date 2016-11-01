//----------Batalha Naval 2----------//

#include <limits>
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "bomb.h"
#include "ship.h"
#include "board.h"
#include "player.h"
#include "auxiliary.h"
#include "Score.h"

using namespace std;

//=================================================================//
/*
FUNCTION MEANING:
Sends a message to the screen and waits for the user to insert ENTER.
*/

void waitPlayer(string msg)
{
  displayColorMsg(msg, BLACK, WHITE);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//=================================================================//
/*
FUNCTION MEANING:
Displays the game's menu that has the "start game", "how to play" and " " options.

NOTER:
- clrscr() --> clears the screen (defined in auxiliary.cpp)
- displayTextFile --> displays the file content (defined in auxiliary.cpp)
- waitPlayer --> defined in auxiliary.cpp
- gameHeader --> defined in auxiliary.cpp
*/

void gameMenu()
{
	int option;

	do
	{
		clrscr();
    gameHeader();
    displayTextFile("gameMenu.txt");
    cout << "\nYour option: ";
		cin >> option;

		clrscr();

		switch (option)
		{
		case 1:
		{
      gameHeader();
			break;
		}
		case 2:
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
      gameHeader();
			displayTextFile("gameHowToPlay.txt");
      cout << endl << endl;
			waitPlayer("Press ENTER to go back to menu");
			break;
		}
		case 3:
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
      gameHeader();
			displayTextFile("gameInformation.txt");
      cout << endl << endl;
			waitPlayer("Press ENTER to go back to menu");
			break;
		}
		case 4:
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
      gameHeader();
			displayTextFile("Scores.txt");
			cout << endl << endl;
			waitPlayer("Press ENTER to go back to menu");
			break;
		}
		default:
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid option!" << endl;
			waitPlayer("Press ENTER to go back to menu");
			break;
		}
		}
	} while (option != 1);
}

//=================================================================//
/*
FUNCTION MEANING:
This function aks the player's names and boardFiles and associate them to the objects of the class player
player1 and player2 in a random way.

NOTES:
- IsFileText(...) --> Verify if as the ".txt" extension and if not, it will add it automatically (defined in auxiliary.cpp);
- FileFail(...) --> Verify if the board file name is valid and if it will open without any problems. If it's not valid
it will ask again for a new board file name (defined in auxiliary.cpp);
- gameHeader --> defined in auxiliary.cpp
*/

void playersData(Player &player1, Player &player2)
{
	string name1, name2, boardFile1, boardFile2;
	int r = random(0, 1); //random number to choose first player

	cin.ignore();
	cout << "Player name: ";
	getline(cin, name1);
	cout << "BoardFile name: ";
	getline(cin, boardFile1);
	fileFail(boardFile1);

	cout << endl;

	cout << "Player name: ";
	getline(cin, name2);
	cout << "BoardFile name: ";
	getline(cin, boardFile2);
	fileFail(boardFile2);
	cout << endl;

  //Choose a random first player
	if (r == 0)
	{
		cout << "The first player is " << name1 << " and " << name2 << " is the second." << endl << endl;
		player1.setName(name1);
		player1.setBoard(boardFile1);
		player2.setName(name2);
		player2.setBoard(boardFile2);
	}
	else
	{
		cout << "The first player is " << name2 << " and " << name1 << " is the second." << endl << endl;
		player1.setName(name2);
		player1.setBoard(boardFile2);
		player2.setName(name1);
		player2.setBoard(boardFile1);
	}
}

//=================================================================//
/*
FUNCTION MEANING:
This function shows the player's boards

NOTES:
- clrscr() --> clears the screen (defined in auxiliary.cpp)
- waitPlayer(...) defined in auxiliary.cpp
- gameHeader --> define in auxiliary.cpp
*/

void showPlayersBoard(Player player1, Player player2)
{
  gameHeader();

	cout << player1.getName() << endl;
	player1.showBoard();
	cout << endl << player2.getName() << endl;
	player2.showBoard();
	cout << endl;
}

//=================================================================//
/*
FUNCTION MEANING:
This function starts a player's turn.

NOTES:
- displayTextFile(...) defined in auxiliary.cpp
- clrscr() --> clears the screen (defined in auxiliary.cpp)
- waitPlayer(...) defined in auxiliary.cpp
- gameHeader --> define in auxiliary.cpp
*/

void playerTurn(Player &player, Player &playerTarget)
{
	Bomb b;

  gameHeader();

  cout << player.getName() << "'s turn" << endl;
  cout << "\nHere is " << playerTarget.getName() << "'s board:" << endl;
  playerTarget.showBoard();

  cout << endl << "Lets send a bomb to " << playerTarget.getName() << "'s board" << endl;
  if (playerTarget.attackBoard(player.getBomb())) //attack's the oponent board
  {
    //refresh the screen and display the bomb result
    clrscr();
    gameHeader();
    cout << player.getName() << " you hit a ship!" << endl;
  }
  else
  {
    //refresh the screen and display the bomb result
    clrscr();
    gameHeader();
    cout << player.getName() << " you just hit water!" << endl;
  }

  cout << "\nHere is " << playerTarget.getName() << "'s board:" << endl;
  playerTarget.showBoard();
  cout << endl;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
	waitPlayer("Your turn as ended");
  
  clrscr();
}

//=================================================================//
/*
FUNCTION MEANING:
This function ends the game and shows the winner and his/her score.

NOTES:
- gameHeader --> defined in auxiliay.cpp
*/

void endGame(Player player1, Player player2, time_t time)
{
	Player winner;

	if (player1.gameOver())
		winner = player2;
	else if (player2.gameOver())
		winner = player1;

  clrscr;
  gameHeader();

	cout << endl << endl << endl << endl << endl;

	setcolor(YELLOW, BLACK);
	cout << "The winner is " << winner.getName() << "!" << endl << endl;

	Score player(time, winner);

	cout << "Score : " << player.scoreCalculation(time, winner) << endl << endl << endl << endl << endl;

	setcolor(LIGHTCYAN, BLACK);
	displayTextFile("EndOfGame.txt");
	setcolor(LIGHTGRAY, BLACK);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////   MAIN   ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	srand((unsigned)time(NULL));  // seed for random numbers
	windowSize();

	Player player1, player2;
	time_t t1, t2, timeElapsed;

	gameMenu();

	playersData(player1, player2);
	waitPlayer("Press ENTER to continue");

  clrscr();

	showPlayersBoard(player1, player2);
	waitPlayer("These are your boards. Press ENTER to start the game! ");

	clrscr();

	//Starts the game
	t1 = time(NULL);

	int n = 1;
	do
	{
		if (n % 2 != 0)
			playerTurn(player1, player2);
		else
			playerTurn(player2, player1);
		n++;
	} while (!player1.gameOver() && !player2.gameOver());

	//End Game
	t2 = time(NULL);
	timeElapsed = t2 - t1;

	endGame(player1, player2, timeElapsed);

	return 0;
}