/*
ID: jkchoik1
PROG: crypt1
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
#include <set>
using namespace std;

//http://train.usaco.org/usacoprob2?a=qxjyGzruutH&S=crypt1

set<int> numbers;

bool isAllowed(int num, int allowedDigit)
{
	string strNum = to_string(num);

	if (strNum.size() != allowedDigit)
		return false;

	for (int i = 0; i < strNum.size(); i++)
	{
		set<int>::iterator it = numbers.find(strNum[i] - '0');
		if (it == numbers.end())
			return false;
	}
	return true;
}

int sub_main()
{
	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");

	int n;

	fin >> n;

	for (int i = 0; i < n; i++)
	{
		int num;
		fin >> num;
		numbers.insert(num);
	}

	int ret = 0;
	for (int i = 100; i < 1000; i++)
	{
		for (int j = 10; j < 100; j++)
		{
			if (isAllowed(i, 3) && isAllowed(j, 2) && isAllowed(i * (j % 10), 3) && isAllowed(i * (j / 10), 3) && isAllowed(i * j, 4))
				ret++;
		}
	}

	fout << ret << endl;

	return 0;
}