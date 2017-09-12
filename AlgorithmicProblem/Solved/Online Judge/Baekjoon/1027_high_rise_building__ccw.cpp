#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;
//https://www.acmicpc.net/problem/1027
#pragma region using ccw
struct vector2
{
	double x, y;

	vector2(int x1, int y1, int x2, int y2)
	{
		x = x2 - x1;
		y = y2 - y1;
	}

	double outerProduct(const vector2& b) const
	{
		return x * b.y - y * b.x;
	}
};

double getOuterProduct(int oriX, int oriY, int aX, int aY, int bX, int bY)
{
	vector2 a(oriX, oriY, aX, aY);
	vector2 b(oriX, oriY, bX, bY);
	return a.outerProduct(b);
}
#pragma endregion

int main()
{
	int n;
	cin >> n;

	vector<int> heights;

	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		heights.push_back(num);
	}

	int ret = 0;
#pragma region using ccw (80% 정도에서 오답처리 됨)
	for (int origin = 0; origin < n; origin++)
	{
		int sum = 2;
		if (origin == 0 || origin == n - 1)
			sum--;
		for (int leftTarget = origin - 2; leftTarget >= 0; leftTarget--)
		{
			bool ok = true;
			for (int leftBlock = leftTarget + 1; leftBlock < origin; leftBlock++)
			{
				if (getOuterProduct(origin, heights[origin], leftBlock, heights[leftBlock], leftTarget, heights[leftTarget]) >= 0)
				{
					ok = false;
					break;
				}
			}
			if (ok)
				sum++;
		}
		for (int rightTarget = origin + 2; rightTarget < n; rightTarget++)
		{
			bool ok = true;
			for (int rightBlock = rightTarget - 1; rightBlock > origin; rightBlock--)
			{
				if (getOuterProduct(origin, heights[origin], rightBlock, heights[rightBlock], rightTarget, heights[rightTarget]) <= 0)
				{
					ok = false;
					break;
				}
			}
			if (ok)
				sum++;
		}
		ret = max(ret, sum);
	}
#pragma endregion

	for (int origin = 0; origin < n; origin++)
	{
		int sum = 0;
		double maxSlope = -1 * INT_MAX;

		for (int leftTarget = origin - 1; leftTarget >= 0; leftTarget--)
		{
			double slope = (double)(heights[leftTarget] - heights[origin]) / abs(leftTarget - origin);
			if (slope > maxSlope)
			{
				maxSlope = slope;
				sum++;
			}
		}

		maxSlope = -1 * INT_MAX;
		for (int rightTarget = origin + 1; rightTarget < n; rightTarget++)
		{
			double slope = (double)(heights[rightTarget] - heights[origin]) / abs(rightTarget - origin);
			if (slope > maxSlope)
			{
				maxSlope = slope;
				sum++;
			}
		}
		ret = max(ret, sum);
	}

	cout << ret << endl;

	return 0;
}