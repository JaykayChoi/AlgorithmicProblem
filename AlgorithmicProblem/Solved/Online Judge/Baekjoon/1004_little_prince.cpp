#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//https://www.acmicpc.net/problem/1004

struct Pos
{
	int x, y, r;
};

bool whetherAEncloseB(Pos a, Pos b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) < a.r * a.r;
}

int main()
{
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++)
	{
		Pos start, goal, planet;
		int ret = 0;
		int numPlanet;
		cin >> start.x >> start.y >> goal.x >> goal.y;
		cin >> numPlanet;

		for (int j = 0; j < numPlanet; j++)
		{
			cin >> planet.x >> planet.y >> planet.r;

			bool isStartEnclosed, isGoalEnclosed;
			isStartEnclosed = whetherAEncloseB(planet, start);
			isGoalEnclosed = whetherAEncloseB(planet, goal);

			if (isStartEnclosed == isGoalEnclosed)
				continue;
			if (isStartEnclosed || isGoalEnclosed)
				ret++;
		}
		cout << ret << endl;
	}

	return 0;
}