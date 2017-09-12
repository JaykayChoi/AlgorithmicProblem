/*
ID: jkchoik1
PROG: dualpal
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//http://train.usaco.org/usacoprob2?a=qxjyGzruutH&S=dualpal

string convertToBase(int number, int base)
{
	if (base == 10)
		return to_string(number);
	string ret;
	int temp = base;

	while (temp < number)
	{
		temp *= base;
	}

	while (true)
	{
		temp /= base;

		//if (number / temp == 10)
		//	ret += number / temp - 10 + 'A';
		//else
		ret += number / temp + '0';

		number = number % temp;

		if (temp < 2)
			break;
	}

	return ret;
}

string reverseString(string str)
{
	//reverse(str.begin(), str.end());
	//return str;
	string ret = "";
	for (int i = str.length() - 1; i >= 0; i--)
		ret += str[i];
	return ret;
}

bool isPalindromic(string str)
{
	return str == reverseString(str);
}

bool isDualPalindromes(int number)
{
	bool ret = false;
	int leftCount = 2;

	for (int base = 2; base <= 10; base++)
	{
		if (isPalindromic(convertToBase(number, base)))
			leftCount--;

		if (leftCount == 0)
		{
			ret = true;
			break;
		}
	}

	return ret;
}

int sub_main()
{
	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");
	int N, S;
	fin >> N >> S;

	for (int i = S + 1; ; ++i)
	{
		if (isDualPalindromes(i))
		{
			fout << i << endl;
			N--;
		}
		if (N == 0)
			break;
	}

	return 0;
}
