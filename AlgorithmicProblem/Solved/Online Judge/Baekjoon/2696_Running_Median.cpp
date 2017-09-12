#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <set>
using namespace std;

int main()
{
	int cases, m, n;
	multiset<int> numbers;
	multiset<int>::iterator iter;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		cin >> m;
		int* arr = new int[m];
		for (int i = 0; i < m; i++)
			cin >> arr[i];
		int n = m / 2 + 1;
		cout << n << endl;
		numbers.clear();
		for (int i = 0; i < m; i += 2)
		{
			if (i != 0)
				numbers.insert(arr[i - 1]);
			numbers.insert(arr[i]);
			iter = numbers.begin();
			for (int j = 1; j <= i / 2; j++)
				iter++;
			cout << *iter;
			if (i != 0 && (i + 2) % 20 == 0 && i != m - 1)
				cout << endl;
			else if (i != m - 1)
				cout << " ";
		}
		cout << endl;
		delete[] arr;
	}

	return 0;
}