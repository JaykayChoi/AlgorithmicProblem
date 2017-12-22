#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

//https://www.acmicpc.net/problem/1992

int n;
bool tree[65][65];

void compress(int startY, int startX, int size)
{
	bool start = tree[startY][startX];
	bool isSame = true;
	for (int y = startY; y < startY + size; y++)
	{
		for (int x = startX; x < startX + size; x++)
		{
			if (tree[y][x] != start)
			{
				isSame = false;
				break;
			}
		}
		if (!isSame)
			break;
	}
	if (isSame)
	{
		printf("%d", start);
	}
	else
	{
		printf("%c", '(');
		int newSize = size / 2;
		compress(startY, startX, newSize);
		compress(startY, startX + newSize, newSize);
		compress(startY + newSize, startX, newSize);
		compress(startY + newSize, startX + newSize, newSize);
		printf("%c", ')');
	}

}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char c;
			scanf(" %c", &c);
			tree[i][j] = c - '0';
		}
	}
	compress(0, 0, n);
	return 0;
}


ÃâÃ³: http://jaykaychoi.tistory.com/143?category=561047 [Program Programming Programmer]