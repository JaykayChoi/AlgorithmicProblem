#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll getRouterNumber(const int* numbers, int minLength, int n)
{
	ll ret = 1;
	int lastPos = numbers[0];
	for (int i = 1; i < n; i++)
	{
		if (numbers[i] >= lastPos + minLength)
		{
			ret++;
			lastPos = numbers[i];
		}
	}
	return ret;
}

ll binarySearch(const int* numbers, ll low, ll high, ll needNumber, ll n)
{
	ll ret = 0;
	while (low <= high)
	{
		ll mid = (low + high) / 2;
		ll routerNumber = getRouterNumber(numbers, mid, n);
		if (needNumber > routerNumber)
		{
			high = mid - 1;
		}
		else
		{
			ret = max(ret, mid);
			low = mid + 1;
		}
	}
	return ret;
}

int main()
{
	int n, c, highest;
	highest = 0;
	scanf("%d %d", &n, &c);
	int* numbers = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &numbers[i]);
		highest = max(highest, numbers[i]);
	}
	sort(numbers, numbers + n);

	printf("%d\n", binarySearch(numbers, 0, highest, c, n));

	delete[] numbers;
	return 0;
}