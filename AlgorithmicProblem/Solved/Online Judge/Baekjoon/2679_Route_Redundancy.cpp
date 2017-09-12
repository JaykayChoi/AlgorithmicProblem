#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <vector>
#include <queue>
#include <iomanip> 
using namespace std;

const int MAX_N = 1000;
int capacity[MAX_N][MAX_N];
int flow[MAX_N][MAX_N];
int N, source, sink;

int getMaxFlow_dfs(int here, int minFlow, vector<bool>& visited)
{
	if (here == sink)
		return minFlow;

	int ret = 0;
	for (int next = 0; next < N; next++)
	{
		if (visited[next])
			continue;
		if (next == here)
			continue;
		if (capacity[here][next] == 0 || capacity[here][next] < ret)
			continue;
		visited[next] = true;
		ret = max(ret, getMaxFlow_dfs(next, min(minFlow, capacity[here][next]), visited));
		visited[next] = false;
	}
	return ret;
}

int getTotalFlow_networkFlow_bfs()
{
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;

	while (true)
	{
		vector<int> parent(N, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty())
		{
			int here = q.front();
			q.pop();
			for (int next = 0; next < N; next++)
			{
				if (capacity[here][next] - flow[here][next] > 0 && parent[next] == -1)
				{
					q.push(next);
					parent[next] = here;
				}
			}
		}

		if (parent[sink] == -1)
			break;

		int amount = INT_MAX;
		for (int p = sink; p != source; p = parent[p])
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

		for (int p = sink; p != source; p = parent[p])
		{
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}

	return totalFlow;
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int E;
		cin >> N >> E >> source >> sink;

		memset(capacity, 0, sizeof(capacity));

		for (int i = 0; i < E; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			capacity[a][b] = c;
		}

		int totalFlow = getTotalFlow_networkFlow_bfs();

		vector<bool> visited(N, false);
		int maxFlow = getMaxFlow_dfs(source, INT_MAX, visited);
		cout << fixed << setprecision(3) << (double)totalFlow / (double)maxFlow << endl;
	}
	return 0;
}



