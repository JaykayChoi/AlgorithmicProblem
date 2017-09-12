#pragma warning (disable:4996)
#include <stdio.h>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
typedef long long ll;

int main()
{
	ll a, b, v;
	scanf("%d %d %d", &a, &b, &v);
	ll ret = 1 + (v - a) / (a - b);
	if ((v - a) % (a - b) != 0)
		ret++;
	printf("%d\n", ret);

	return 0;
}