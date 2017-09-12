#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//https://www.acmicpc.net/problem/1010

const int MAX = 31;

int cache[MAX][MAX];

int getBinomialCoefficient(int n, int k)
{
	if (n == k || k == 0)
		return 1;

	if (cache[n][k] != -1)
		return cache[n][k];

	return cache[n][k] = getBinomialCoefficient(n - 1, k - 1) + getBinomialCoefficient(n - 1, k);
}


int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int n, m;
		cin >> n >> m;
		memset(cache, -1, sizeof(cache));
		cout << getBinomialCoefficient(m, n) << endl;
	}

	return 0;
}
