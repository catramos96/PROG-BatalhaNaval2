#ifndef SCORE_H	// impede que inclua varias vezes as mesmas header files
#define SCORE_H


#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "auxiliary.h"
#include "player.h"

using namespace std;

class Score
{
public:
	Score(time_t timeElapsed, Player &player);
	double scoreCalculation(time_t timeElapsed, Player &player);
	void bublesort(vector<playerScore> &top10);
private:
	vector<playerScore> top10;
};

#endif