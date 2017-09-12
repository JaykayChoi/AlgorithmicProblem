#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=14

const int MAX_INT = 1000000;
int cache[MAX_INT + 1];

int memoization(int number)
{
	int ret = 0;
	ll num = number;

	while (true)
	{
		if (num < MAX_INT && cache[num] != -1)
		{
			ret += cache[num];
			break;
		}

		if (num % 2 == 0)
			num = num / 2;
		else
			num = 3 * num + 1;
		ret++;
	}

	cache[number] = ret;

	return ret;
}

int submain()
{
	int maxCount = 0;
	int ret = 1;

	memset(cache, -1, sizeof(cache));
	cache[1] = 1;

	for (int i = 2; i <= MAX_INT; i++)
	{
		int count = memoization(i);
		if (count > maxCount)
		{
			maxCount = count;
			ret = i;
		}
	}

	cout << ret << endl;

	system("pause");
	return 0;
}