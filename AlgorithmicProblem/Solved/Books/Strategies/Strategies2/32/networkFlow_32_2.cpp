#include<cstdio>
#include<cassert>
#include<cstring>
#include<map>
#include<set>
#include<time.h>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int MAX_V = 100;

// �׷����� ���� ��� ǥ��
int V;
// capacity[u][v] = u���� v�� ���� �� �ִ� �뷮
// flow[u][v] = u���� v�� �귯���� ���� (�ݴ� ������ ��� ����)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

// flow[][]�� ����ϰ� �� ������ ��ȯ�Ѵ�
int networkFlow(int source, int sink) {
	// flow �� 0���� �ʱ�ȭ�Ѵ�
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;

	while (true) {
		// �ʺ� �켱 Ž������ ���� ��θ� ã�´�
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty()) {
			int here = q.front(); 
			q.pop();
			for (int there = 0; there < V; ++there)
				// �ܿ� �뷮�� ���� �ִ� ������ ���� Ž���Ѵ�
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
		}
		// ���� ��ΰ� ������ �����Ѵ�
		if (parent[sink] == -1) break;
		// ���� ��θ� ���� ������ �󸶳� ������ �����Ѵ�
		int amount = 987654321;
		for (int p = sink; p != source; p = parent[p])
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		// ���� ��θ� ���� ������ ������
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}

	return totalFlow;
}

int main() {
	int cases;
	cin >> cases;
	for (int cc = 0; cc < cases; ++cc) {
		int E;
		cin >> V >> E;
		memset(capacity, 0, sizeof(capacity));
		for (int i = 0; i < E; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			capacity[a][b] = c;
		}
		cout << networkFlow(0, V - 1) << endl;
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				if (flow[i][j] > 0)
					cout << i << " => " << j << ": " << flow[i][j] << endl;
	}
}

