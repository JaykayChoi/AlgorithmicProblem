#include <iostream>
using namespace std;

//https://projecteuler.net/problem=26


class Reciprocalcycles_26
{
public:
	int maxDenominator;

	int recursive(int i, int value, int count)
	{
		if (value == 1 || count > maxDenominator)
			return count;

		value *= 10;
		value %= i;
		count++;
		recursive(i, value, count);
	}

	int solve()
	{
		int curMaxCount = 0;
		int ret = 0;

		for (int i = 2; i <= maxDenominator; i++)
		{
			int count = 0;
			int value = 10 % i;

			count = recursive(i, value, count);

			if (count > curMaxCount && count <= maxDenominator)
			{
				curMaxCount = count;
				ret = i;
			}
		}

		return ret;
	}

	int sub_main()
	{
		maxDenominator = 1000;

		cout << solve() << endl;

		return 0;
	}
};
