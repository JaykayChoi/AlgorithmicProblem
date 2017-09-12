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

//https://algospot.com/judge/problem/read/WITHDRAWAL

class Withdrawal_12_6
{
public:

private:
	int n, k;
	int c[1000], r[1000];

	// ���� ����: ���� ��� average �� �ǵ��� �� �� �ֳ�?
	bool decision(double average) {
		// sum(c[i]/r[i]) <= x
		// sum(c[i])/sum(r[i]) <= x
		// sum(c[i]) <= x*sum(r[i])
		// 0 <= x*sum(r[i]) - sum(c[i])
		// 0 <= sum(x*r[i] - c[i])

		// v[i] = x*r[i] - c[i] �� ����Ѵ�
		vector<double> v;
		for (int i = 0; i < n; i++)
			v.push_back(average * c[i] - r[i]);
		sort(v.begin(), v.end());

		// �� ������ v �� k���� ���� 0 �̻��� �� �� �ִ����� �ٲ��: Ž������� �ذ�
		double sum = 0;
		for (int i = n - k; i < n; i++)
			sum += v[i];
		return sum >= 0;
	}

	// ����ȭ ����: ���� �� �ִ� �ּ��� ���� ����� ����Ѵ�
	double optimize() {
		// ���� ����� [0,1] ������ �Ǽ��̴�.
		// �ݺ��� �Һ� ����: !decision(lo) && decision(hi)
		double lo = -1e-9, hi = 1;
		for (int iter = 0; iter < 100; iter++) {
			double mid = (lo + hi) / 2;
			// ���� ��� mid �� �޼��� �� �ֳ�?
			if (decision(mid))
				hi = mid;
			else
				lo = mid;
		}
		return hi;
	}

	double brute() {
		double ret = 1;
		for (int i = 0; i < (1 << n); i++)
			if (__builtin_popcount(i) == k) {
				int ranks = 0, counts = 0;
				for (int j = 0; j < n; j++)
					if (i & (1 << j)) {
						ranks += r[j];
						counts += c[j];
					}
				ret = min(ret, ranks * 1.0 / counts);
			}
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n >> k;
			for (int i = 0; i < n; i++) cin >> r[i] >> c[i];
			printf("%.10lf\n", optimize());
			//printf("%.10lf\n", brute());
		}
	}
};