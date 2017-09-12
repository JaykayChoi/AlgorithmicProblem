#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

//https://projecteuler.net/problem=3

vector<ll> getPrimeFactor(ll n)
{
	vector<ll> ret;
	ll sqrtn = ll(sqrt(n));

	for (ll i = 2; i <= sqrtn; i++)
	{
		while (n % i == 0)
		{
			n /= i;
			ret.push_back(i);
		}
	}

	if (n > 1)
		ret.push_back(n);
	return ret;
}

int submain()
{
	vector<ll> frimes = getPrimeFactor(600851475143);

	cout << frimes.back() << endl;

	system("pause");
	return 0;
}