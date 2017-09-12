#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

//https://www.acmicpc.net/problem/1014

const int MAX_N = 10;
const int dy[6] = { -1, 0, 1, -1, 0, 1 };
const int dx[6] = { -1, -1, -1, 1, 1, 1 };

int height, width, blockedCount;
bool isBlocked[MAX_N][MAX_N];
vector<int> adjacent[MAX_N * 5];
int aMatch[MAX_N * 5], bMatch[MAX_N * 5];
bool visited_ForDFS[MAX_N * 5];

bool dfs(int a)
{
	if (visited_ForDFS[a])
		return false;
	visited_ForDFS[a] = true;

	for (vector<int>::iterator b = adjacent[a].begin(); b != adjacent[a].end(); b++)
	{
		if (bMatch[*b] == -1 || dfs(bMatch[*b]))
		{
			aMatch[a] = *b;
			bMatch[*b] = a;
			return true;
		}
	}
	return false;
}

int bipartiteMatching(int count)
{
	int ret = 0;
	for (int i = 0; i < count; i++)
	{
		memset(visited_ForDFS, 0, sizeof(visited_ForDFS));
		if (dfs(i))
			ret++;
	}
	return ret;
}

int placeStudents()
{
	int id[MAX_N / 2][MAX_N];

	int count[2] = { 0, 0 };
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x += 2)
			id[y][x] = count[0]++;
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 1; x < width; x += 2)
			id[y][x] = count[1]++;
	}

	for (int x = 0; x < width; x += 2)
	{
		for (int y = 0; y < height; y++)
		{
			if (isBlocked[y][x])
				continue;

			for (int dir = 0; dir < 6; dir++)
			{
				int nextY = y + dy[dir];
				int nextX = x + dx[dir];
				if (nextY < 0 || nextY >= height || nextX < 0 || nextX >= width || isBlocked[nextY][nextX])
					continue;
				adjacent[id[y][x]].push_back(id[nextY][nextX]);
			}
		}
	}

	return bipartiteMatching(count[0]);
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		cin >> height >> width;

		memset(isBlocked, 0, sizeof(isBlocked));
		memset(aMatch, -1, sizeof(aMatch));
		memset(bMatch, -1, sizeof(bMatch));
		for (int i = 0; i < MAX_N * 5; i++)
			adjacent[i].clear();
		blockedCount = 0;
		for (int i = 0; i < height; i++)
		{
			string str;
			cin >> str;
			for (int j = 0; j < width; j++)
			{
				if (str[j] == 'x')
				{
					isBlocked[i][j] = true;
					blockedCount++;
				}
			}
		}

		cout << height * width - blockedCount - placeStudents() << endl;
	}

	return 0;
}