#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

bool isChanged(int x, int y, ll mid)
{
	ll oldValue = (ll)y * 100 / x;
	ll newValue = (mid + (ll)y) * 100 / (x + mid);
	return newValue != oldValue;
}

int binarySearch(int x, int y)
{
	ll low, high, ret;
	low = 0;
	high = ret = x;
	while (low <= high)
	{
		ll mid = (low + high) / 2;
		if (!isChanged(x, y, mid))
		{
			low = mid + 1;
		}
		else
		{
			ret = min(ret, mid);
			high = mid - 1;
		}
	}
	return ret;
}

int main()
{
	int x, y;
	while (scanf("%d %d", &x, &y) != EOF)
	{
		if ((ll)y * 100 / x >= 99LL)
			printf("-1\n");
		else
			printf("%d\n", binarySearch(x, y));
	}
	return 0;
}