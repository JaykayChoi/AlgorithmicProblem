#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
//https://www.acmicpc.net/problem/1012

const int UNIT = 100;

set<int> points;
int maxPosition;

int getNextPosition(int position, int direction)
{
	int ret = position;
	switch (direction)
	{
	case 0:
		ret -= UNIT;
		break;
	case 1:
		ret++;
		break;
	case 2:
		ret += UNIT;
		break;
	case 3:
		ret--;
		break;
	default:
		break;
	}

	if (ret < 0 || ret > maxPosition)
		return -1;
	return ret;
}

void recursive(int position)
{
	points.erase(position);
	for (int i = 0; i < 4; i++)
	{
		int temp = getNextPosition(position, i);

		if (temp != -1)
		{
			set<int>::iterator it = points.find(temp);
			if (it != points.end())
				recursive(temp);
		}
	}
}

int solve()
{
	int ret = 0;
	while (true)
	{
		if (points.empty())
			break;

		ret++;
		set<int>::iterator it = points.begin();
		recursive(*it);
	}

	return ret;
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int m, n, k;
		points.clear();
		cin >> m >> n >> k;
		maxPosition = m - 1 + (n - 1) * UNIT;
		for (int i = 0; i < k; i++)
		{
			int x, y;
			cin >> x >> y;
			points.insert(x + y * UNIT);
		}

		cout << solve() << endl;
	}

	return 0;
}
