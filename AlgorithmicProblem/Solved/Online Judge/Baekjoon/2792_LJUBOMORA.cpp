#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;
typedef long long ll;

bool canDivide(vector<int> colors, ll mid, int n)
{
	ll count = 0;
	for (auto& e : colors)
	{
		while (true)
		{
			ll division = min(mid, (ll)e);
			if (division == 0)
				break;
			ll quotient = e / division;
			if (quotient > 0)
			{
				count += quotient;
				if (count > n)
					return false;
				e -= quotient * division;
			}
		}
	}
	return true;
}

int binarySearch(vector<int>& colors, ll high, int n)
{
	ll low = 1;
	ll ret = high;

	while (low <= high)
	{
		ll mid = (low + high) / 2;
		if (!canDivide(colors, mid, n))
		{
			low = mid + 1;
		}
		else
		{
			ret = min(ret, mid);
			high = mid - 1;
		}
	}
	return ret;
}

int main()
{
	int n, m, highest;
	highest = 0;
	scanf("%d %d", &n, &m);
	vector<int> colors(m, 0);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &colors[i]);
		highest = max(highest, colors[i]);
	}

	printf("%d\n", binarySearch(colors, highest, n));

	return 0;
}