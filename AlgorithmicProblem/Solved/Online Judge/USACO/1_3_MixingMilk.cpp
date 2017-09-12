/*
ID: jkchoik1
PROG: milk
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <map>
using namespace std;

//http://train.usaco.org/usacoprob2?a=qxjyGzruutH&S=milk

int buyMilk(multimap<int, int>& sellers, int needMilk)
{
	int cost = 0;
	int leftBuyingMilk = needMilk;
	for (multimap<int, int>::iterator it = sellers.begin(); it != sellers.end(); it++)
	{
		if (it->second <= leftBuyingMilk)
		{
			leftBuyingMilk -= it->second;
			cost += it->second * it->first;
		}
		else
		{
			cost += leftBuyingMilk * it->first;
			break;
		}
	}
	return cost;
}


int sub_main()
{
	ofstream fout("milk.out");
	ifstream fin("milk.in");

	int needMilk, numFarmers;
	fin >> needMilk >> numFarmers;

	multimap<int, int> sellers;
	for (int i = 0; i < numFarmers; i++)
	{
		int price, amount;
		fin >> price >> amount;
		sellers.insert(make_pair(price, amount));
	}

	fout << buyMilk(sellers, needMilk) << endl;

	return 0;
}
