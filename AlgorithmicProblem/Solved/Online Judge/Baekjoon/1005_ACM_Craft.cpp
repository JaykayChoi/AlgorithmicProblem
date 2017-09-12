#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

//https://www.acmicpc.net/problem/1005

multimap<int, int> techTrees;
vector<int> buildingTimes;
int cache[1001];

//It used more than the allotted runtime
int bruteForce(int target, int sum)
{
	multimap<int, int>::iterator it = techTrees.find(target);

	if (it == techTrees.end())
		return sum;

	int ret = 0;
	pair< multimap<int, int>::iterator, multimap<int, int>::iterator > p = techTrees.equal_range(target);
	for (it = p.first; it != p.second; it++)
	{
		ret = max(ret, bruteForce(it->second, sum + buildingTimes[it->second]));
	}
	return ret;
}

int dp(int target)
{
	multimap<int, int>::iterator it = techTrees.find(target);

	if (it == techTrees.end())
		return 0;

	int& ret = cache[target];
	if (ret != -1)
		return ret;

	pair< multimap<int, int>::iterator, multimap<int, int>::iterator > p = techTrees.equal_range(target);
	for (it = p.first; it != p.second; it++)
	{
		int candidate = buildingTimes[it->second] + dp(it->second);
		ret = max(ret, candidate);
	}
	return ret;
}

int main()
{
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++)
	{
		techTrees.clear();
		buildingTimes.clear();
		int numBuilding, numTechTree, targetBuilding;
		cin >> numBuilding >> numTechTree;

		for (int i = 0; i < numBuilding; i++)
		{
			int num;
			cin >> num;
			buildingTimes.push_back(num);
		}

		for (int i = 0; i < numTechTree; i++)
		{
			int a, b;
			cin >> a >> b;
			techTrees.insert(make_pair(b - 1, a - 1));
		}

		cin >> targetBuilding;
		memset(cache, -1, sizeof(cache));
		int ret = buildingTimes[targetBuilding - 1] + dp(targetBuilding - 1);
		cout << ret << endl;
	}

	return 0;
}

