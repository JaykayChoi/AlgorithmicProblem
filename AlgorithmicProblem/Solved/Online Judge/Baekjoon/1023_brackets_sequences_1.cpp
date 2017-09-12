#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
#include <set>
using namespace std;
typedef long long ll;
//https://www.acmicpc.net/problem/1023

set<ll> cache;

bool isBracketsString(const string& formula)
{
	int opening = 0;
	for (int i = 0; i < formula.size(); i++)
	{
		if (formula[i] == '1')
			opening++;
		else
		{
			if (opening > 0)
				opening--;
			else
				return false;
		}
	}

	if (opening == 0)
		return true;
	else
		return false;
}

string convertToBinary(ll number)
{
	int closing = 0;
	bool isBracketsString = true;
	string ret = "";
	for (int i = 0; number > 0; i++)
	{
		if (number % 2 == 1)
		{
			ret = "(" + ret;
			if (isBracketsString)
			{
				if (closing == 0)
					isBracketsString = false;
				else
					closing--;
			}
		}
		else
		{
			ret = ")" + ret;
			if (isBracketsString)
				closing++;
		}
		number = number >> 1;
	}

	if (isBracketsString)
		ret = "";
	return ret;
}

void memoization(string formula, const int n)
{
	if (formula.size() == n - 1)
	{
		formula += "0";
		if (isBracketsString(formula))
			cache.insert(stoll(formula, NULL, 2));
		return;
	}

	memoization(formula + "1", n);
	memoization(formula + "0", n);
}

int main()
{
	ll n, k;
	//cin >> n >> k;
	k = 1125899906842623;
	n = 50;

	ll curNum = ((ll)1 << n) - 1;
	ll count = 0;
	string ret;
	if (n % 2 == 0)
	{
		while (curNum >= 0)
		{
			if (count == k)
				break;
			curNum--;
			ret = convertToBinary(curNum);
			if (ret != "")
				count++;
		}
	}
	else
	{
		ret = convertToBinary(curNum - k);
		count = k;
	}

	if (count == k)
		cout << ret << endl;
	else
		cout << -1 << endl;

	return 0;
}


