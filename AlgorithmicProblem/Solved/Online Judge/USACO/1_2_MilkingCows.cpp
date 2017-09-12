/*
ID: jkchoik1
PROG: milk2
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

//http://train.usaco.org/usacoprob2?a=2SmqCnVm4ca&S=milk2

int sub_main()
{
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");

	int N;
	multimap<int, int> farmers;

	fin >> N;

	for (int i = 0; i < N; i++)
	{
		int start, end;
		fin >> start >> end;
		farmers.insert(make_pair(start, end));
	}



	int longestContinuousTtime = 0;
	int longestIdleTime = 0;

	int start = 0;
	int end = 0;

	for (multimap<int, int>::iterator it = farmers.begin(); it != farmers.end(); it++)
	{
		if (it->first >= start && it->first <= end)
		{
			if (it->second > end)
				end = it->second;
		}
		else
		{
			if (end != 0)
				longestIdleTime = max(longestIdleTime, it->first - end);
			start = it->first;
			end = it->second;
		}

		longestContinuousTtime = max(longestContinuousTtime, end - start);
	}

	fout << longestContinuousTtime << " " << longestIdleTime << endl;

	return 0;
}

