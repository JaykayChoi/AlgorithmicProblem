#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;
typedef long long ll;

bool canHandle(const vector<int>& numbers, ll time, int people)
{
	ll count = 0;
	for (auto& elem : numbers)
		count += time / elem;
	return count >= people;
}

ll binarySearch(const vector<int>& numbers, ll low, ll high, int people)
{
	ll ret = high;
	while (low <= high)
	{
		ll mid = (low + high) / 2;
		if (!canHandle(numbers, mid, people))
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
	int n, people, lowest, highest;
	lowest = INT_MAX;
	highest = 0;
	scanf("%d %d", &n, &people);
	vector<int> numbers(n, 0);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &numbers[i]);
		lowest = min(lowest, numbers[i]);
		highest = max(highest, numbers[i]);
	}

	printf("%lld\n", binarySearch(numbers, (ll)lowest * people / n, (ll)highest * people / n, people));
	return 0;
}