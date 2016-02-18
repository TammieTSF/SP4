#include "Highscore.h"

Highscore::Highscore()
{
}


Highscore::~Highscore()
{
}

void Highscore::addScore(int newScore)
{
	this->newScore = newScore;
}

int Highscore::getScore()
{
	return newScore;
}