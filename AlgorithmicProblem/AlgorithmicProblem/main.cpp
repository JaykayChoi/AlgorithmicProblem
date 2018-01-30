#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1932

const int MAX = 1000;
int numbers[MAX][MAX];
int cache[2][MAX];
int n;
 
int dp()
{
    for (int x = 0; x < n; x++)
        cache[(n - 1) % 2][x] = numbers[n - 1][x];
 
    for (int y = n - 2; y >= 0; y--)
    {
        for (int x = 0; x < y + 1; x++)
            cache[y % 2][x] = max(cache[(y + 1) % 2][x], cache[(y + 1) % 2][x + 1]) + numbers[y][x];
    }
 
    return cache[0][0];
}


int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i + 1; j++)
		{
			scanf("%d", &numbers[i][j]);
		}
    }

	return 0;
}