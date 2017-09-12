#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//https://projecteuler.net/problem=18

const int MAX = 15;
int numbers[MAX][MAX];
int cache[2][MAX];

int dynamicProgramming()
{
	for (int x = 0; x < MAX; x++)
		cache[(MAX - 1) % 2][x] = numbers[MAX - 1][x];

	for (int y = MAX - 2; y >= 0; y--)
	{
		for (int x = 0; x < y + 1; x++)
			cache[y % 2][x] = max(cache[(y + 1) % 2][x], cache[(y + 1) % 2][x + 1]) + numbers[y][x];
	}

	return cache[0][0];
}

int submain()
{
	ifstream fin("input.in");

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < i + 1; j++)
			fin >> numbers[i][j];
	}

	cout << dynamicProgramming() << endl;

	fin.close();
	system("pause");
	return 0;
}
