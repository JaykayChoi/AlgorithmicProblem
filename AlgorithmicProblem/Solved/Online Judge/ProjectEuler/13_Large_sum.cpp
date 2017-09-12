#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=13

int submain()
{
	ifstream fin("input.in");

	string row;

	int numbers[100][50];

	for (int i = 0; i < 100; i++)
	{
		fin >> row;

		for (int j = 0; j < 50; j++)
		{
			int num = row[j] - '0';
			numbers[i][j] = num;
		}
	}

	for (int j = 49; j >= 0; j--)
	{
		for (int i = 1; i < 100; i++)
		{
			numbers[i][j] += numbers[i - 1][j];
			numbers[i - 1][j] = 0;
			if (numbers[i][j] >= 10 && j != 0)
			{
				numbers[99][j - 1] += numbers[i][j] / 10;
				numbers[i][j] %= 10;
			}
		}
	}
	string ret = "";
	for (int i = 0; i < 10; i++)
		ret += to_string(numbers[99][i]);

	for (int i = 0; i < 10; i++)
		cout << ret[i];

	cout << endl;


	system("pause");
	return 0;
}