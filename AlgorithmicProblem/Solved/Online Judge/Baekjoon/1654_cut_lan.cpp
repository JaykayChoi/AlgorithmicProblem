#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

ll getLineNumber(const int* numbers, int length, int n)
{
	ll ret = 0;
	for (int i = 0; i < n; i++)
		ret += numbers[i] / length;
	return ret;
}

ll binarySearch(const int* numbers, ll low, ll high, ll needNumber, ll n)
{
	ll ret = 0;
	while (low <= high)
	{
		ll mid = (low + high) / 2;
		ll lineNumber = getLineNumber(numbers, mid, n);
		if (needNumber > lineNumber)
		{
			high = mid - 1;
		}
		else
		{
			ret = max(ret, mid);
			low = mid + 1;
		}
	}
	return ret;
}

int main()
{
	int n, needNumber;
	ll lowest, hightest;
	lowest = hightest = 0;
	scanf("%d %d", &n, &needNumber);
	int* lengths = new int[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &lengths[i]);
		hightest = max(hightest, (ll)lengths[i]);
	}

	printf("%d\n", binarySearch(lengths, lowest, hightest, needNumber, n));
	delete[] lengths;
	return 0;
}