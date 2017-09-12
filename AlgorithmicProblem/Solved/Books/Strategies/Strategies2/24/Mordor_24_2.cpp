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

//https://algospot.com/judge/problem/read/MORDOR

class Mordor_24_2
{
public:

private:
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

	// �� ǥ������ ����
	vector<int> h;

	int sub_main() {
		int cases;
		scanf_s("%d", &cases);
		while (cases--) {
			int n, q;
			scanf_s("%d %d", &n, &q);
			h.resize(n);
			for (int i = 0; i < n; i++)
				scanf_s("%d", &h[i]);

			RMQ minimum(h);
			for (int i = 0; i < n; i++) h[i] = -h[i];
			RMQ maximum(h);

			for (int i = 0; i < q; i++) {
				int a, b;
				scanf_s("%d %d", &a, &b);
				printf("%d\n", -maximum.query(a, b) - minimum.query(a, b));
			}

		}
		return 0;
	}
};