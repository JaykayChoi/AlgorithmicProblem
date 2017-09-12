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

//https://algospot.com/judge/problem/read/FAMILYTREE

class FamilyTree_24_4
{
public:
	//const int INT_MAX = numeric_limits<int>::max();

	// �迭�� ���� �ּ� ������ �ذ��ϱ� ���� ���� Ʈ���� ����
	struct RMQ {
		// �迭�� ����
		int n;
		// �� ������ �ּҰ�
		vector<int> rangeMin;
		RMQ(const vector<int>& array) {
			n = array.size();
			rangeMin.resize(n * 4);
			init(array, 1, 0, n - 1);

		}
		// node ��尡 array[left..right] �迭�� ǥ���� ��
		// node �� ��Ʈ�� �ϴ� ����Ʈ���� �ʱ�ȭ�ϰ�, �� ������ �ּҰ��� ��ȯ�Ѵ�
		int init(const vector<int>& array, int node, int left, int right) {
			if (left == right)
				return rangeMin[node] = array[left];
			int mid = (left + right) / 2;
			return rangeMin[node] = min(init(array, node * 2, left, mid),
				init(array, node * 2 + 1, mid + 1, right));
		}

		// array[index] = newValue �� �ٲ���� �� node �� ��Ʈ�� �ϴ� ���� Ʈ����
		// ������Ʈ�ϰ� ��尡 ǥ���ϴ� ������ �ּҰ��� ��ȯ�Ѵ�
		int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
			// index �� ��尡 ǥ���ϴ� ������ ������� ��쿣 �����Ѵ�
			if (index < nodeLeft || nodeRight < index) return rangeMin[node];
			// Ʈ���� �������� ������ ���
			if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
			int mid = (nodeLeft + nodeRight) / 2;
			return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid),
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
		}

		// update() �� �ܺο��� ȣ���ϱ� ���� �������̽�
		int update(int index, int newValue) { return update(index, newValue, 1, 0, n - 1); }

		// node �� ǥ���ϴ� ���� array[nodeLeft..nodeRight] �� �־��� ��
		// �� ������ array[left..right] �� �������� �ּҰ��� ���Ѵ�
		int query(int left, int right, int node, int nodeLeft, int nodeRight) {
			// �� ������ ��ġ�� ������ ���� ū ���� ��ȯ�Ѵ�: ���õ�
			if (right < nodeLeft || nodeRight < left) return INT_MAX;
			// node �� ǥ���ϴ� ������ array[left..right] �� ������ ���ԵǴ� ���
			if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
			// ���� ������ ������ Ǭ �� ����� ��ģ��
			int mid = (nodeLeft + nodeRight) / 2;
			return min(query(left, right, node * 2, nodeLeft, mid),
				query(left, right, node * 2 + 1, mid + 1, nodeRight));
		}

		// query() �� �ܺο��� ȣ���ϱ� ���� �������̽�
		int query(int left, int right) { return query(left, right, 1, 0, n - 1); }
	};

	// Ʈ���� ����
	int n;
	vector<int> child[100000];
	// Ʈ���� ��ȣ�� �Ϸ� ��ȣ ������ ���� ����
	int no2serial[100000], serial2no[100000];
	// �� ��尡 trip �� ó�� �����ϴ� ��ġ, �׸��� �� ����� ����
	int locInTrip[100000], depth[100000];
	// ���� �Ϸ� ��ȣ
	int nextSerial;

	void traverse(int here, int d, vector<int>& trip) {
		// traverse() �� ó�� �湮���ڸ��� �Ϸ� ��ȣ�� �ο��Ѵ�.
		// �̷��� �ϸ� �׻� �θ�� �ڼպ��� ���� �Ϸ� ��ȣ�� ���� �ȴ�.
		no2serial[here] = nextSerial;
		serial2no[nextSerial] = here;
		++nextSerial;

		// ���� ���
		depth[here] = d;

		// trip �� ���� ����� �Ϸ� ��ȣ�� �߰��Ѵ�
		locInTrip[here] = trip.size();
		trip.push_back(no2serial[here]);

		// ��� �ڽ� ��带 �湮
		for (int i = 0; i < child[here].size(); i++) {
			traverse(child[here][i], d + 1, trip);

			// �ڽĳ�带 �湮�ϰ� ���� ���� ���ƿ� ������ �ٽ� �߰��ϱ�
			trip.push_back(no2serial[here]);
		}
	}

	// Ʈ���� ��ȸ�ϸ� ���� �ʿ��� ������ ����ϰ�, RMQ ���� Ʈ����
	// ����� ��ȯ�Ѵ�.
	RMQ* prepareRMQ() {
		nextSerial = 0;
		// ��ȸ �������� ������ ������ �Ϸ� ��ȣ�� ��´�
		vector<int> trip;
		traverse(0, 0, trip);
		return new RMQ(trip);
	}

	// u �� v ������ �Ÿ��� ����Ѵ�
	int distance(RMQ* rmq, int u, int v) {
		// trip[] �迭���� u �� v �� ù ���� ��ġ�� ã�´�
		int lu = locInTrip[u], lv = locInTrip[v];
		if (lu > lv) swap(lu, lv);
		// rmq �� u �� v �� �ּ� ���� ������ �Ϸù�ȣ�� ��ȯ�Ѵ�
		int lca = serial2no[rmq->query(lu, lv)];
		return depth[u] + depth[v] - 2 * depth[lca];
	}

	int sub_main() {
		int cases;
		scanf_s("%d", &cases);
		while (cases--) {
			int queries;
			scanf_s("%d %d", &n, &queries);
			for (int i = 0; i < n; i++) child[i].clear();
			for (int i = 1; i < n; i++) {
				int parent;
				scanf_s("%d", &parent);
				child[parent].push_back(i);
			}

			RMQ* rmq = prepareRMQ();
			for (int i = 0; i < queries; i++) {
				int a, b;
				scanf_s("%d %d", &a, &b);
				printf("%d\n", distance(rmq, a, b));
			}
			delete rmq;
		}
		return 0;
	}

};
