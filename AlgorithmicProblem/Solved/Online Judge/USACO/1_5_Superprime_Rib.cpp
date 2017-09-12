/*
ID: jkchoik1
PROG: sprime
LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//http://jaykaychoi.tistory.com/61
vector<int> ret;

bool isPrime(int number)
{
	if (number == 1)
		return false;
	if (number == 2)
		return true;

	if (number % 2 == 0)
		return false;

	int sqrtn = int(sqrt(number));

	for (int div = 3; div <= sqrtn; div += 2)
		if (number % div == 0)
			return false;
	return true;
}

void makePrime(int remainingDegit, int number)
{
	if (remainingDegit == 0)
	{
		ret.push_back(number);
		return;
	}

	for (int i = number * 10 + 1; i <= number * 10 + 9; i++)
	{
		if (isPrime(i))
			makePrime(remainingDegit - 1, i);
	}
}

int main()
{
	ifstream fin("sprime.in");
	ofstream fout("sprime.out");

	int length;
	fin >> length;


	makePrime(length, 0);

	sort(ret.begin(), ret.end());

	for (vector<int>::iterator it = ret.begin(); it != ret.end(); it++)
		fout << *it << endl;

	fin.close();
	fout.close();
	return 0;
}