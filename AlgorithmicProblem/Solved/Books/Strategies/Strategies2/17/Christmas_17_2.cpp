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

//https://algospot.com/judge/problem/read/CHRISTMAS

class Christmas_17_2
{
public:

private:

	//부분 합을 이용

	//D[]의 부분 합 배열 psum과 k가 주어질 때, 몇 가지 방법으로 살 수 있는지 반환
	//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다
	int waysToBuy(const vector<int>& psum, int k)
	{
		const int MOD = 20091101;
		int ret = 0;
		//psum[]의 각 값을 몇 번이나 본 적 있는지 기록
		vector<ll> count(k, 0);
		REP(i, psum.sz)
		{
			count[psum[i]]++;
		}
		//두 번 이상 본 적 있다면 이 값 중 두 개를 선택하는 방법의 수를 더한다
		REP(i, k)
		{
			if (count[i] >= 2)
				ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
		}
		return ret;
	}

	//D[]의 부분 합 배열 psum[]과 k가 주어질 때, 겹치지 않게 몇 번이나 살 수 있는지 반환
	//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다
	int maxBuys(const vector<int>& psum, int k)
	{
		//ret[i]= 첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
		vector<int> ret(psum.sz, 0);
		//prev[s]=psum[]이 s 였던 마지막 위치
		vector<int> prev(k, -1);
		REP(i, psum.sz)
		{
			//i번째 상자를 아예 고려하지 않는 경우
			if (i > 0)
				ret[i] = ret[i - 1];
			else
				ret[i] = 0;
			
			//psum[i]를 전에도 본 적이 있으면, prev[psum[i]] + 1 부터 여기까지 쭉 사 본다
			int loc = prev[psum[i]];
			if (loc != -1)
				ret[i] = max(ret[i], ret[loc] + 1);
			//prev[]에 현재 위치를 기록한다
			prev[psum[i]] = i;
		}
		return ret.back();
	}
};