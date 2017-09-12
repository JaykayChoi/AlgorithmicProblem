/*
ID: jkchoik1
PROG: barn1
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

//http://train.usaco.org/usacoprob2?a=qxjyGzruutH&S=barn1

multimap<int, int> gaps;
vector<int> occupiedStalls;


int calcNeedBoards()
{
	sort(occupiedStalls.begin(), occupiedStalls.end());

	int serialNumber = 0;
	int ret = 1;
	for (vector<int>::iterator it = occupiedStalls.begin(); it != occupiedStalls.end(); it++)
	{
		if (serialNumber == 0)
			serialNumber = *it;
		else if (*it == serialNumber + 1)
			serialNumber = *it;
		else
		{
			serialNumber = *it;
			ret++;
		}
	}
	return ret;
}

int repairBarn(int maxNumBoards)
{
	if (occupiedStalls.size() <= maxNumBoards)
		return occupiedStalls.size();

	if (calcNeedBoards() == maxNumBoards)
		return occupiedStalls.size();

	for (multimap<int, int>::iterator it = gaps.begin(); it != gaps.end(); it++)
	{
		for (int i = 0; i < it->first; i++)
			occupiedStalls.push_back(it->second + i);

		if (calcNeedBoards() == maxNumBoards)
			return occupiedStalls.size();
	}
}

int sub_main()
{
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");

	int maxNumBoards, totalStalls, numCows;
	fin >> maxNumBoards >> totalStalls >> numCows;

	for (int i = 0; i < numCows; i++)
	{
		int stall;
		fin >> stall;
		occupiedStalls.push_back(stall);
	}
	sort(occupiedStalls.begin(), occupiedStalls.end());
	int serialNumber = 0;
	for (vector<int>::iterator it = occupiedStalls.begin(); it != occupiedStalls.end(); it++)
	{
		if (serialNumber == 0)
			serialNumber = *it;
		else if (*it == serialNumber + 1)
			serialNumber = *it;
		else
		{
			int gap = *it - serialNumber - 1;
			gaps.insert(make_pair(gap, *it - gap));
			serialNumber = *it;
		}
	}

	fout << repairBarn(maxNumBoards) << endl;

	return 0;
}
