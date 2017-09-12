/*
ID: jkchoik1
PROG: holstein
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

//http://jaykaychoi.tistory.com/71

int numV, numG;
vector<int> vitaminRequirements;
vector<vector<int>> feeds;
set<int> ret;

bool whetherMeetVitaminRequirements(const vector<int>& fedVitamins)
{
	for (int i = 0; i < numV; i++)
	{
		if (fedVitamins[i] < vitaminRequirements[i])
			return false;
	}
	return true;
}

void feed(vector<int>& fedVitamins, int type, bool isSubtraction)
{
	for (int i = 0; i < numV; i++)
	{
		int vitamins = feeds[type][i];
		if (isSubtraction)
			vitamins *= -1;
		fedVitamins[i] += vitamins;
	}
}

set<int> chooseFeedType(vector<int>& fedVitamins, set<int>& feedingOrder)
{
	if (whetherMeetVitaminRequirements(fedVitamins))
		return feedingOrder;


	for (int i = 0; i < numG; i++)
	{
		set<int>::iterator it = feedingOrder.find(i);
		if (it != feedingOrder.end())
			continue;
		if (ret.empty() == false && feedingOrder.size() > ret.size())
			return ret;
		if (feedingOrder.empty() == false)
		{
			set<int>::iterator it = feedingOrder.end();
			it--;
			if (i < *it)
				continue;
		}
		feedingOrder.insert(i);
		feed(fedVitamins, i, false);
		set<int> candidate = chooseFeedType(fedVitamins, feedingOrder);
		if (ret.empty() || candidate.size() < ret.size())
			ret = candidate;
		feed(fedVitamins, i, true);
		feedingOrder.erase(i);
	}
	return ret;
}

int main()
{
	ifstream fin("holstein.in");
	ofstream fout("holstein.out");


	fin >> numV;

	for (int i = 0; i < numV; i++)
	{
		int num;
		fin >> num;
		vitaminRequirements.push_back(num);
	}

	fin >> numG;

	for (int i = 0; i < numG; i++)
	{
		vector<int> temp;
		for (int i = 0; i < numV; i++)
		{
			int num;
			fin >> num;
			temp.push_back(num);
		}
		feeds.push_back(temp);
	}

	vector<int> temp1(numV, 0);
	set<int> temp2;
	set<int> ret = chooseFeedType(temp1, temp2);

	fout << ret.size();
	for (set<int>::iterator it = ret.begin(); it != ret.end(); it++)
		fout << " " << *it + 1;
	fout << endl;


	fin.close();
	fout.close();
	return 0;
}