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
	//������ ��.
	int cityNum;

	//�� ���� ���� �Ÿ�.
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

	//path : ���ݱ��� ���� ���
	//visited : �� ������ �湮 ����
	//currentLength : ���ݱ��� ���� ����� ����
	//������ ���õ��� ��� �湮�ϴ� ��ε� �� ���� ª�� ���� ���̸� ��ȯ�Ѵ�.
	double shortestPath(vector<int>& _path, vector<bool>& _visited, double _currentLength)
	{
		//��� ���ø� �� �湮���� ���� ���� ���÷� ���ư��� ����.
		if (_path.size() == cityNum)
			return _currentLength + dist[_path[0]][_path.back()];

		//�ſ� ū ������ �ʱ�ȭ.
		double ret = 987654321;
			//numeric_limits<long>::max();

		//���� �湮�� ���ø� ���� �õ��غ���.
		for (int next = 0; next < cityNum; next++)
		{
			if (_visited[next])
				continue;

			int here = _path.back();
			_path.push_back(next);
			_visited[next] = true;

			//������ ��θ� ��� ȣ���� ���� �ϼ��ϰ� ���� ª�� ����� ���̸� ��´�.
			double cand = shortestPath(_path, _visited, _currentLength + dist[here][next]);
			ret = min(ret, cand);
			_visited[next] = false;
			_path.pop_back();
		}
		return ret;
	}
};