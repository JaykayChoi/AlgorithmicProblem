#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef long long ll;

//https://projecteuler.net/problem=9

int submain()
{
	const int sum = 1000;

	int ret = 0;
	for (int a = 1; a < sum; a++)
	{
		for (int b = a + 1; b < sum; b++)
		{
			for (int c = b + 1; c < sum; c++)
			{
				if (a + b + c != sum)
					continue;
				if (c * c == a * a + b * b)
				{
					ret = a * b * c;
					break;
				}
			}
			if (ret != 0)
				break;
		}
		if (ret != 0)
			break;
	}

	cout << ret << endl;

	system("pause");
	return 0;
}