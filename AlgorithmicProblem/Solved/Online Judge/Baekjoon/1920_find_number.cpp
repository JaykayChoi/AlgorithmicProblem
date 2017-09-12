#pragma warning (disable:4996)
#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int binarySearch(const int* numbers, int target, int n)
{
	int low = 0;
	int high = n - 1;

	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (numbers[mid] > target)
			high = mid - 1;
		else if (target > numbers[mid])
			low = mid + 1;
		else if (numbers[mid] == target)
			return 1;
	}

	return 0;
}

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int main()
{
	int n, m, num;
	scanf("%d", &n);
	int* numbers = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	//qsort(numbers, n, sizeof(int), compare);
	sort(numbers, numbers + n);
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &num);
		printf("%d\n", binarySearch(numbers, num, n));
	}
	delete[] numbers;
	return 0;
}