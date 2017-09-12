#pragma warning (disable:4996)
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;

int main()
{
	int n, h, num;
	scanf("%d %d", &n, &h);
	vector<int> bottom(h + 1, 0);
	vector<int> top(h + 1, 0);
	vector<int> sorted(h, 0);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num);
		if (i % 2 == 0)
			bottom[num]++;
		else
			top[num]++;
	}
	for (int i = h - 1; i > 1; i--)
	{
		bottom[i - 1] += bottom[i];
		top[i - 1] += top[i];
	}

	for (int i = 1; i <= h; i++)
		sorted[i - 1] = bottom[i] + top[h - i + 1];

	sort(sorted.begin(), sorted.end());

	int count = 1;
	for (int i = 1; i < h; i++)
	{
		if (sorted[0] == sorted[i])
			count++;
		else
			break;
	}
	printf("%d %d\n", sorted[0], count);
	return 0;
}