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

//https://algospot.com/judge/problem/read/LUNCHBOX

class LunchBox_10_2
{
public:

private:
	int n;
	int m[10000], e[10000];

	int heat() {
		// 어느 순서로 데워야 할지를 정한다
		vector<pair<int, int> > order;
		for (int i = 0; i < n; i++)
			order.push_back(make_pair(-e[i], i));
		sort(order.begin(), order.end());
		// 해당 순서대로 데워먹는 과정을 시뮬레이션한다
		int ret = 0, beginEat = 0;
		for (int i = 0; i < n; i++) {
			int box = order[i].second;
			beginEat += m[box];
			ret = max(ret, beginEat + e[box]);
		}
		return ret;
	}
};