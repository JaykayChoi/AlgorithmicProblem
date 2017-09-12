#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//http://jaykaychoi.tistory.com/admin/entry/post/?id=65

int sumProperDivisors(int number)
{
	int ret = 1;
	int sqrtn = sqrt(number);
	for (int i = 2; i <= sqrtn; i++)
	{
		if (number % i == 0)
		{
			ret += i;
			int pairNum = number / i;
			if (pairNum != i)
				ret += pairNum;
		}
	}
	return ret;
}

int main()
{
	int ret = 0;

	for (int i = 2; i <= 10000; i++)
	{
		int sum = sumProperDivisors(i);

		if (i == sumProperDivisors(sum) && i != sum)
			ret += i;
	}
	cout << ret << endl;
	system("pause");
	return 0;
}