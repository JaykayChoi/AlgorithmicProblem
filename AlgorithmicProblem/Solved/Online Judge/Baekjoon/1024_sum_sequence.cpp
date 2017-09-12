#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1024

ll sum(ll startNum, int n)
{
	if (n % 2 == 1)
		return sum(startNum + 1, n - 1) + startNum;

	return (startNum * 2 + n - 1) * (n / 2);
}

int main()
{
	ll n;
	int l;
	cin >> n >> l;

	int ret = -1;
	int ret2 = 0;

	for (int i = l; i <= 100; i++)
	{
		ll start = (n / i) + (i / 2) - i + 1;
		if (start < 0)
			continue;
		if (sum(start, i) == n)
		{
			ret = start;
			ret2 = i;
			break;
		}
	}

	if (ret != -1)
	{
		for (int i = 0; i < ret2; i++)
		{
			if (i != 0)
				cout << " ";
			cout << i + ret;
		}
	}
	else
		cout << -1;
	cout << endl;

	return 0;
}