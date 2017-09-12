#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=8

int submain()
{
	ifstream fin("input.in");
	vector<int> numbers;

	string str;
	fin >> str;

	for (int i = 0; i < str.size(); i++)
	{
		numbers.push_back(str[i] - '0');
	}

	const int adjacentDigits = 13;

	ll maxNum = 0;
	ll multi = 1;
	for (int i = 0; i < numbers.size(); i++)
	{
		if (i < adjacentDigits)
		{
			multi *= numbers[i];
			if (i == adjacentDigits - 1)
				maxNum = multi;
			continue;
		}

		if (numbers[i - adjacentDigits] == 0)
		{
			multi = 1;
			for (int j = i - adjacentDigits + 1; j <= i; j++)
				multi *= numbers[j];
		}
		else
		{
			multi /= numbers[i - adjacentDigits];
			multi *= numbers[i];
		}
		maxNum = max(maxNum, multi);
	}

	cout << maxNum << endl;

	system("pause");
	return 0;
}