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

//https://algospot.com/judge/problem/read/STRJOIN

class StrJoin_10_4
{
public:

private:
	// lengths 에서 최소값을 지우고 그 값을 반환한다.
	int pop(vector<int>& lengths) {
		vector<int>::iterator min = min_element(lengths.begin(), lengths.end());
		int ret = *min;
		lengths.erase(min);
		return ret;
	}

	// 문자열들의 길이가 주어질 때 하나로 합치는 최소 비용을 반환한다.
	int concat2(vector<int> lengths) {
		int ret = 0;
		while (lengths.size() > 1) {
			int min1 = pop(lengths);
			int min2 = pop(lengths);
			ret += min1 + min2;
			lengths.push_back(min1 + min2);
		}
		return ret;
	}

	// 문자열들의 길이가 주어질 때 하나로 합치는 최소 비용을 반환한다.
	int concat(const vector<int>& lengths) {
		// 최소 큐를 선언한다
		priority_queue<int, vector<int>, greater<int> > pq;
		for (int i = 0; i < lengths.size(); ++i)
			pq.push(lengths[i]);

		int ret = 0;
		// 원소가 1개 이상 남은 동안 반복한다
		while (pq.size() > 1) {
			// 가장 짧은 문자열 두 개를 찾아서 합치고 큐에 넣는다
			int min1 = pq.top(); pq.pop();
			int min2 = pq.top(); pq.pop();
			pq.push(min1 + min2);
			ret += min1 + min2;
		}
		return ret;
	}


	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int n;
			cin >> n;
			vector<int> lengths(n);
			for (int i = 0; i < n; i++) cin >> lengths[i];
			cout << concat(lengths) << endl;
		}
	}
};