#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
int d[501][501];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &d[i][j]);

	return 0;
}