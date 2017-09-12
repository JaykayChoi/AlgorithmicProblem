#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=12

const int MAX_NUM = 10000;

bool isPrime[MAX_NUM + 1];

vector<int> primes;

void eratosthenes()
{
	memset(isPrime, 1, sizeof(isPrime));

	isPrime[0] = isPrime[1] = false;

	int sqrtn = int(sqrt(MAX_NUM));

	int i;
	for (i = 2; i <= sqrtn; i++)
	{
		if (isPrime[i])
		{
			for (int j = i*i; j <= MAX_NUM; j += i)
				isPrime[j] = false;

			primes.push_back(i);
		}
	}

	for (; i < MAX_NUM; i += 2)
	{
		if (isPrime[i])
			primes.push_back(i);
	}
}



int countFactors(ll number)
{
	ll num = number;
	int ret = 1;

	for (ll i = 0; primes[i] * primes[i] <= number; i++)
	{
		int count = 0;
		while (num % primes[i] == 0)
		{
			num /= primes[i];
			count++;
		}

		ret *= count + 1;
	}

	if (num > 1)
		ret *= 2;

	return ret;
}


int getNumDivisors(ll num)
{
	int ret = 0;
	ll sqrtn = sqrt(num);
	for (ll i = 1; i <= sqrtn; i++)
	{
		if (num % i == 0)
			ret++;
	}

	if (num > 1)
		ret *= 2;

	return ret;
}



int submain()
{
	clock_t start = clock();
	eratosthenes();
	clock_t end = clock();
	double time = double(end - start) / CLOCKS_PER_SEC;
	cout << "eratosthenes (s): " << time << endl;

	start = clock();
	ll ret = 0;
	for (ll i = 1; ; i++)
	{
		int triangle = i * (i + 1) / 2;

		if (countFactors(triangle) >= 500)
		{
			ret = triangle;
			break;
		}
	}
	end = clock();
	time = double(end - start) / CLOCKS_PER_SEC;
	cout << "countFactors (s): " << time << endl;

	cout << ret << endl;

	start = clock();
	ret = 0;
	for (ll i = 1; ; i++)
	{
		int triangle = i * (i + 1) / 2;

		if (getNumDivisors(triangle) >= 500)
		{
			ret = triangle;
			break;
		}
	}
	end = clock();
	time = double(end - start) / CLOCKS_PER_SEC;
	cout << "getNumDivisors (s): " << time << endl;



	cout << ret << endl;



	system("pause");
	return 0;
}