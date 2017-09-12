#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=5

int minPrimeFactors[30];

void eratosthenes(int maxNum)
{
	minPrimeFactors[0] = minPrimeFactors[1] = -1;

	for (int i = 2; i <= maxNum; i++)
		minPrimeFactors[i] = i;

	int sqrtn = int(sqrt(maxNum));

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

map<int, int> getPrimeFactor(int num)
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


int submain()
{
	int maxNum = 20;
	eratosthenes(maxNum);

	ll ret = 1;

	map<int, int> primes;

	for (int i = 2; i <= maxNum; i++)
	{
		map<int, int> temp = getPrimeFactor(i);

		for (map<int, int>::iterator it = temp.begin(); it != temp.end(); it++)
		{
			map<int, int>::iterator it2 = primes.find(it->first);

			if (it2 == primes.end())
				primes.insert(make_pair(it->first, 1));
			else
			{
				if (it->second > primes[it->first])
					primes[it->first] = it->second;
			}
		}
	}

	for (map<int, int>::iterator it = primes.begin(); it != primes.end(); it++)
	{
		ret *= (pow(it->first, it->second));
	}


	cout << ret << endl;

	system("pause");
	return 0;
}