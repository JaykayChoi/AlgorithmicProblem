/*
ID: jkchoik1
PROG: sort3
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//http://jaykaychoi.tistory.com/70

int n;
vector<int> numbers;
int eachNumbers[3];

int solve()
{
	int ret = 0;

	for (int i = 0; i < eachNumbers[0]; i++)
	{
		if (numbers[i] == 1)
			continue;

		int start, end;

		if (numbers[i] == 2)
		{
			start = eachNumbers[0];
			end = eachNumbers[0] + eachNumbers[1];
		}
		else
		{
			start = eachNumbers[0] + eachNumbers[1];
			end = n;
		}

		for (int j = start; j < end; j++)
		{
			if (numbers[j] == 1)
			{
				numbers[j] = numbers[i];
				numbers[i] = 1;
				ret++;
				break;
			}
		}

		if (numbers[i] == 1)
			continue;
		if (numbers[i] == 2)
		{
			start = eachNumbers[0] + eachNumbers[1];
			end = n;
		}
		else
		{
			start = eachNumbers[0];
			end = eachNumbers[0] + eachNumbers[1];
		}

		for (int j = start; j < end; j++)
		{
			if (numbers[j] == 1)
			{
				numbers[j] = numbers[i];
				numbers[i] = 1;
				ret++;
				break;
			}
		}
	}

	for (int i = eachNumbers[0]; i < eachNumbers[0] + eachNumbers[1]; i++)
	{
		if (numbers[i] == 3)
			ret++;
	}

	return ret;
}

int main()
{
	ifstream fin("sort3.in");
	ofstream fout("sort3.out");

	fin >> n;


	for (int i = 0; i < n; i++)
	{
		int num;
		fin >> num;
		numbers.push_back(num);
		eachNumbers[num - 1]++;
	}

	fout << solve() << endl;

	fin.close();
	fout.close();
	return 0;
}