#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll multiply(ll a, ll b, ll c)
{
	if (b == 0)
		return 1;

	int multi = multiply(a, b / 2, c);
	if (b % 2 == 0)
		return multi * multi % c;
	else
		return ((multi * a) % c * multi) % c;
}

int main()
{
	ll a, b, c;
	cin >> a >> b >> c;

	cout << multiply(a, b, c) % c << endl;

	return 0;
}