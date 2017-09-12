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

//https://algospot.com/judge/problem/read/CANADATRIP

class CanadaTrip_12_4
{
public:

private:
	int n, k;
	int l[5000], m[5000], g[5000];


	// ���� ����: dist �������� ���鼭 k �� �̻��� ǥ������ ���� �� �ִ°�?
	bool decision(int dist) {
		int ret = 0;
		for (int i = 0; i < n; i++)
			// i ��° ���� ǥ������ �ϳ� �̻� ���� �Ǵ°�?
			if (dist >= l[i] - m[i])
				ret += (min(dist, l[i]) - (l[i] - m[i])) / g[i] + 1;
		return ret >= k;
	}

	// k��° ǥ������ ������ ������ ��ġ�� ����Ѵ�
	int optimize() {
		// �ݺ��� �Һ� ����: !decision(lo) && decision(hi)
		int lo = -1, hi = 8030001;
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (decision(mid))
				hi = mid;
			else
				lo = mid;
		}
		return hi;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n >> k;
			for (int i = 0; i < n; i++)
				cin >> l[i] >> m[i] >> g[i];
			cout << optimize() << endl;
		}
	}

};