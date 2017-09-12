#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll cache[10][65];
ll getCount(int n, int digit)
{
	if (digit == 1)
	{
		return 1;
	}

	ll& ret = cache[n][digit];
	if (ret != -1)
		return ret;
	ll sum = 0;
	for (int i = 0; i <= n; i++)
	{
		sum += getCount(i, digit - 1);
	}
	ret = sum;
	return ret;
}

int main()
{
	memset(cache, -1, sizeof(cache));
	int cases, n;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		cin >> n;
		ll ret = 0;
		for (int i = 0; i < 10; i++)
		{
			ret += getCount(i, n);
		}
		cout << ret << endl;
	}

	return 0;
}