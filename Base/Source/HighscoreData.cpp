#include "HighscoreData.h"


HighscoreData::HighscoreData()
	: newScore(0)
	, counter(0)
{
}


HighscoreData::~HighscoreData()
{
}

void HighscoreData::addtheScores(int theScore)
{
	if (counter < 5) // if my counter is not at 5
	{
		scores[counter].addScore(theScore); // add the score in
		counter++;
	}
}

void HighscoreData::MergeHighscore(Highscore list[], int first, int middle, int last)
{
	Highscore* temp = new Highscore[middle - first + 1];
	int i, j, k; // i - temp array, j - 2nd list, k - combine list

	for (j = first, i = 0; j <= middle; i++, j++)
	{
		temp[i] = list[j]; // duplicate the first list(list[]).
	}

	i = 0;
	k = first;
	while (k < j && j <= last)
	{
		if (temp[i].getScore() >= list[j].getScore()) // if the score in i is bigger than the score in j
			list[k++] = temp[i++]; // put i into k
		else // if the score in i is smaller than the score in j
			list[k++] = temp[j++]; // put j into k
	}
	while (k < j)
	{
		list[k++] = temp[i++];
	}

	delete[] temp; // remove the temp array
}

void HighscoreData::MergeSortHighscore(Highscore list[], int first, int last)
{
	if (first < last)
	{
		int middle = (first + last) / 2;
	}
}

