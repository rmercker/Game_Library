#include "stdafx.h"
#include "Rounds.h"

Rounds::Rounds() { // starts with round 1 and controlls number of rocks
	roundNum = 1;
	rockNum = 0;
	score = 0;
	bool over = false;
}

int Rounds::getRound() { // returns round number
	return roundNum;
}

int Rounds::getRock() { // returns number of rocks
	return rockNum;
}

int Rounds::getScore() { // returns current score
	return score;
}

bool Rounds::getOver() { // used to check if round is over
	return over;
}

void Rounds::setRock() { // sets number of rocks each round based on last round and randon
	rockNum += 1 + rand() % 10;
}

void Rounds::setRound() { // sets the round number to initiate new round
	roundNum++;
}

void Rounds::setScore() { // sets score
	score += roundNum * 10;
}

void Rounds::setOver(bool val) { // is round over
	over = val;
}