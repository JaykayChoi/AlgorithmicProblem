#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <list>

using namespace std;

//https://www.acmicpc.net/problem/1158

void josephus(int n, int m)
{
	list<int> survivors;

	for (int i = 1; i <= n; i++)
	{
		survivors.push_back(i);
	}

	list<int>::iterator dead = survivors.begin();
	for (int i = 0; i < m - 1; i++)
	{
		dead++;
	}
	printf("<");
	while (true)
	{
		printf("%d", *dead);
		dead = survivors.erase(dead);

		if (dead == survivors.end())
		{
			dead = survivors.begin();
		}

		n--;

		if (n == 0)
		{
			break;
		}

		printf(", ");

		for (int i = 0; i < (m - 1) % n; i++)
		{
			dead++;
			if (dead == survivors.end())
			{
				dead = survivors.begin();
			}
		}
	}
	printf(">");
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	josephus(n, m);

	return 0;
}