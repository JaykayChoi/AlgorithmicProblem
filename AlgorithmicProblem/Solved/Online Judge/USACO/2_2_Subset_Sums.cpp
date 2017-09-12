/*
ID: jkchoik1
PROG: subset
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

//http://jaykaychoi.tistory.com/76

int n;
int triangularNumber;
ll cache[400][40];

ll getNumWays(int remainder, int curNum)
{
	if (remainder < 0 || curNum < 0)
		return 0;

	ll& ret = cache[remainder][curNum];
	if (ret != -1)
		return ret;

	if (remainder == 0 && curNum == 0)
		return ret = 1;

	//in case of no sum + in case of sum
	return ret = getNumWays(remainder, curNum - 1) + getNumWays(remainder - curNum, curNum - 1);
}

int main()
{
	ifstream fin("subset.in");
	ofstream fout("subset.out");

	fin >> n;
	triangularNumber = n * (n + 1) / 2;

	memset(cache, -1, sizeof(cache));

	if (triangularNumber % 2 == 0)
		fout << getNumWays(triangularNumber / 2, n) / 2 << endl;
	else
		fout << "0" << endl;


	fin.close();
	fout.close();
	return 0;
}