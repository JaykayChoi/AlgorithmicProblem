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


class PartialSum_17_1
{
public:

private:
	int n, a[1000], b[1000];

	// �־��� ���� a �� �κ����� ����Ѵ�.
	vector<int> partialSum(const vector<int>& a) {
		vector<int> ret(a.size());
		ret[0] = a[0];
		for (int i = 1; i < a.size(); i++)
			ret[i] = ret[i - 1] + a[i];
		return ret;
	}

	// � ������ �κ��� psum[] �� �־��� ��, ���� ������ a ���� b ������ ���� ���Ѵ�.
	int rangeSum(const vector<int>& psum, int a, int b) {
		return psum[b] - (a ? psum[a - 1] : 0);
	}

	// A[] �� ������ �κ� �� ���� sqpsum, A[] �� �κ� �� ���� psum �� �־��� ��
	// A[a..b] �� �л��� ��ȯ�Ѵ�
	double variance(const vector<int>& sqpsum, const vector<int>& psum, int a, int b) {
		// �켱 �ش� ������ ����� ����Ѵ�
		double mean = rangeSum(psum, a, b) / double(b - a + 1);

		double ret = rangeSum(sqpsum, a, b) - 2 * mean * rangeSum(psum, a, b) + (b - a + 1) * mean * mean;
		return ret / (b - a + 1);
	}

	// ���� �迭 A �� �־��� ��, ���� 0 �� ���� ����� ������ �������� ���밪�� ����Ѵ�.
	int smallestInterval(const vector<int>& A) {
		// A �� ���̰� 1 �϶��� ���� ó���Ѵ�.
		if (A.size() == 1) return abs(A[0]);

		// �κ����� ���ϰ� �����Ѵ�.
		vector<int> psum = partialSum(A);
		sort(psum.begin(), psum.end());

		// ������� ������ �κ��� �� �ּ� ���̰� �ȴ�.
		int ret = psum[1] - psum[0];
		for (int i = 2; i < psum.size(); ++i)
			ret = min(ret, psum[i] - psum[i - 1]);
		return ret;
	}

	double sqr(double x) { return x*x; }

	int grid[100][100], gridPartialSum[100][100];

	// � 2���� �迭 A[][] �� �κ��� psum[][] �� �־��� ��,
	// A[y1,x1] �� A[y2,x2] �� �� ������ ���� �κ� �迭�� ���� ��ȯ�Ѵ�.
	int gridSum(const vector<vector<int> >& psum, int y1, int x1, int y2, int x2) {
		int ret = psum[y2][x2];
		if (y1 > 0) ret -= psum[y1 - 1][x2];
		if (x1 > 0) ret -= psum[y2][x1 - 1];
		if (y1 > 0 && x1 > 0) ret += psum[y1 - 1][x1 - 1];
		return ret;
	}

	int CInput() {
		cin >> n;
		vector<int> A(n), A2(n);
		for (int i = 0; i < n; i++) {
			cin >> A[i];
			A2[i] = A[i] * A[i];
		}
		vector<int> psum(n), sqpsum(n);
		partial_sum(A.begin(), A.end(), psum.begin());
		partial_sum(A2.begin(), A2.end(), sqpsum.begin());

		for (int i = 0; i < n; i++)
			for (int j = i; j < n; j++) {
				double sum = 0;
				for (int k = i; k < j + 1; k++)
					sum += A[k];
				double mean = sum / (j - i + 1);
				double var = 0;
				for (int k = i; k < j + 1; k++)
					var += sqr(mean - A[k]);
				var /= (j - i + 1);
				printf("var %g\n", var);
				printf("variance %g\n", variance(sqpsum, psum, i, j));
				assert(fabs(var - variance(sqpsum, psum, i, j)) < 1e-8);
			}

	}
};
