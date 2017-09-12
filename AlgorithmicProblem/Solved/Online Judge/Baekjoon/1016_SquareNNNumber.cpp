#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1016

const ll MAX_N = 1000003;
unsigned char sieve[(MAX_N + 7) / 8];

ll minNum, maxNum;

bool isSquareNNNumber(ll number)
{
	number -= minNum;
	return sieve[number >> 3] & (1 << (number & 7));
}

void removeFromSieve(ll number)
{
	number -= minNum;
	sieve[number >> 3] &= ~(1 << (number & 7));
}

void eratosthenes()
{
	memset(sieve, 255, sizeof(sieve));

	ll maxNumSqrt = ll(sqrt(maxNum));
	ll num = 1;
	while (true)
	{
		num++;
		if (num > maxNumSqrt)
			break;
		ll i = num * num;

		for (ll j = minNum % i == 0 ? minNum : (ll)(minNum / i) * i + i; j <= maxNum; j += i)
		{
			if (j >= minNum)
				removeFromSieve(j);
		}
	}
}

int main()
{
	cin >> minNum >> maxNum;
	eratosthenes();

	int ret = 0;
	for (ll i = minNum; i <= maxNum; i++)
	{
		if (isSquareNNNumber(i))
			ret++;
	}

	cout << ret << endl;
	return 0;
}
