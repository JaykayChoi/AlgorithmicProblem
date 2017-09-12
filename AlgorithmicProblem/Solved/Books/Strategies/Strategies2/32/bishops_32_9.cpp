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

vector<string> board;
int id[2][8][8];

const int dx[2] = { -1, 1 };
const int dy[2] = { 1, 1 };

int n, m;
int adj[64][64];

// �� ������ ��Ī�� ��� ������ ��ȣ�� �����Ѵ�.
vector<int> aMatch, bMatch;

// dfs() �� �湮 ����
vector<bool> visited;

// A�� ������ a���� B�� ��Ī���� ���� �������� ���� ��θ� ã�´�.
bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; ++b)
		if (adj[a][b])
			if (bMatch[b] == -1 || dfs(bMatch[b])) {
				// ���� ��� �߰�!! a �� b �� ��ġ��Ų��.
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
	return false;
}

// aMatch, bMatch �迭�� ����ϰ� �ִ� ��Ī�� ũ�⸦ ��ȯ�Ѵ�.
int bipartiteMatch() {
	// ó������ � ������ ����Ǿ� ���� �ʴ�
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);

	int size = 0;
	for (int start = 0; start < n; ++start) {
		visited = vector<bool>(n, false);
		// ���� �켱 Ž���� �̿��� start���� �����ϴ� ���� ��θ� ã�´�
		if (dfs(start))
			++size;
	}
	return size;
}

int placeBishops() {
	// �� �밢���� ��ȣ�� ���δ�
	memset(id, -1, sizeof(id));
	int count[2] = { 0, 0 };
	for (int dir = 0; dir < 2; ++dir)
	{
		for (int y = 0; y < board.size(); ++y)
		{
			for (int x = 0; x < board.size(); ++x)
			{
				if (board[y][x] == '.' && id[dir][y][x] == -1) 
				{
					int cy = y, cx = x;
					while (0 <= cy && cy < board.size() && 0 <= cx && cx < board.size() &&
						board[cy][cx] == '.') 
					{
						id[dir][cy][cx] = count[dir];
						cy += dy[dir];
						cx += dx[dir];
					}
					count[dir]++;
				}
			}
		}
	}
	// �̺� �׷����� �����
	n = count[0];
	m = count[1];
	memset(adj, 0, sizeof(adj));
	for (int y = 0; y < board.size(); ++y)
		for (int x = 0; x < board.size(); ++x)
			if (board[y][x] == '.')
				adj[id[0][y][x]][id[1][y][x]] = 1;
	return bipartiteMatch();
}

int main()
{
	int cases;
	cin >> cases;
	for (int cc = 0; cc < cases; ++cc) {
		int n;
		cin >> n;
		board.resize(n);
		for (int i = 0; i < n; ++i) cin >> board[i];
		cout << placeBishops() << endl;
	}
}

//3
//
//5
//
//* .*..
//
//.*..*
//
//*.***
//
//*.*.*
//
//.*.*.
//
//8
//
//..**.*.*
//
//**.***.*
//
//*.**...*
//
//.*.**.**
//
//*.**.*.*
//
//..**.*.*
//
//...*.*.*
//
//**.*.*.*
//
//8
//
//* .*.*.*.
//
//.*.*.*.*
//
//*.*.*.*.
//
//.*.*.*.*
//
//*.*.*.*.
//
//.*.*.*.*
//
//*.*.*.*.
//
//.*.*.*.*