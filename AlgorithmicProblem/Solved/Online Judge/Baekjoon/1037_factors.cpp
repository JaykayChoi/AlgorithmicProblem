#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;

typedef long long ll;


int main()
{
	int n;
	cin >> n;
	vector<ll> numbers;
	for (int i = 0; i < n; i++)
	{
		ll num;
		cin >> num;
		numbers.push_back(num);
	}
	sort(numbers.begin(), numbers.end());
	ll ret = numbers[0] * numbers[n - 1];
	cout << ret << endl;
	return 0;
}

