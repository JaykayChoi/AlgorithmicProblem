#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;

//https://www.acmicpc.net/problem/1028

namespace Dir
{
	enum Dir { southeast, southwest, northwest, northeast };
}

const int MAX_N = 750;
int height, width;
int map[MAX_N + 1][MAX_N + 1];
int cache[MAX_N + 1][MAX_N + 1][4];

void getMovingPoint(Dir::Dir dir, int& y, int& x, int step)
{
	if (step <= 0)
		return;
	switch (dir)
	{
	case Dir::southeast:
		y += step; x += step;
		break;
	case Dir::southwest:
		y += step; x -= step;
		break;
	case Dir::northwest:
		y -= step; x -= step;
		break;
	case Dir::northeast:
		y -= step; x += step;
		break;
	default:
		break;
	}
}

int getMaxMovingStep(Dir::Dir dir, int y, int x)
{
	int& step = cache[y][x][dir];

	if (step != -1)
		return step;

	step = 0;
	int nextY = y;
	int nextX = x;
	while (true)
	{
		switch (dir)
		{
		case Dir::southeast:
			nextY++; nextX++;
			break;
		case Dir::southwest:
			nextY++; nextX--;
			break;
		case Dir::northwest:
			nextY--; nextX--;
			break;
		case Dir::northeast:
			nextY--; nextX++;
			break;
		default:
			break;
		}
		if (nextY < 0 || nextY >= height || nextX < 0 || nextX >= width)
			break;
		if (map[nextY][nextX] != 1)
			break;
		else
			step++;
	}
	return step;
}

bool isDiamond(int y, int x, int step)
{
	getMovingPoint(Dir::southeast, y, x, step);

	if (getMaxMovingStep(Dir::southwest, y, x) < step)
		return false;
	getMovingPoint(Dir::southwest, y, x, step);

	if (getMaxMovingStep(Dir::northwest, y, x) < step)
		return false;
	getMovingPoint(Dir::northwest, y, x, step);

	if (getMaxMovingStep(Dir::northeast, y, x) < step)
		return false;
	else
		return true;
}

int getMaxDiamond()
{
	int ret = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (map[y][x] == 1)
			{
				if (ret == 0)
					ret++;

				int step = getMaxMovingStep(Dir::southeast, y, x);

				for (int i = step; step > ret - 1; step--)
				{
					if (isDiamond(y, x, step))
						ret = step + 1;
				}
			}
		}
	}
	return ret;
}

int main()
{
	memset(cache, -1, sizeof(cache));
	memset(map, -1, sizeof(map));

	cin >> height >> width;

	for (int i = 0; i < height; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < width; j++)
			map[i][j] = str[j] - '0';
	}

	cout << getMaxDiamond() << endl;
	return 0;
}