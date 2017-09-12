#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
using namespace std;

struct Point
{
	int x, y;
};

struct Answer
{
	int y, x1, x2;
	Answer(int _y, int _x1, int _x2) : y(_y), x1(_x1), x2(_x2) {}
};

Point p0;

int distSq(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// 0: p, q and r are colinear
// 1: Clockwise
// 2: Counterclockwise
int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0)
		return 0;
	return (val > 0) ? 1 : 2;
}

int compare(const void *vp1, const void *vp2)
{
	Point *p1 = (Point *)vp1;
	Point *p2 = (Point *)vp2;

	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

	return (o == 2) ? -1 : 1;
}

int convexHull(Point points[], int n, int x, int y, int& selectedIndex)
{
	p0 = points[0];
	qsort(&points[1], n - 1, sizeof(Point), compare);

	for (int i = 1; i < n; i++)
	{
		if (points[i].x == x && points[i].y == y)
		{
			selectedIndex = i;
			int nextIndex = i + 1;
			if (nextIndex == n)
				nextIndex = 0;
			return orientation(points[i - 1], points[i], points[nextIndex]);
		}
	}
}

bool isBoundaryPoints(vector<Point>& boundaryPoints, int y, int x)
{
	for (auto& elem : boundaryPoints)
	{
		if (elem.x == x && elem.y == y)
			return true;
	}
	return false;
}

void calcBoundaryPoints(vector<Point>& boundaryPoints, Point* points, int n)
{
	for (int i = 0; i < n; i++)
	{
		int nextIndex = i + 1;
		if (i == n - 1)
			nextIndex = 0;

		int diffX = points[i].x - points[nextIndex].x;
		int diffY = points[i].y - points[nextIndex].y;
		if (diffX == 0 || diffY == 0 || max(abs(diffX), abs(diffY)) % min(abs(diffX), abs(diffY)) == 0)
		{
			if (diffX == 0)
			{
				diffY /= abs(diffY);
			}
			else if (diffY == 0)
			{
				diffX /= abs(diffX);
			}
			else
			{
				int slope = min(abs(diffX), abs(diffY));
				diffX /= slope;
				diffY /= slope;
			}

			int count = 1;
			while (true)
			{
				Point newPoint;
				newPoint.x = points[i].x - diffX * count;
				newPoint.y = points[i].y - diffY * count;
				if (points[nextIndex].x == newPoint.x && points[nextIndex].y == newPoint.y)
					break;
				boundaryPoints.push_back(newPoint);
				count++;
			}
		}
	}
}

int main()
{
	int cases, n, k;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		int n;
		cin >> n;
		Point* points = new Point[n + 1];
		vector<Point> boundaryPoints;
		vector<Answer> ret;
		int minY = INT_MAX;
		int minX = INT_MAX;
		int maxX = INT_MIN;
		for (int i = 0; i < n; i++)
		{
			cin >> points[i].x >> points[i].y;
			boundaryPoints.push_back(points[i]);
			minY = min(minY, points[i].y);
			minX = min(minX, points[i].x);
			maxX = max(maxX, points[i].x);
		}
		calcBoundaryPoints(boundaryPoints, points, n);
		int selectedIndex = n;
		for (int y = points[0].y - 1; y > minY; y--)
		{
			for (int x = minX + 1; x < maxX; x++)
			{
				if (isBoundaryPoints(boundaryPoints, y, x))
					continue;
				points[selectedIndex].x = x;
				points[selectedIndex].y = y;
				int ori = convexHull(points, n + 1, x, y, selectedIndex);
				if (ori == 1)
				{
					int x2 = x + 1;
					for (; x2 < maxX; x2++)
					{
						if (isBoundaryPoints(boundaryPoints, y, x2))
							break;
						points[selectedIndex].x = x2;
						points[selectedIndex].y = y;
						ori = convexHull(points, n + 1, x2, y, selectedIndex);
						if (ori != 1)
							break;
					}

					Answer answer(y, x, x2 - 1);
					ret.push_back(answer);

					break;
				}
			}
		}
		cout << ret.size() << endl;
		for (auto& ans : ret)
		{
			cout << ans.y << " " << ans.x1 << " " << ans.x2 << endl;
		}
		delete[] points;
	}

	return 0;
}