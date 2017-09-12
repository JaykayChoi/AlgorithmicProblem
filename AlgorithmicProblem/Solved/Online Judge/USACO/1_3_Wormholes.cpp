/*
ID: jkchoik1
PROG: wormhole
LANG: C++11
*/
//http://jaykaychoi.tistory.com/42

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Pos
{
	int x, y;
	Pos(int _x, int _y) : x(_x), y(_y) {}
};

int n;
map<int, int> wormholeOnRight;
map<int, int> pairs;

bool isThereInfiniteCycle()
{
	for (int i = 0; i < n; i++)
	{
		bool ret = true;
		int bessie = i;
		for (int j = 0; j < n; j++)
		{
			map<int, int>::iterator it = wormholeOnRight.find(pairs[bessie]);
			if (it == wormholeOnRight.end())
			{
				ret = false;
				break;
			}
			else
				bessie = it->second;
		}
		if (ret)
			return true;
	}
	return false;
}

int countInfiniteCycle()
{
	if (pairs.size() == n)
	{
		if (isThereInfiniteCycle())
			return 1;
		else
			return 0;
	}
	int ret = 0;
	int firstFree = 0;
	for (int i = 0; i < n; i++)
	{
		map<int, int>::iterator it = pairs.find(i);
		if (it == pairs.end())
		{
			firstFree = i;
			break;
		}
	}

	for (int pairWith = firstFree + 1; pairWith < n; pairWith++)
	{
		map<int, int>::iterator it = pairs.find(pairWith);
		if (it == pairs.end())
		{
			pairs.insert(make_pair(firstFree, pairWith));
			pairs.insert(make_pair(pairWith, firstFree));
			ret += countInfiniteCycle();

			pairs.erase(firstFree);
			pairs.erase(pairWith);
		}
	}

	return ret;
}

int submain()
{
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");

	fin >> n;

	vector<Pos> wormholes;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		fin >> a >> b;
		Pos pos(a, b);
		wormholes.push_back(pos);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (wormholes[i].y == wormholes[j].y && wormholes[j].x > wormholes[i].x)
			{
				map<int, int>::iterator it = wormholeOnRight.find(i);
				if (it == wormholeOnRight.end() || wormholes[it->second].x > wormholes[j].x)
					wormholeOnRight[i] = j;
			}
		}
	}


	fout << countInfiniteCycle() << endl;

	fin.close();
	fout.close();
	return 0;
}
