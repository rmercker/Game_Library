#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>


class HighScore {
private:
	std::string** high_Score;

public:
	HighScore();
	void highScore();
	std::string printHigh(int i, int j);
	bool determineHigh(int score);
	void newHigh(std::string name, int score);
};