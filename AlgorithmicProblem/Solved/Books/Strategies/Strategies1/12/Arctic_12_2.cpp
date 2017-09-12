#include "Utils.h"
using namespace std;
using namespace Utils;
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

//https://algospot.com/judge/problem/read/ARCTIC

class Arctic_12_2
{
public:

private:
	int n;
	// �� ���� ������ �Ÿ�
	double dist[101][101];
	double y[101], x[101];

	// �Ÿ� d ������ �����鸸�� �������� �� ��� ������ ����Ǵ��� ���θ� ��ȯ�Ѵ�.
	bool decision(double d) {
		vector<bool> visited(n, false);
		visited[0] = true;
		queue<int> q;
		q.push(0);
		int seen = 0;
		while (!q.empty()) {
			int here = q.front();
			q.pop();
			++seen;
			for (int there = 0; there < n; ++there)
				if (!visited[there] && dist[here][there] <= d) {
					visited[there] = true;
					q.push(there);
				}
		}
		return seen == n;
	}

	// ��� ������ ������ �� �ִ� �ּ��� d �� ��ȯ�Ѵ�.
	double optimize() {
		double lo = 0, hi = 1416.00;
		for (int it = 0; it < 100; ++it) {
			double mid = (lo + hi) / 2;
			// mid �� �����ϴٸ�, �� ���� (����) ���� ã�´�.
			if (decision(mid))
				hi = mid;
			// mid �� �Ұ����ϴٸ�, �� ���� (ū) ���� ã�´�.
			else
				lo = mid;
		}
		return hi;
	}

	int CInput()
	{
		int cases;
		cin >> cases;
		REP(cc, cases)
		{
			cin >> n;
			REP(i, n) cin >> y[i] >> x[i];
			REP(i, n) REP(j, i) dist[i][j] = dist[j][i] = hypot(x[i] - x[j], y[i] - y[j]);
			printf("%.2lf\n", optimize());
		}
	}
};