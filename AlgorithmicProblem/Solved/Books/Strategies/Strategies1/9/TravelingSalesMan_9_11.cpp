#include "Utils.h"
using namespace std;
using namespace Utils;

//여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘 

const int MAX = 20;
class TravelingSalesMan_9_11
{
public:

private:

#pragma region answer
	int n, dist[MAX][MAX];
	double cache[MAX][1 << MAX];	//-1로 초기화 해야 됨.

	//here 현재 위치
	//visited 각 도시의 방문 여부
	//here 에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
	//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길으를 반환한다.
	//항상 0번 도시에서 시작한다고 가정한다.
	double shortestPath2(int here, int visited)
	{
		//모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
		if (visited == (1 << n) - 1)
			return dist[here][0];

		//memoization
		double& ret = cache[here][visited];
		if (ret >= 0)
			return ret;
		ret = 987654321;

		//다음 방문할 도시를 전부 시도해 본다.
		for (int next = 0; next < n; next++)
		{
			//이미 방문한 도시인 경우.
			if (visited & (1 << next))
				continue;

			double cand = dist[here][next] + shortestPath2(next, visited + (1 << next));

			ret = min(ret, cand);
		}
		return ret;
	}
#pragma endregion



#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
	using namespace std;


	const int MAX_CITY = 20;

	int numCity;
	double distances[MAX_CITY][MAX_CITY];

#pragma region dynamic programming
	double cache[MAX_CITY][1 << MAX_CITY];
#pragma endregion

#pragma region bruteForce
	double bruteForce(vector<int>& visitedCity, vector<bool>& isVisited, double curLength)
	{
		if (visitedCity.size() == numCity)
			return curLength + distances[visitedCity.back()][visitedCity[0]];

		double ret = 987654321;

		for (int next = 0; next < numCity; next++)
		{
			if (isVisited[next])
				continue;

			int here = visitedCity.back();
			visitedCity.push_back(next);
			isVisited[next] = true;

			double length = bruteForce(visitedCity, isVisited, curLength + distances[here][next]);
			ret = min(ret, length);

			isVisited[next] = false;
			visitedCity.pop_back();
		}

		return ret;
	}
#pragma endregion


#pragma region dynamic programming
	double dynamicProgramming(int here, int visitedCity)
	{
		if (visitedCity == (1 << numCity) - 1)
			return distances[here][0];

		double& ret = cache[here][visitedCity];

		if (ret >= 0)
			return ret;

		ret = 987654321;

		for (int next = 0; next < numCity; next++)
		{
			if (visitedCity & (1 << next))
				continue;

			double length = dynamicProgramming(next, visitedCity + (1 << next)) + distances[here][next];

			ret = min(ret, length);
		}

		return ret;
	}
#pragma endregion

	int sub_main()
	{
		//10 cities
		ifstream fin("input.in");

		fin >> numCity;

		memset(distances, 0, sizeof(distances));

		for (int i = 0; i < numCity; i++)
		{
			for (int j = i + 1; j < numCity; j++)
			{

				double dist1;
				fin >> dist1;
				distances[i][j] = distances[j][i] = dist1;
			}
		}

#pragma region bruteForce
		vector<int> visitedCity;
		visitedCity.push_back(0);
		vector<bool> isVisited(numCity, false);
		isVisited[0] = true;

		clock_t start = clock();
		cout << "bruteForce : " << bruteForce(visitedCity, isVisited, 0);

		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC;
		cout << " elapse time(s): " << time << endl;
#pragma endregion


#pragma region dynamic programming
		memset(cache, -1, sizeof(cache));

		start = clock();
		cout << "dynamicProgramming : " << dynamicProgramming(0, 0);

		end = clock();
		time = double(end - start) / CLOCKS_PER_SEC;
		cout << " elapse time(s): " << time << endl;
#pragma endregion

		system("pause");
		return 0;
	}

};
