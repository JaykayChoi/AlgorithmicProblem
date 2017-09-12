/*
ID: jkchoik1
PROG: hamming
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

//http://jaykaychoi.tistory.com/74

int getHammingDistance(int a, int b)
{
	int ret = 0;
	while (a > 0 || b > 0)
	{
		if (a % 2 != b % 2)
			ret++;
		a /= 2;
		b /= 2;
	}
	return ret;
}



int main()
{
	ifstream fin("hamming.in");
	ofstream fout("hamming.out");

	int n, b, d, maxNum;
	fin >> n >> b >> d;

	maxNum = (1 << b) - 1;
	int temp = getHammingDistance(0, 25);
	set<int> ret;

	for (int i = 0; i <= maxNum; i++)
	{
		ret.clear();
		ret.insert(i);
		for (int j = i; j <= maxNum; j++)
		{
			bool ok = true;
			for (set<int>::iterator it = ret.begin(); it != ret.end(); it++)
			{
				if (getHammingDistance(*it, j) < d)
				{
					ok = false;
					break;
				}
			}
			if (ok)
			{
				ret.insert(j);
				if (ret.size() >= n)
					break;
			}
		}
		if (ret.size() >= n)
			break;
	}
	int i = 0;
	for (set<int>::iterator it = ret.begin(); it != ret.end(); it++)
	{
		if (i != 0 && i % 10 == 0)
			fout << endl;
		else if (i != 0)
			fout << " ";

		fout << *it;

		i++;
	}
	fout << endl;


	fin.close();
	fout.close();
	return 0;
}