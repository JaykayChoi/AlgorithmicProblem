#include<cassert>
#include<vector>
#include<iostream>
#include<cstring>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include "Utils.h"
#include <ctime>
using namespace std;

//https://en.wikipedia.org/wiki/Travelling_salesman_problem

class TravelingSalesMan_6_7
{
public:
	void Solve()
	{
		input();
		vector<int> path;
		path.push_back(0);
		vector<bool> visited(10, false);
		visited[0] = true;
		clock_t start = clock();
		cout << shortestPath(path, visited, 0) << endl;
		clock_t end = clock();
		double time = double(end - start) / CLOCKS_PER_SEC;

		cout << "Time (s): " << time << endl;
	}
private:
	//도시의 수.
	int cityNum;

	//두 도시 간의 거리.
	double dist[10][10];

	void input()
	{
		string filePath = "TravelingSalesMan_Input.txt";
		vector<string> vInputLines = Utils::GetLine_InputFile(filePath);

		cityNum = stoi(vInputLines[0]);

		int rootNum = 0;
		for (int i = cityNum - 1; i > 0; i--)
			rootNum += i;
		string delimiter = " ";
		vector<int> vInputCitys = Utils::SplitStringToInt(vInputLines[1], delimiter);
		vector<int> vInputDistances = Utils::SplitStringToInt(vInputLines[2], delimiter);

		memset(dist, 0, sizeof(dist));

		for (int i = 0; i < rootNum; i++)
		{
			dist[vInputCitys[2 * i]][vInputCitys[2 * i + 1]] = vInputDistances[i];
			dist[vInputCitys[2 * i + 1]][vInputCitys[2 * i]] = vInputDistances[i];
		}
	}

	//path : 지금까지 만든 경로
	//visited : 각 도시의 방문 여부
	//currentLength : 지금까지 만든 경로의 길이
	//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
	double shortestPath(vector<int>& _path, vector<bool>& _visited, double _currentLength)
	{
		//모든 도시를 다 방문했을 때는 시작 도시로 돌아가고 종료.
		if (_path.size() == cityNum)
			return _currentLength + dist[_path[0]][_path.back()];

		//매우 큰 값으로 초기화.
		double ret = 987654321;
			//numeric_limits<long>::max();

		//다음 방문할 도시를 전부 시도해본다.
		for (int next = 0; next < cityNum; next++)
		{
			if (_visited[next])
				continue;

			int here = _path.back();
			_path.push_back(next);
			_visited[next] = true;

			//나머지 경로를 재귀 호출을 통해 완성하고 가장 짧은 경로의 길이를 얻는다.
			double cand = shortestPath(_path, _visited, _currentLength + dist[here][next]);
			ret = min(ret, cand);
			_visited[next] = false;
			_path.pop_back();
		}
		return ret;
	}
};