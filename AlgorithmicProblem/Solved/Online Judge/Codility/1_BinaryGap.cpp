#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//https://codility.com/programmers/task/binary_gap/

void toBinary(int n)
{
	if (n != 1)
		toBinary(n / 2);
	cout << n % 2;
}

int solution1(int num)
{
	int count = 0;
	int ret = 0;
	while (num > 0)
	{
		if (num % 2 == 0)
			count++;
		else
		{
			ret = (ret, count);
			count = 0;
		}
		num /= 2;
	}
	return ret;
}

int solution2(int N)
{
	int ret = 0;
	int lastIndex = -1;

	//N is 32 bit integer
	for (int i = 0; i < 32; i++)
	{
		int bit = 1 << i;

		if (bit > N)
			return ret;

		if ((N & bit) > 0)
		{
			if (lastIndex == -1)
				lastIndex = i;
			else
			{
				int count = (i - lastIndex) - 1;
				ret = max(ret, count);
				lastIndex = i;
			}
		}
	}
	return ret;
}

int submain()
{
	//cout << solution1(1) << endl;

	long temp = 5555555555555555555;
	cout << sizeof(temp) << endl;

	system("pause");
	return 0;
}
