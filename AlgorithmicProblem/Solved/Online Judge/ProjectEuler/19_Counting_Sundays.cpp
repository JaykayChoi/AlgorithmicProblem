#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
//http://jaykaychoi.tistory.com/62
int calcDaysOfMonth(int month, int year)
{
	switch (month)
	{
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return 29;
		else
			return 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}

int main()
{
	//1.1.1901 is Tuesday
	int now = 2;
	int ret = 0;
	for (int i = 1901; i < 2001; i++)
	{
		for (int month = 1; month < 13; month++)
		{
			if ((now + 1) % 7 == 00)
				ret++;
			now = (now + calcDaysOfMonth(month, i)) % 7;
		}
	}

	cout << ret << endl;
	system("pause");
	return 0;
}