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


//range minumum query
class RMQ_24_1
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

	template<typename TRAITS>
	struct SegmentTree {
		TRAITS processor;

		typedef typename TRAITS::ELEM ELEM;
		typedef typename TRAITS::RESULT RESULT;

		int n;
		const vector<ELEM>& A;
		vector<RESULT> result;

		SegmentTree(const vector<ELEM>& _A) : n(_A.size()), A(_A), result(_A.size() * 4 + 10) {
			init(0, n - 1, 1);
		}

		void init(int left, int right, int node) {
			if (left == right) {
				result[node] = processor.single(A[left]);
				return;
			}
			int mid = (left + right) / 2;
			init(left, mid, node * 2);
			init(mid + 1, right, node * 2 + 1);
			result[node] = processor.combine(result[node * 2], result[node * 2 + 1]);
		}

		void update(int index, const ELEM& newValue, int node, int nodeLeft, int nodeRight) {
			if (index < nodeLeft || nodeRight < index) return;
			if (nodeLeft == nodeRight) {
				result[node] = processor.single(newValue);
				return;
			}
			int mid = (nodeLeft + nodeRight) / 2;
			update(index, newValue, node * 2, nodeLeft, mid);
			update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
			result[node] = processor.combine(result[node * 2], result[node * 2 + 1]);
		}

		void update(int index, const ELEM& newValue) {
			update(index, newValue, 1, 0, n - 1);
		}

		RESULT query(int left, int right, int node, int nodeLeft, int nodeRight) {
			left = max(left, nodeLeft); right = min(right, nodeRight);
			if (left > right) return processor.null();
			if (left == nodeLeft && right == nodeRight) return result[node];
			int mid = (nodeLeft + nodeRight) / 2;
			return processor.combine(query(left, right, node * 2, nodeLeft, mid),
				query(left, right, node * 2 + 1, mid + 1, nodeRight));
		}

		RESULT query(int left, int right) {
			return query(left, right, 1, 0, n - 1);
		}
	};

	struct MaxPairTraits {
		typedef int ELEM;
		typedef pair<int, int> RESULT;
		int null() { return numeric_limits<int>::min(); }
		RESULT combine(const RESULT& a, const RESULT& b) {
			int x = max(a.first, b.first);
			int y = min(a.first, b.first), z = max(a.second, b.second);
			return RESULT(x, max(y, z));
		}
		RESULT single(int elem) { return RESULT(elem, null()); }
	};

	// ranged sum �� ����
	struct SumTraits {
		typedef int ELEM;
		typedef int RESULT;
		int null() { return 0; }
		int combine(int a, int b) { return a + b; }
		int single(int elem) { return elem; }
	};

	// ranged minimum query �� ����
	struct MinTraits {
		typedef int ELEM;
		typedef int RESULT;
		int null() { return INT_MAX; }
		int combine(int a, int b) { return min(a, b); }
		int single(int elem) { return elem; }
	};

	int sub_main() {

		const int MAXN = 100000;
		for (int N = 10; N <= MAXN; N *= 10) {
			vector<int> test(N);
			for (int i = 0; i < N; i++) test[i] = rand() % 1000;
			RMQ rmq(test);
			SegmentTree<MinTraits> rmq2(test);
			const int TESTS = 100000;
			for (int i = 0; i < TESTS; i++) {
				int a = rand() % N;
				int b = rand() % N;
				if (a > b) swap(a, b);
				int A = rmq.query(a, b);
				int B = *min_element(test.begin() + a, test.begin() + b + 1);
				int C = rmq2.query(a, b);
				if (A != B || A != C) {
					printf("fuck\n");
					for (int i = 0; i < N; i++) {
						printf("%d ", test[i]);
					}
					printf("\n");
					printf("a=%d, b=%d, rmq=%d, brute=%d, rmq2=%d\n",
						a, b, A, B, C);
					return 0;
				}
			}
			printf("passed %d tests on N=%d\n", TESTS, N);
		}
		printf("all good.\n");
		return 0;
	}
};
