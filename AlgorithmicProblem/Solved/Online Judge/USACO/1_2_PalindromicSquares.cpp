/*
ID: jkchoik1
PROG: palsquare
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//http://train.usaco.org/usacoprob2?a=qxjyGzruutH&S=palsquare

string convertToBase(int number, int base)
{
	string ret;
	int temp = base;

	while (temp < number)
	{
		temp *= base;
	}

	while (true)
	{
		temp /= base;

		if (number / temp >= 10)
			ret += number / temp - 10 + 'A';
		else
			ret += number / temp + '0';

		number = number % temp;

		if (temp < 2)
			break;
	}

	return ret;
}

string reverseString(string str)
{
	string ret = "";
	for (int i = str.length() - 1; i >= 0; i--)
		ret += str[i];
	return ret;
}

bool isPalindromic(string str)
{
	return str == reverseString(str);
}

int sub_main()
{
	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");
	int base;
	fin >> base;

	for (int i = 1; i <= 300; ++i)
	{
		string p = convertToBase(i * i, base);
		if (isPalindromic(p))
			fout << convertToBase(i, base) << " " << p << endl;
	}

	return 0;
}
