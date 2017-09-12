#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll cache[91][2];
ll getPinaryNumber(int digit, int num)
{
	if (digit == 1)
		return 1;

	ll& ret = cache[digit][num];
	if (ret != 0)
		return ret;

	if (num == 1)
		ret += getPinaryNumber(digit - 1, 0);
	else
		ret += getPinaryNumber(digit - 1, 1) + getPinaryNumber(digit - 1, 0);

	return ret;
}

int main()
{
	int digit;
	cin >> digit;
	memset(cache, 0, sizeof(cache));
	cout << getPinaryNumber(digit, 1) << endl;

	return 0;
}