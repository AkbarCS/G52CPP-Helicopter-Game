#include "HiScore.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

HiScore::HiScore()
{
}


HiScore::~HiScore()
{
}

std::vector<int>* HiScore::readScoresFromFile()
{
	std::ifstream infile("scores.txt");

	int a;

	std::vector<int>* arr = new std::vector<int>();

	//get size of array
	while (infile >> a)
		{
			arr->push_back(a);
		}

	infile.close();

	printf("value of length is %d\n", arr->size());

	sort(arr->rbegin(), arr->rend());

	return arr;
}

void HiScore::writeScoreToFile(int score)
{
	ofstream file("scores.txt", ios::app);		// open filename.txt in append mode
	file << score << endl;						// append the score to the end of the file
	file.close(); 
	printf("score written\n");
}