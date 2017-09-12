#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;

int BinomialCoefficient_Cache[11][11];

int getBinomialCoefficient(int n, int k)
{
	if (n == k || k == 0)
		return 1;

	if (BinomialCoefficient_Cache[n][k] != -1)
		return BinomialCoefficient_Cache[n][k];

	return BinomialCoefficient_Cache[n][k] = getBinomialCoefficient(n - 1, k - 1) + getBinomialCoefficient(n - 1, k);
}

ll makeNumber(int n, int k, int num)
{
	ll ret;

	if (k <= 1)
		return num - 1;

	int firstNumber = k - 2;
	while (true)
	{
		firstNumber++;
		int bino = getBinomialCoefficient(firstNumber, k - 1);
		if (num > bino)
			num -= bino;
		else
			break;
	}

	ret = firstNumber * pow(10, k - 1) + makeNumber(firstNumber - 1, k - 1, num);
	return ret;
}

int main()
{
	memset(BinomialCoefficient_Cache, -1, sizeof(BinomialCoefficient_Cache));
	int n;
	cin >> n;
	n++;
	ll ret = -1;

	for (int digit = 1; digit <= 10; digit++)
	{
		int bino = getBinomialCoefficient(10, digit);
		if (n > bino)
		{
			n -= bino;
		}
		else
		{
			ret = makeNumber(9, digit, n);
			break;
		}
	}

	cout << ret << endl;
	return 0;
}

