
//http://jaykaychoi.tistory.com/admin/entry/post/?id=43


/*
ID: jkchoik1
PROG: skidesign
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

const int maxDifference = 17;
int n;
vector<int> originalHills;


ll getCost(vector<int>& hills)
{
	ll ret = 0;
	for (int i = 0; i < n; i++)
	{
		ret += pow(originalHills[i] - hills[i], 2);
	}
	return ret;
}

ll changeHillHight()
{
	int lowest = originalHills[0];
	int highest = originalHills[n - 1];
	int heightTobeChanged = highest - lowest - maxDifference;

	ll ret = 999999999999999;

	for (int i = 0; i <= heightTobeChanged; i++)
	{
		vector<int> hills = originalHills;
		int changedHeight = lowest + i;
		for (vector<int>::iterator it = hills.begin(); it != hills.end(); it++)
		{
			if (*it < changedHeight)
				*it = changedHeight;
		}
		changedHeight = highest - heightTobeChanged + i;
		for (vector<int>::iterator it = hills.begin(); it != hills.end(); it++)
		{
			if (*it > changedHeight)
				*it = changedHeight;
		}

		ret = min(ret, getCost(hills));
	}
	return ret;
}

int main(void)
{
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");

	fin >> n;

	for (int i = 0; i < n; i++)
	{
		int num;
		fin >> num;
		originalHills.push_back(num);
	}
	sort(originalHills.begin(), originalHills.end());

	fout << changeHillHight() << endl;

	fin.close();
	fout.close();
	return 0;
}


//const int maxDifference = 17;
//int n;
//vector<int> originalHills;
//ll minCost;

//ll getCost(vector<int>& hills)
//{
//	ll ret = 0;
//	for (int i = 0; i < n; i++)
//	{
//		ret += pow(originalHills[i] - hills[i], 2);
//	}
//	return ret;
//}
//
//ll changeHillHight(vector<int> hills)
//{
//	if (hills[n - 1] - hills[0] <= maxDifference)
//		return getCost(hills);
//
//	ll curCost = getCost(hills);
//	if (minCost != 0 && curCost > minCost)
//		return curCost;
//
//	vector<int> addHill = hills;
//	vector<int> shortenHill = hills;
//
//	int changedHeight = hills[0] + 1;
//	for (vector<int>::iterator it = addHill.begin(); it != addHill.end(); it++)
//	{
//		if (*it < changedHeight)
//			*it = changedHeight;
//	}
//	changedHeight = hills[n - 1] - 1;
//	for (vector<int>::iterator it = shortenHill.begin(); it != shortenHill.end(); it++)
//	{
//		if (*it > changedHeight)
//			*it = changedHeight;
//	}
//
//	if (minCost == 0)
//		minCost = 99999999999999;
//	return minCost = min(minCost, min(changeHillHight(addHill), changeHillHight(shortenHill)));
//}
//
//int main(void)
//{
//	ifstream fin("skidesign.in");
//	ofstream fout("skidesign.out");
//
//	fin >> n;
//
//	for (int i = 0; i < n; i++)
//	{
//		int num;
//		fin >> num;
//		originalHills.push_back(num);
//	}
//	sort(originalHills.begin(), originalHills.end());
//
//	fout << changeHillHight(originalHills) << endl;
//
//	fin.close();
//	fout.close();
//	return 0;
//}