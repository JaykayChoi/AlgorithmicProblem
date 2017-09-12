/*
ID: jkchoik1
PROG: pprime
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//http://jaykaychoi.tistory.com/60
bool isPrime(int n)
{
	if (n == 1)
		return false;
	if (n == 2)
		return true;

	if (n % 2 == 0)
		return false;

	int sqrtn = int(sqrt(n));

	for (int div = 3; div <= sqrtn; div += 2)
		if (n % div == 0)
			return false;
	return true;
}

vector<int> solve(int min, int max)
{
	vector<int> ret;
	if (min <= 5 && max >= 5)
		ret.push_back(5);
	if (min <= 7 && max >= 7)
		ret.push_back(7);

	if (max < 11)
		return ret;
	for (int d1 = 1; d1 <= 9; d1 += 2)
	{
		int palindrome = 10 * d1 + d1;
		if (isPrime(palindrome))
			ret.push_back(palindrome);
	}

	if (max < 101)
		return ret;
	for (int d1 = 1; d1 <= 9; d1 += 2)
	{
		for (int d2 = 0; d2 <= 9; d2++)
		{
			int palindrome = 100 * d1 + 10 * d2 + d1;
			if (isPrime(palindrome))
				ret.push_back(palindrome);

			palindrome = 1000 * d1 + 100 * d2 + 10 * d2 + d1;
			if (isPrime(palindrome))
				ret.push_back(palindrome);
		}
	}

	if (max < 10001)
		return ret;
	for (int d1 = 1; d1 <= 9; d1 += 2)
	{
		for (int d2 = 0; d2 <= 9; d2++)
		{
			for (int d3 = 0; d3 <= 9; d3++)
			{
				int palindrome = 10000 * d1 + 1000 * d2 + 100 * d3 + 10 * d2 + d1;
				if (isPrime(palindrome))
					ret.push_back(palindrome);

				palindrome = 100000 * d1 + 10000 * d2 + 1000 * d3 + 100 * d3 + 10 * d2 + d1;
				if (isPrime(palindrome))
					ret.push_back(palindrome);
			}
		}
	}

	if (max < 1000001)
		return ret;
	for (int d1 = 1; d1 <= 9; d1 += 2)
	{
		for (int d2 = 0; d2 <= 9; d2++)
		{
			for (int d3 = 0; d3 <= 9; d3++)
			{
				for (int d4 = 0; d4 <= 9; d4++)
				{
					int palindrome = 1000000 * d1 + 100000 * d2 + 10000 * d3 + 1000 * d4 + 100 * d3 + 10 * d2 + d1;
					if (isPrime(palindrome))
						ret.push_back(palindrome);

					palindrome = 10000000 * d1 + 1000000 * d2 + 100000 * d3 + 10000 * d4 + 1000 * d4 + 100 * d3 + 10 * d2 + d1;
					if (isPrime(palindrome))
						ret.push_back(palindrome);
				}
			}
		}
	}

	sort(ret.begin(), ret.end());
	return ret;
}

int main()
{
	ifstream fin("pprime.in");
	ofstream fout("pprime.out");

	int a, b;
	fin >> a >> b;

	vector<int> ret = solve(a, b);

	for (vector<int>::iterator it = ret.begin(); it != ret.end(); it++)
	{
		if (*it > b)
			break;
		if (*it >= a)
			fout << *it << endl;
	}

	fin.close();
	fout.close();
	return 0;
}