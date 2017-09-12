#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
//https://www.acmicpc.net/problem/1030
int s, n, k;
int length;

int getColor(int y, int x)
{
	if (y == 1)
		int temp = 0;
	int unit = length / n;
	int border = (n - k) / 2;
	while (unit > 0)
	{
		if (y / unit >= border && y / unit <= n - 1 - border && x / unit >= border && x / unit <= n - 1 - border)
			return 1;

		if (y >= unit)
			y %= unit;
		if (x >= unit)
			x %= unit;
		unit /= n;
	}
	return 0;
}

int main()
{
	int r1, r2, c1, c2;
	cin >> s >> n >> k >> r1 >> r2 >> c1 >> c2;

	length = pow(n, s);

	for (int y = r1; y <= r2; y++)
	{
		for (int x = c1; x <= c2; x++)
			cout << getColor(y, x);

		cout << endl;
	}

	return 0;
}