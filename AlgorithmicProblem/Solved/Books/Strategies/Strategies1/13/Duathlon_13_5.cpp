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

//https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1326

class Duathlon_13_5
{
public:

private:
	double t;
	vector<double> runSpeed, cycleSpeed;

	// �޸��� ������ ���̰� run�� ��, i�� ������ �ɸ��� �ð�
	double time(int i, double run) {
		double cycle = t - run;
		return run / runSpeed[i] + cycle / cycleSpeed[i];
	}

	// �޸��� ���� ���̰� r�� ��, others(r) - cheater(r) �� ��ȯ�Ѵ�.
	double diff(double r) {
		int n = runSpeed.size();
		double cheater = time(n - 1, r);
		double others = time(0, r);
		for (int i = 1; i < n - 1; ++i)
			others = min(others, time(i, r));
		return others - cheater;
	}

	// diff() �Լ��� �ִ밪�� ��ġ�� ��� �˻����� ����Ѵ�.
	double maxDifference() {
		double lo = 0, hi = t;
		for (int it = 0; it < 100; ++it) {
			double aab = (2 * lo + hi) / 3;
			double abb = (lo + 2 * hi) / 3;
			if (diff(aab) > diff(abb))
				hi = abb;
			else
				lo = aab;
		}
		return (lo + hi) / 2;
	}

	int CInput() {
		while (cin >> t) {
			int n;
			cin >> n;
			runSpeed.resize(n);
			cycleSpeed.resize(n);
			for (int i = 0; i < n; ++i)
				cin >> runSpeed[i] >> cycleSpeed[i];
			double ret = maxDifference();
			double timeDiff = diff(ret);
			if (timeDiff < 0)
				printf("The cheater cannot win.\n");
			else
				printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n",
					timeDiff * 3600,
					ret,
					t - ret);
		}
	}
};