#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;

const int MAX_NM = 50;

int n, m, k;

int howManyLampsAreTurnedOn(const bool lamps[MAX_NM][MAX_NM])
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		bool isAnswer = true;
		for (int j = 0; j < m; j++)
		{
			if (lamps[i][j] == false)
			{
				isAnswer = false;
				break;
			}
		}
		if (isAnswer)
			count++;
	}
	return count;
}
void turnLamps(bool lamps[MAX_NM][MAX_NM], int row)
{
	for (int i = 0; i < n; i++)
		lamps[i][row] = !lamps[i][row];
}

int recursive(bool lamps[][MAX_NM], int remaining)
{
	if (remaining == 0)
		return howManyLampsAreTurnedOn(lamps);

	int ret = -1;

	for (int i = 0; i < m; i++)
	{
		turnLamps(lamps, i);
		ret = max(ret, recursive(lamps, remaining - 1));
		turnLamps(lamps, i);
	}
	return ret;
}

int greedy(const bool lamps[MAX_NM][MAX_NM], int c)
{
	int ret = 0;
	for (int64_t i = 0; i < ((int64_t)1 << m); i++)
	{
		int bitCount = 0;
		for (int j = 0; j < m; j++)
		{
			if ((i >> j) & 1)
				bitCount++;
		}
		if (bitCount > c)
			continue;
		if (bitCount != c && bitCount % 2 != c % 2)
			continue;

		bool tmpLamps[MAX_NM][MAX_NM];
		memset(tmpLamps, 0, sizeof(tmpLamps));
		for (int c = 0; c < n; c++)
		{
			for (int r = 0; r < m; r++)
				tmpLamps[c][r] = lamps[c][r];
		}

		for (int j = 0; j < m; j++)
		{
			if ((i >> j) & 1)
				turnLamps(tmpLamps, j);
		}
		ret = max(ret, howManyLampsAreTurnedOn(tmpLamps));
	}
	return ret;
}

int main()
{
	bool lamps[MAX_NM][MAX_NM];
	memset(lamps, 0, sizeof(lamps));
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < m; j++)
		{
			if (str[j] == '1')
				lamps[i][j] = true;
		}
	}
	cin >> k;
	cout << greedy(lamps, k) << endl;
	return 0;
}

/*
50 50
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
00000000000000000000000000000000000000000000000000
1
*/