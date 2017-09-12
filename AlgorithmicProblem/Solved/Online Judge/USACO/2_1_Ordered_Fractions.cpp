/*
ID: jkchoik1
PROG: frac1
LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//http://jaykaychoi.tistory.com/69

struct Fraction
{
	int numerator, denominators;
	Fraction(int n, int d) : numerator(n), denominators(d) { };
};

//GCD is Greatest common divisor
int calcGCD(int a, int b)
{
	int remainder;
	if (a < 1 || b < 1)
		return 0;

	if (a < b)
		return calcGCD(b, a);

	while ((remainder = a % b) != 0)
	{
		a = b;
		b = remainder;
	}
	return b;
}



int main()
{
	ifstream fin("frac1.in");
	ofstream fout("frac1.out");
	multimap<double, Fraction> ret;
	int n;
	fin >> n;
	if (n > 0)
		ret.insert(make_pair(0, Fraction(0, 1)));
	for (int denominators = 1; denominators <= n; denominators++)
	{
		for (int numerator = 1; numerator <= denominators; numerator++)
		{
			if (calcGCD(denominators, numerator) == 1)
			{
				ret.insert(make_pair((double)numerator / (double)denominators, Fraction(numerator, denominators)));
			}
		}
	}

	for (multimap<double, Fraction>::iterator it = ret.begin(); it != ret.end(); it++)
		fout << it->second.numerator << "/" << it->second.denominators << endl;


	fin.close();
	fout.close();
	return 0;
}