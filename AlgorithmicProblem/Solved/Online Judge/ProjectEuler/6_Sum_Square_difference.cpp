#include <iostream>
#include <string>

using namespace std;

//https://projecteuler.net/problem=6

int submain()
{
	int ret = 0;

	int maxNum = 100;

	for (int i = 1; i <= maxNum; i++)
	{
		for (int j = i + 1; j <= maxNum; j++)
		{
			ret += (i * j);
		}
	}

	ret *= 2;


	cout << ret << endl;

	system("pause");
	return 0;
}