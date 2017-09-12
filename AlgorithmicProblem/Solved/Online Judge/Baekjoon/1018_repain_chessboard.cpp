#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <string>
#include <vector>
using namespace std;

//https://www.acmicpc.net/problem/1019

const int MAX_N = 50;

int height, width;
//0 is black, 1 is white. means boards[y][x]
bool board[MAX_N][MAX_N];

int repaint(int startY, int startX)
{
	int ret = INT_MAX;
	for (int i = 0; i < 2; i++)
	{
		int count = 0;
		bool answer = i;
		for (int y = startY; y < startY + 8; y++)
		{
			if (y % 2 != startY % 2)
				answer = !i;
			else
				answer = i;
			for (int x = startX; x < startX + 8; x++)
			{
				answer = !answer;
				if (board[y][x] != answer)
					count++;
			}
		}
		ret = min(ret, count);
	}
	return ret;
}

int main()
{
	cin >> height >> width;

	for (int i = 0; i < height; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); j++)
			board[i][j] = str[j] == 'B' ? true : false;
	}

	int ret = INT_MAX;

	for (int y = 0; y <= height - 8; y++)
	{
		for (int x = 0; x <= width - 8; x++)
		{
			ret = min(ret, repaint(y, x));
		}
	}

	cout << ret << endl;

	return 0;
}
