#pragma warning (disable:4996)
#include <stdio.h>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll getTotalLength(const int* numbers, int height, int n)
{
	ll ret = 0;
	for (int i = 0; i < n; i++)
		ret += max(0, numbers[i] - height);
	return ret;
}

int binarySearch(const int* numbers, int low, int high, ll target, int n)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		ll totalLength = getTotalLength(numbers, mid, n);
		if (totalLength == target)
			return mid;
		else if (totalLength > target)
			low = mid + 1;
		else if (target > totalLength)
			high = mid - 1;
	}

	return high;
}

int main()
{
	int n, m, lowest, hightest;
	lowest = 0;
	hightest = INT_MIN;
	scanf("%d", &n);
	scanf("%d", &m);
	int* trees = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &trees[i]);
		hightest = max(hightest, trees[i]);
	}

	printf("%d\n", binarySearch(trees, lowest, hightest, m, n));
	delete[] trees;
	return 0;
}