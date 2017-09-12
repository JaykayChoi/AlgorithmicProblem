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

const double INF = 1e200;
const int MAX = 30;
const int CACHED_DEPTH = 5;

class TSP_11_2
{
public:

private:
	int n; // ������ ��
	double dist[MAX][MAX]; // �� ���ð��� �Ÿ��� �����ϴ� �迭


	// ���� Ž�� (11��)

	// �� ������ ������ ���� �� ���� ª�� ���� �̸� ã�� �д�
	double minEdge[MAX];

	// �����̵��� �� �ִٴ� ������ �̿��� �޸���ƽ
	double simpleHeuristic(vector<bool>& visited) {
		double ret = minEdge[0];
		for (int i = 0; i < n; i++)
			if (!visited[i])
				ret += minEdge[i];
		return ret;
	}

	// �� �������� �ٸ� �������� ����� ������� ������ �д�
	vector<int> nearest[MAX];

	// path �� ������ 4���� ���� �� ��� 2���� ������ �ٲ��� �� ��ΰ� �� ª�������� ���θ� ��ȯ�Ѵ�
	bool pathSwapPruning(const vector<int>& path) {
		if (path.size() < 4) return false;
		int p = path[path.size() - 4];
		int a = path[path.size() - 3];
		int b = path[path.size() - 2];
		int q = path[path.size() - 1];

		return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
	}

	// ���� ���ÿ� ���� ���ø� ������ path �� �κ� ��θ�
	// ������ ���� �� ª�������� Ȯ���Ѵ�
	bool pathReversePruning(const vector<int>& path) {
		if (path.size() < 3) return false;
		int b = path[path.size() - 2];
		int q = path[path.size() - 1];
		for (int i = 0; i + 2 < path.size(); ++i) {
			int p = path[i];
			int a = path[i + 1];
			// [.., p, a, ..., b, q] �� [.., p, b, ..., a, q] �� �ٲ㺻��
			if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
				return true;
		}
		return false;
	}

	// Union-Find ��ȣ ������ ���� �ڷ� ������ �����Ѵ�
	struct UnionFind
	{
		int n, components;
		vector<int> parent, rank;
		UnionFind(int n) : n(n), components(n), parent(n), rank(n)
		{
			for (int i = 0; i < n; ++i) { parent[i] = i; rank[i] = 0; }
		}
		int find(int here) { return parent[here] == here ? here : (parent[here] = find(parent[here])); }
		bool merge(int a, int b)
		{
			a = find(a); b = find(b);
			if (a == b) return false;
			if (rank[a] > rank[b])
				parent[b] = a;
			else
			{
				parent[a] = b;
				if (rank[a] == rank[b]) rank[b]++;
			}
			--components;
			return true;
		}
	};

	// ��� ���� ���� ���θ� ���� ������ ������ ������ �д�
	vector<pair<double, pair<int, int> > > edges;

	// here �� ������, ���� �湮���� ���� ���õ��� ��� �����ϴ� MST �� ã�´�.
	double mstHeuristic(int here, const vector<bool>& visited) {
		// Kruskal's MST
		UnionFind sets(n);
		double taken = 0;
		for (int i = 0; i < edges.size(); i++) {
			int a = edges[i].second.first, b = edges[i].second.second;
			if (a != 0 && a != here && visited[a]) continue;
			if (b != 0 && b != here && visited[b]) continue;
			if (sets.merge(a, b))
				taken += edges[i].first;
		}
		return taken;
	}

	// ���ݱ��� ã�� ������
	double best;

	double optimize(vector<int> path) {
		while (true) {
			bool improved = false;
			for (int i = 1; i < n; i++)
				for (int j = i + 1; j < n; j++) {
					int a = path[i], b = path[j];
					double delta = 0;
					delta += dist[a][path[(j + 1) % n]] - dist[b][path[(j + 1) % n]];
					delta += dist[b][path[(i + n - 1) % n]] - dist[a][path[(i + n - 1) % n]];
					if (i + 1 < j) delta += dist[b][path[i + 1]] - dist[a][path[i + 1]]
						+ dist[a][path[j - 1]] - dist[b][path[j - 1]];
					if (delta < 0) {
						improved = true;
						swap(path[i], path[j]);
					}
					if (improved) break;
				}
			if (!improved) break;
		}
		double length = 0;
		for (int i = 0; i < n; i++)
			length += dist[path[i]][path[(i + 1) % n]];
		return length;
	}

	// ���� ������ ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�
	//const int CACHED_DEPTH = 5;

	// dp(here, visited) = cache[here][���� ������ ��][visited]
	map<int, double> cache[MAX][CACHED_DEPTH + 1];

	// here: ���� ��ġ
	// visited: �� ������ �湮 ����
	// �� ��, ������ ���õ��� ��� �湮�ϰ� ���������� ���ư��� �ִܰ���� ���̸� ��ȯ�Ѵ�
	double dp(int here, int visited) {
		// ���� ���: �� �湮�� ���ð� ������ ���������� ���ư���
		if (visited == (1 << n) - 1) return dist[here][0];

		// �޸������̼�
		int remaining = n - __builtin_popcount(visited);
		double& ret = cache[here][remaining][visited];
		if (ret > 0) return ret;

		ret = INF;
		// ���� ���ø� �ϳ��ϳ� �õ��Ѵ�
		for (int next = 0; next < n; ++next) {
			if (visited & (1 << next)) continue;
			ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
		}
		return ret;
	}

	

	double blowUp;
	clock_t begin;

	// path: ���ݱ��� ���� ���
	// visited: �� ������ �湮 ����
	// currentLength: ���ݱ��� ���� ����� ����
	// ������ ���õ��� ��� �湮�ϴ� ��ε��� ����� ���� �����ϸ� �����ظ� �����Ѵ�
	void search(vector<int>& path, vector<bool>& visited, double currentLength) {
		int here = path.back();

		// ������ ��θ� �̿��� ����ġ��
		if (pathReversePruning(path)) return;

		// MST �޸���ƽ�� �̿��� ����ġ��
		double estimation = blowUp * mstHeuristic(here, visited);
		if (best <= currentLength + estimation) return;

		// ���� ���: ���� ���� ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�
		if (path.size() + CACHED_DEPTH >= n) {
			int mask = 0;
			for (int i = 0; i < n; i++) if (visited[i]) mask += (1 << i);
			double cand = currentLength + dp(here, mask);
			if (cand < best) {
				best = cand;
				//fprintf(stderr, "%g %g\n", (clock() - begin) / (double)CLOCKS_PER_SEC, best);
			}
			return;
		}

		double ret = INF; // �ſ� ū ������ �ʱ�ȭ

						  // ���� �湮�� ���ø� ���� �õ��� ����
		for (int i = 0; i < nearest[here].size(); ++i) {
			int next = nearest[here][i];
			if (visited[next]) continue;

			path.push_back(next);
			visited[next] = true;

			// ������ ��θ� ���ȣ���� ���� �ϼ��Ѵ�
			search(path, visited, currentLength + dist[here][next]);

			visited[next] = false;
			path.pop_back();
		}
	}

	vector<string> args;

	double solve() {
		// simpleHeuristic() �� ���� �ʱ�ȭ
		for (int i = 0; i < n; ++i) {
			minEdge[i] = INF;
			for (int j = 0; j < n; ++j)
				if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
		}

		// nearest �ʱ�ȭ
		for (int i = 0; i < n; ++i) {
			vector<pair<double, int> > order;
			for (int j = 0; j < n; j++)
				if (i != j)
					order.push_back(make_pair(dist[i][j], j));
			sort(order.begin(), order.end());
			nearest[i].clear();
			for (int j = 0; j < n - 1; j++)
				nearest[i].push_back(order[j].second);
		}

		// edges �ʱ�ȭ
		edges.clear();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < i; j++)
				edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
		sort(edges.begin(), edges.end());

		for (int i = 0; i < MAX; i++)
			for (int j = 0; j <= CACHED_DEPTH; j++)
				cache[i][j].clear();

		// best �� �ſ� ū ������ �ʱ�ȭ
		best = INF;

		vector<bool> visited(n, false);
		vector<int> path(1, 0);
		visited[0] = true;

		/*
		if(args.size() <= 3)
		args.push_back("1.0");

		begin = clock();
		for(int i = 3; i < args.size(); ++i) {
		fprintf(stderr, "-1.0\n");
		blowUp = atof(args[i].c_str());
		search(path, visited, 0);

		}   */
		//blowUp = 2.0;
		//search(path, visited, 0);
		//blowUp = 2; search(path, visited, 0);
		//blowUp = 1.5; search(path, visited, 0);
		//blowUpRate = 1.0; search(path, visited, 0);
		//blowUpRate = 1.1; search(path, visited, 0);
		//blowUpRate = 1.1; search(path, visited, 0);
		//blowUpRate = 1.1; search(path, visited, 0);
		blowUp = 1.0; search(path, visited, 0);

		return best;
	}

	int CInput(int argc, char* argv[])
	{
		//int pid = fork();
		//if (pid != 0) {
		//	int status;
		//	waitpid(pid, &status, 0);
		//	return 0;
		//}
		//if (argc > 1) freopen(argv[1], "r", stdin);
		//if (argc > 2) freopen(argv[2], "w", stdout);
		//for (int i = 0; i < argc; i++) args.push_back(argv[i]);

		//int cases;
		//cin >> cases;
		//REP(cc, cases)
		//{
		//	cin >> n;
		//	vector<double> y(n), x(n);
		//	for (int i = 0; i < n; i++)
		//		cin >> y[i] >> x[i];
		//	REP(i, n) REP(j, n) dist[i][j] = hypot(y[i] - y[j], x[i] - x[j]);
		//	/*
		//	CLEAR(cache,0);
		//	int ret = 1e10;
		//	REP(st,n) ret = min(ret, shortestPath2(st, 1<<st));
		//	printf("%.15lf\n", ret);
		//	*/
		//	vector<bool> visited(n, false);
		//	visited[0] = true;
		//	vector<int> path(1, 0);
		//	//printf("%.15lf\n", shortestPath(path, visited, 0));
		//	/*
		//	for(int i = 0; i < n; i++) {
		//	for(int j = 0; j < (1<<n); j++)
		//	cache[i][j] = -1;
		//	}
		//	printf("%.15lf\n", shortestPath2(0, 1));
		//	*/
		//	printf("%.15lf\n", solve());
		//}
	}
};
