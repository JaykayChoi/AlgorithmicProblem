#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;

//https://www.acmicpc.net/problem/1022
int getDigit(int n)
{
	int ret = 0;
	while (n > 0)
	{
		ret++;
		n /= 10;
	}
	return ret;
}

int getSpiralNumber(int y, int x)
{
	int maxCoordinate = max(abs(y), abs(x));
	int maxNum = (2 * maxCoordinate + 1) * (2 * maxCoordinate + 1);
	int minNum = maxNum - maxCoordinate * 8 + 1;

	if (x == maxCoordinate && y != maxCoordinate)
		return minNum + maxCoordinate - y - 1;
	else if (y == maxCoordinate * -1)
		return minNum + (maxCoordinate * 2) + maxCoordinate - x - 1;
	else if (x == maxCoordinate * -1)
		return minNum + (maxCoordinate * 4) + maxCoordinate + y - 1;
	else
		return minNum + (maxCoordinate * 6) + maxCoordinate + x - 1;
}

int main()
{
	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;

	vector<int> ret;

	int maxDigit = 0;
	for (int y = r1; y <= r2; y++)
	{
		for (int x = c1; x <= c2; x++)
		{
			int num = getSpiralNumber(y, x);
			maxDigit = max(maxDigit, getDigit(num));
			ret.push_back(num);
		}
	}

	int curX = c1;
	for (vector<int>::iterator it = ret.begin(); it != ret.end(); it++)
	{
		if (curX == c2 + 1)
		{
			cout << endl;
			curX = c1;
		}
		else if (curX != c1)
			cout << " ";

		int digit = getDigit(*it);
		while (digit != maxDigit)
		{
			cout << " ";
			digit++;
		}
		cout << *it;
		curX++;
	}

	return 0;
}
