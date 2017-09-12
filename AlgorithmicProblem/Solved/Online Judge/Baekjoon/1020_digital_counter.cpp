#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1020

const int segments[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 5 };

int n, targetSegmentNum;
ll startNum, lastNum;

int getSegmentNum(ll number)
{
	int ret = 0;
	int remaining = n;
	while (number > 0)
	{
		remaining--;
		ret += segments[number % 10];
		number /= 10;
	}
	ret += (segments[0] * remaining);

	return ret;
}

int bruteForce(ll number)
{
	int changedSegmentNum = -1;
	int ret = 0;
	while (changedSegmentNum != targetSegmentNum)
	{
		ret++;
		if (number == lastNum)
			number = 0;
		else
			number++;
		changedSegmentNum = getSegmentNum(number);
	}
	return ret;
}

int main()
{
	string strStartNum = "111111111111111";
	//cin >> strStartNum;

	n = strStartNum.size();
	startNum = stoll(strStartNum);
	lastNum = pow(10, n) - 1;

	for (int i = 0; i < n; i++)
		targetSegmentNum += segments[strStartNum[i] - '0'];

	cout << bruteForce(startNum) << endl;

	return 0;
}
