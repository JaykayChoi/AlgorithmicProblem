#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=11

int numbers[20][20] = { 0, };

int getNumber(int low, int column)
{
	if (column < 0 || column > 19 || low < 0 || low > 19)
		return 0;
	return numbers[low][column];
}


int submain()
{
	ifstream fin("input.in");
	ll ret = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 20; column++)
		{
			int num;
			fin >> num;
			numbers[row][column] = num;
		}
	}

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 20; column++)
		{
			ll product = getNumber(row, column) * getNumber(row, column + 1) * getNumber(row, column + 2) * getNumber(row, column + 3);
			ret = max(ret, product);

			product = getNumber(row, column) * getNumber(row + 1, column) * getNumber(row + 2, column) * getNumber(row + 3, column);
			ret = max(ret, product);

			product = getNumber(row, column) * getNumber(row + 1, column + 1) * getNumber(row + 2, column + 2) * getNumber(row + 3, column + 3);
			ret = max(ret, product);

			product = getNumber(row, column) * getNumber(row + 1, column - 1) * getNumber(row + 2, column - 2) * getNumber(row + 3, column - 3);
			ret = max(ret, product);
		}
	}


	cout << ret << endl;

	system("pause");
	return 0;
}