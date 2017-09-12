#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

//https://www.acmicpc.net/problem/1003

map<int, int> cache;
int fibonacci_dp(int num)
{
	map<int, int>::iterator it = cache.find(num);
	if (it != cache.end())
		return it->second;

	int ret = 0;
	if (num == 0)
		ret = 0;
	else if (num == 1)
		ret = 1;
	else
		ret = fibonacci_dp(num - 1) + fibonacci_dp(num - 2);

	cache.insert(make_pair(num, ret));

	return ret;
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int n;
		cin >> n;
		if (n == 0)
			cout << "1 0" << endl;
		else
			cout << fibonacci_dp(n - 1) << " " << fibonacci_dp(n) << endl;
	}
	return 0;
}