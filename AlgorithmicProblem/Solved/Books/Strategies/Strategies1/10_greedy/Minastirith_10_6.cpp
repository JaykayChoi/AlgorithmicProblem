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

//https://algospot.com/judge/problem/read/MINASTIRITH


class Minastirith_10_6
{
public:

private:
	const double pi = 2.0 * acos(0);

	int n;
	double y[100], x[100], r[100];
	pair<double, double> ranges[100];

	void convertToRange() {
		for (int i = 0; i < n; i++) {
			double loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
			double range = 2.0 * asin(r[i] / 2.0 / 8.0);
			ranges[i] = make_pair(loc - range, loc + range);
		}
	}

	void sortRanges() {
	}

	// [begin,end] ������ ���� ���� ������ �ּ����� ���� ���� ��ȯ�Ѵ�
	// ranges �� ���� ��ġ�� ������������ ���ĵǾ� �ִٰ� ��������.
	int solveLinear(double begin, double end) {

		int used = 0, idx = 0;
		// ���� ���� ������ ���� �ִ� ���� ����Ѵ�
		while (begin < end) {
			// begin ���� ������ �����ϴ� ���� �� ���� �ʰ� ������ ������ ã�´�
			double maxCover = -1;
			while (idx < n && ranges[idx].first <= begin) {
				maxCover = max(maxCover, ranges[idx].second);
				++idx;
			}
			// ���� ������ ã�� �������� ū ���� ��ȯ�Ѵ�
			if (maxCover <= begin)
				return 987654321;
			// ������ ���� �κ��� �߶󳽴�
			begin = maxCover;
			++used;
		}
		return used;
	}


	// 0 �� ���� ������ �����ϰ� �������� �������� Ǭ��.
	int solveCircular() {
		int ret = 987654321;

		// �� ������ ���� ��ġ�� ������������ �����Ѵ�
		sort(ranges, ranges + n);

		// 0 �� ���� ������ ��������.
		for (int i = 0; i < n; ++i)
			if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
				// �� ������ ���� �κ��� ���� ���� �߽ɰ��� ������ ������ ����
				double begin = fmod(ranges[i].second, 2 * pi);
				double end = fmod(ranges[i].first + 2 * pi, 2 * pi);

				// [begin, end] ������ �־��� ������ ����ؼ� ���´�.
				ret = min(ret, 1 + solveLinear(begin, end));
			}
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n;
			assert(1 <= n && n <= 100);
			for (int i = 0; i < n; i++) {
				cin >> y[i] >> x[i] >> r[i];
				assert(fabs(8.0 - hypot(y[i], x[i])) < 1e-8);
				assert(0 <= r[i] && r[i] <= 16.0);
			}
			convertToRange();
			int ret = solveCircular();
			if (ret == 987654321)
				cout << "IMPOSSIBLE" << endl;
			else
				cout << ret << endl;
		}
	}
};