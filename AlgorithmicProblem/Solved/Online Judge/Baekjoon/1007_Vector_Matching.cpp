#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip> 
using namespace std;
typedef long long ll;

//https://www.acmicpc.net/problem/1007
struct Pos
{
	int x, y;
};

int n;
ll _sumX, _sumY;
vector<Pos> points;


double bruteForce(int start, int remaining, int sumX, int sumY, vector<int>& selected)
{
	if (remaining == 0)
		return sqrt(pow(_sumX - sumX * 2, 2) + pow(_sumY - sumY * 2, 2));

	double ret = -1;
	for (int i = start; i <= points.size() - remaining; ++i)
	{
		selected.push_back(i);
		double candidate = bruteForce(i + 1, remaining - 1, sumX + points[i].x, sumY + points[i].y, selected);
		if (candidate < ret || ret == -1)
			ret = candidate;
		selected.pop_back();
	}
	return ret;
}


int main()
{
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++)
	{
		points.clear();
		_sumX = _sumY = 0;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			_sumX += x;
			_sumY += y;

			Pos pos;
			pos.x = x;
			pos.y = y;
			points.push_back(pos);
		}

		vector<int> temp;
		cout << fixed << setprecision(6) << bruteForce(0, n / 2, 0, 0, temp) << endl;
	}

	return 0;
}
