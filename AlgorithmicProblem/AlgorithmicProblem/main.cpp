#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/6236
//https://www.acmicpc.net/problem/2343

ll getNeedNum(const int* numbers, ll length, int n)
{
	ll ret = 0;
	ll accumulated = 0;
	for (int i = 0; i < n; i++)
	{
		if (numbers[i] > length)
		{
			return -1;
		}
		if (accumulated + numbers[i] < length)
		{
			accumulated += numbers[i];
		}
		else if (accumulated + numbers[i] == length)
		{
			accumulated = 0;
			ret++;
		}
		else 
		{
			accumulated = numbers[i];
			ret++;
		}
	}
	if (accumulated > 0)
	{
		ret++;
	}
	return ret;
}
int binarySearch(const int* numbers, int low, ll high, int n, int m)
{
	while (low + 1 < high)
	{
		ll mid = (low + high) / 2;
		ll needNum = getNeedNum(numbers, mid, n);
		if (needNum == -1 || needNum > m)
		{
			low = mid;
		}
		else
		{
			high = mid;
		}
	}
	return high;
}

int main()
{
	int n, m;

	scanf("%d", &n);
	scanf("%d", &m);

	int* minutes = new int[n];
	ll sum = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &minutes[i]);
		sum += minutes[i];
	}

	printf("%d\n", binarySearch(minutes, 1, sum, n, m));

	delete[] minutes;
	return 0;
}