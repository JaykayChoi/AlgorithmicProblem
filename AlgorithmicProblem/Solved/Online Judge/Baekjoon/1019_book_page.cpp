#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1019

ll ret[10] = { 0, };

void printNumber()
{
	for (int i = 0; i < 10; i++)
	{
		if (i != 0)
			cout << " ";

		cout << ret[i];
	}

	cout << endl;
}

void calcDigit(int n)
{
	while (n > 0)
	{
		ret[n % 10]++;
		n /= 10;
	}
}

void bruteForce(int n)
{
	memset(ret, 0, sizeof(ret));
	for (int i = 1; i <= n; i++)
		calcDigit(i);

	printNumber();
}

void solve(ll n)
{
	memset(ret, 0, sizeof(ret));
	string str = to_string(n);
	queue<int> num;
	for (int i = 0; i < str.size(); i++)
		num.push(str[i] - '0');
	vector<int> firstNumbers;
	while (num.size() > 1)
	{
		int firstNum = num.front();

		if (firstNum == 0)
		{
			num.pop();
			firstNumbers.push_back(firstNum);
			continue;
		}

		int digit = num.size() - 1;
		string strOnes = "";
		string strOneZeros = "1";
		for (int i = 0; i < digit; i++)
		{
			strOnes += '1';
			strOneZeros += '0';
		}
		ll ones = stoll(strOnes);
		ll oneZeros = stoll(strOneZeros);


		ll temp1 = digit * (pow(10, digit - 1)) * firstNum;
		ll temp2 = temp1 - ones;

		ret[0] += temp2;
		for (int i = 1; i < 10; i++)
			ret[i] += temp1;

		for (int i = 1; i < firstNum; i++)
			ret[i] += oneZeros;

		if (firstNumbers.empty() == false)
		{
			int remaining = digit;
			for (int i = 9; i <= 9 * pow(10, digit - 1); i *= 10)
			{
				ret[0] += remaining * i;
				remaining--;
			}
		}

		for (vector<int>::iterator it = firstNumbers.begin(); it != firstNumbers.end(); it++)
			ret[*it] += (firstNum * oneZeros);
		firstNumbers.push_back(firstNum);

		calcDigit(firstNum * oneZeros);

		num.pop();
	}

	int lastNum = num.front();
	for (int i = 1; i <= lastNum; i++)
	{
		ret[i]++;
		for (vector<int>::iterator it = firstNumbers.begin(); it != firstNumbers.end(); it++)
			ret[*it]++;
	}

	printNumber();
}

int main()
{
	ll n;
	cin >> n;
	solve(n);
	return 0;
}
