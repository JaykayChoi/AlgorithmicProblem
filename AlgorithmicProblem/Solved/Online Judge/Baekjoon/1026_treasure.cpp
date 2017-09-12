#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1026

int main()
{
	int n;
	cin >> n;

	vector<int> a, b;
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < n; i++)
		{
			int num;
			cin >> num;
			if (k == 0)
				a.push_back(num);
			else
				b.push_back(num);
		}
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	int ret = 0;
	for (int i = 0; i < n; i++)
		ret += (a[i] * b[n - i - 1]);

	cout << ret << endl;

	return 0;
}