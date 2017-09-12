#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//https://www.acmicpc.net/problem/1002

struct Pos
{
	int x, y, r;
};

int getNumIntersection(Pos a, Pos b)
{
	double distance_centralPoints = sqrt((double)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
	int sumRedius = a.r + b.r;
	int differenceRedius = abs(a.r - b.r);

	if (a.x == b.x && a.y == b.y)
	{
		if (a.r == b.r)
			return -1;
		else
			return 0;
	}
	else if (sumRedius > distance_centralPoints && differenceRedius < distance_centralPoints)
		return 2;
	else if (sumRedius == distance_centralPoints || differenceRedius == distance_centralPoints)
		return 1;
	else
		return 0;
}

int main()
{
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++)
	{
		Pos a, b;
		cin >> a.x >> a.y >> a.r >> b.x >> b.y >> b.r;
		cout << getNumIntersection(a, b) << endl;
	}

	return 0;
}