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
	// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
	struct RMQ {
		// 배열의 길이
		int n;
		// 각 구간의 최소값
		vector<int> rangeMin;
		RMQ(const vector<int>& array) {
			n = array.size();
			rangeMin.resize(n * 4);
			init(array, 1, 0, n - 1);

		}
		// node 노드가 array[left..right] 배열을 표현할 때
		// node 를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소값을 반환한다
		int init(const vector<int>& array, int node, int left, int right) {
			if (left == right)
				return rangeMin[node] = array[left];
			int mid = (left + right) / 2;
			return rangeMin[node] = min(init(array, node * 2, left, mid),
				init(array, node * 2 + 1, mid + 1, right));
		}

		// array[index] = newValue 로 바뀌었을 때 node 를 루트로 하는 구간 트리를
		// 업데이트하고 노드가 표현하는 구간의 최소값을 반환한다
		int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
			// index 가 노드가 표현하는 구간과 상관없는 경우엔 무시한다
			if (index < nodeLeft || nodeRight < index) return rangeMin[node];
			// 트리의 리프까지 내려온 경우
			if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
			int mid = (nodeLeft + nodeRight) / 2;
			return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid),
				update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
		}

		// update() 를 외부에서 호출하기 위한 인터페이스
		int update(int index, int newValue) { return update(index, newValue, 1, 0, n - 1); }

		// node 가 표현하는 범위 array[nodeLeft..nodeRight] 가 주어질 때
		// 이 범위와 array[left..right] 의 교집합의 최소값을 구한다
		int query(int left, int right, int node, int nodeLeft, int nodeRight) {
			// 두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨
			if (right < nodeLeft || nodeRight < left) return INT_MAX;
			// node 가 표현하는 범위가 array[left..right] 에 완전히 포함되는 경우
			if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
			// 양쪽 구간을 나눠서 푼 뒤 결과를 합친다
			int mid = (nodeLeft + nodeRight) / 2;
			return min(query(left, right, node * 2, nodeLeft, mid),
				query(left, right, node * 2 + 1, mid + 1, nodeRight));
		}

		// query() 를 외부에서 호출하기 위한 인터페이스
		int query(int left, int right) { return query(left, right, 1, 0, n - 1); }
	};

	// 각 표지판의 높이
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