#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;


int main()
{
	int cases, n, minSum;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		cin >> n;
		int *arr = new int[n];
		for (int i = 0; i < n; i++)
			cin >> arr[i];

		for (int i = 0; i < n; i++)
		{
			minSum = 0;
			for (int j = 0; j <= i; j++)
				minSum += arr[j];

			int k, curSum = 0;
			for (k = i + 1; k < n; k++)
			{
				curSum += arr[k];
				if (curSum == minSum)
					curSum = 0;
				else if (curSum > minSum)
					break;
			}
			if (k == n && curSum == 0)
				break;
		}


		cout << minSum << endl;
		delete[] arr;
	}

	return 0;
}