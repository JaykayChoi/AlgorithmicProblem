#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=15

ll cache[50][50];

ll getBinomialCoefficient(int n, int k)
{
	///��� ���Ҹ� �� ���� ��� �Ǵ� �� ���Ұ� ���� ���
	if (n == k || k == 0)
		return 1;

	if (cache[n][k] != -1)
		return cache[n][k];

	return cache[n][k] = getBinomialCoefficient(n - 1, k - 1) + getBinomialCoefficient(n - 1, k);
}

int submain()
{
	memset(cache, -1, sizeof(cache));
	cout << getBinomialCoefficient(40, 20) << endl;

	system("pause");
	return 0;
}