#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//http://jaykaychoi.tistory.com/67

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
	vector<int> abundants;

	for (int i = 1; i <= 28123; i++)
	{
		int sum = sumProperDivisors(i);

		if (i < sum)
			abundants.push_back(i);
	}

	bool isSumAbundant[28124];
	memset(isSumAbundant, 0, sizeof(isSumAbundant));

	for (int i = 0; i < abundants.size(); i++)
	{
		for (int j = i; j < abundants.size(); j++)
		{
			if (abundants[i] + abundants[j] <= 28123)
				isSumAbundant[abundants[i] + abundants[j]] = true;
			else
				break;
		}
	}


	for (int i = 1; i <= 28123; i++)
	{
		if (isSumAbundant[i] == false)
			ret += i;
	}

	cout << ret << endl;
	system("pause");
	return 0;
}