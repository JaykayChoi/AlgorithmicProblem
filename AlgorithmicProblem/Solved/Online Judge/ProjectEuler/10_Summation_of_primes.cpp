#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=10

bool isPrime[100000000];
int maxNum = 110000000;

void eratosthenes()
{
	memset(isPrime, 1, sizeof(isPrime));

	isPrime[0] = isPrime[1] = false;

	int sqrtn = int(sqrt(maxNum));

	for (int i = 2; i <= sqrtn; i++)
	{
		if (isPrime[i])
		{
			for (int j = i*i; j <= maxNum; j += i)
				isPrime[j] = false;
		}
	}
}


int submain()
{
	const int limit = 2000000;
	ll ret = 0;
	eratosthenes();

	for (int i = 2; i <= limit; i++)
	{
		if (isPrime[i])
		{
			ret += i;
		}
	}

	cout << ret << endl;

	system("pause");
	return 0;
}