#include <stdio.h>
#include <iostream>

using namespace std;

//1부터 n 까지의 합.

class DivideConquer_fastSum_7_1
{
public:
	void Solve()
	{
		cout << fastSum(3) << endl;
	}
private:
	int fastSum(int n)
	{
		if (n == 1)
			return 1;
		if (n % 2 == 1)
			return fastSum(n - 1) + n;

		return 2 * fastSum(n / 2) + (n / 2) * (n / 2);
	}

	int sum(int n)
	{
		return n * (n + 1) / 2;
	}

};