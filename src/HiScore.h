#pragma once

#include <vector>

class HiScore
{
public:
	HiScore();
	~HiScore();
	static std::vector<int>* HiScore::readScoresFromFile();
	static void writeScoreToFile(int score);
	//static std::vector<int>* HiScore::sortScoreArray(vector<int>* arr, int length);
};

