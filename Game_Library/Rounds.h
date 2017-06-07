#pragma once
#include "stdafx.h"
#include "Rock.h"

class Rounds {
private:
	int roundNum;
	int rockNum;
	int score;
	bool over;

public:
	Rounds();

	int getRound();
	int getRock();
	int getScore();
	bool getOver();

	void setRound();
	void setRock();
	void setScore();
	void setOver(bool val);
};