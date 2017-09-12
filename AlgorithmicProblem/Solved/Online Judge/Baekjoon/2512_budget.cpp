#pragma warning (disable:4996)
#include <stdio.h>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll getSumBudget(const int* numbers, int maxBudget, int n)
{
	ll ret = 0;
	for (int i = 0; i < n; i++)
		ret += min(numbers[i], maxBudget);
	return ret;
}

int binarySearch(const int* numbers, int low, int high, ll totalBudget, int n)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		ll sumBudget = getSumBudget(numbers, mid, n);
		if (sumBudget == totalBudget)
			return mid;
		else if (sumBudget > totalBudget)
			high = mid - 1;
		else if (totalBudget > sumBudget)
			low = mid + 1;
	}

	return high;
}

int main()
{
	int n, lowest, hightest, totalBudget;
	lowest = 0;
	hightest = INT_MIN;
	scanf("%d", &n);
	int* budgets = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &budgets[i]);
		hightest = max(hightest, budgets[i]);
	}
	scanf("%d", &totalBudget);

	printf("%d\n", binarySearch(budgets, lowest, hightest, totalBudget, n));
	delete[] budgets;
	return 0;
}