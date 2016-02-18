#pragma once
#include "Highscore.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class HighscoreData
{
private:
	int counter; // to count where the loop is currently at
	int newScore; // variable for the new score.

	Highscore scores[5]; // Make the array of scores, 5 is the limit

public:
	HighscoreData();
	~HighscoreData();

	void addtheScores(int theScore); // add the score

	void MergeHighscore(Highscore list[], int first, int middle, int last);
	void MergeSortHighscore(Highscore list[], int first, int last);


	void PrintHighscore();
};

