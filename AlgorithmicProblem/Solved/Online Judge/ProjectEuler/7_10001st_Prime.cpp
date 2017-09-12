
#include <iostream>
#include <string>

using namespace std;

//https://projecteuler.net/problem=7

bool isPrime[10000000];
int maxNum = 1000000;

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
	int limit = 10001;
	int ret = 0;
	eratosthenes();

	for (int i = 2; ; i++)
	{
		if (isPrime[i])
		{
			limit--;
			if (limit == 0)
			{
				ret = i;
				break;
			}
		}
	}

	cout << ret << endl;

	system("pause");
	return 0;
}