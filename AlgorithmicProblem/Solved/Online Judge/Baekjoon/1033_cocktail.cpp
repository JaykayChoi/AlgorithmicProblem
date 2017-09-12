#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
#include <map>

using namespace std;
typedef long long ll;

const int MAX_NUM = 10000000;
int minPrimeFactors[MAX_NUM];

void eratosthenes(ll maxNum)
{
	minPrimeFactors[0] = minPrimeFactors[1] = -1;

	for (int i = 2; i <= maxNum; i++)
		minPrimeFactors[i] = i;

	ll sqrtn = ll(sqrt(maxNum));

	for (int i = 2; i <= sqrtn; i++)
	{
		if (minPrimeFactors[i] == i)
		{
			for (int j = i * i; j <= maxNum; j += i)
			{
				if (minPrimeFactors[j] == j)
					minPrimeFactors[j] = i;
			}
		}
	}
}



map<int, int> getPrimeFactor(ll num)
{
	map<int, int> ret;

	while (num > 1)
	{
		map<int, int>::iterator it = ret.find(minPrimeFactors[num]);

		if (it == ret.end())
			ret.insert(make_pair(minPrimeFactors[num], 1));
		else
			ret[minPrimeFactors[num]]++;

		num /= minPrimeFactors[num];
	}
	return ret;
}

void reduce(ll& a, ll& b, ll minA, ll minB)
{
	map<int, int> primeFactorsA = getPrimeFactor(a);
	map<int, int> primeFactorsB = getPrimeFactor(b);

	while (true)
	{
		if (primeFactorsA.empty() || primeFactorsB.empty())
			return;

		map<int, int>::iterator itA = primeFactorsA.begin();
		map<int, int>::iterator itB = primeFactorsB.begin();
		if (itA->first == itB->first)
		{
			ll tempA = a / itA->first;
			ll tempB = b / itB->first;
			if (tempA < minA || tempB < minB)
			{
				return;
			}
			else
			{
				a = tempA;
				b = tempB;
				if (itA->second == 1)
					primeFactorsA.erase(itA);
				else
					itA->second--;
				if (itB->second == 1)
					primeFactorsB.erase(itB);
				else
					itB->second--;
			}
		}
		else
		{
			if (itA->first > itB->first)
				primeFactorsB.erase(itB);
			else
				primeFactorsA.erase(itA);
		}
	}
}

int main()
{
	eratosthenes(MAX_NUM);
	int n;
	int numbers[10][4];
	ll ret[10] = { 1, };
	memset(numbers, -1, sizeof(numbers));
	cin >> n;
	for (int i = 0; i < n; i++)
		ret[i] = 1;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int num;
			cin >> num;
			numbers[i][j] = num;
		}
	}
	bool isCompleted = false;
	while (isCompleted == false)
	{
		int i = 0;
		for (; i < n - 1; i++)
		{
			if (ret[numbers[i][0]] * numbers[i][3] != ret[numbers[i][1]] * numbers[i][2])
			{
				ll defaultA = ret[numbers[i][0]];
				ll defaultB = ret[numbers[i][1]];
				ret[numbers[i][0]] *= ret[numbers[i][1]] * numbers[i][2];
				ret[numbers[i][1]] *= defaultA * numbers[i][3];
				ll tempA = ret[numbers[i][0]];
				ll tempB = ret[numbers[i][1]];
				reduce(tempA, tempB, defaultA, defaultB);
				ret[numbers[i][0]] = tempA;
				ret[numbers[i][1]] = tempB;
				break;
			}
		}
		if (i == n - 1)
			isCompleted = true;
	}

	for (int i = 0; i < n; i++)
	{
		if (i != 0)
			cout << " ";
		cout << ret[i];
	}
	cout << endl;
	return 0;
}