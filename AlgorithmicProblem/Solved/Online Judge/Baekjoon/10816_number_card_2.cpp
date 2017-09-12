#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

#include <map>
using namespace std;

int main()
{
	int n, m, num;
	map<int, int> numbers;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num);
		numbers[num]++;
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &num);
		printf("%d", numbers[num]);
		if (i != m - 1)
			printf(" ");
	}
	return 0;
}