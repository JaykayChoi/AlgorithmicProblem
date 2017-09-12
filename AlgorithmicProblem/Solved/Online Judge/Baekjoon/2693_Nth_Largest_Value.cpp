#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int compare(const void * a, const void * b)
{
	return (*(int*)a - *(int*)b);
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int arr[10] = { 0, };
		for (int j = 0; j < 10; j++)
			cin >> arr[j];
		qsort(arr, 10, sizeof(int), compare);
		cout << arr[7] << endl;
	}

	return 0;
}