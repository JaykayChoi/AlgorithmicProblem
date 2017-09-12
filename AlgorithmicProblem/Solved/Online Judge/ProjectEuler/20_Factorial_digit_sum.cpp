#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//http://jaykaychoi.tistory.com/64

int main()
{
	vector <int> digits(1000);
	int ret = 0;

	digits[0] = 1;

	int raising = 0, curDigit = 0;

	for (int i = 2; i <= 100; i++)
	{
		for (int j = 0; j <= curDigit; j++)
		{
			digits[j] = digits[j] * i + raising;
			raising = 0;
			if (digits[j] > 9)
			{
				raising = digits[j] / 10;
				digits[j] %= 10;
				if (j == curDigit)
					curDigit++;
			}
		}
	}

	for (int i = 0; i <= curDigit; i++)
		ret += digits[i];

	cout << ret << endl;

	system("pause");
	return 0;
}