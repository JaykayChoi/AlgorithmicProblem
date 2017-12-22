#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

//https://www.acmicpc.net/problem/1149

int cost[1000][3];
int cache[1000][4];

int dp(int curHouse, int preColor, int n)
{
	if (curHouse == n)
	{
		return 0;
	}

	int& ret = cache[curHouse][preColor];
	if (ret != -1)
	{
		return ret;
	}

	ret = INT_MAX;
	for (int i = 0; i < 3; i++)
	{
		if (preColor != i)
		{
			ret = min(ret, dp(curHouse + 1, i, n) + cost[curHouse][i]);
		}
	}
	return ret;
}

int main()
{
	memset(cache, -1, sizeof(cache));
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &cost[i][0], &cost[i][1], &cost[i][2]);
	}

	printf("%d\n", dp(0, 3, n));

	return 0;
}