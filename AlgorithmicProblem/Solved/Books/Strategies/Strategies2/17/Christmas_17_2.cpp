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

	//�κ� ���� �̿�

	//D[]�� �κ� �� �迭 psum�� k�� �־��� ��, �� ���� ������� �� �� �ִ��� ��ȯ
	//psum[]�� ù ��° ���� ���� 0�� �����ߴٰ� �����Ѵ�
	int waysToBuy(const vector<int>& psum, int k)
	{
		const int MOD = 20091101;
		int ret = 0;
		//psum[]�� �� ���� �� ���̳� �� �� �ִ��� ���
		vector<ll> count(k, 0);
		REP(i, psum.sz)
		{
			count[psum[i]]++;
		}
		//�� �� �̻� �� �� �ִٸ� �� �� �� �� ���� �����ϴ� ����� ���� ���Ѵ�
		REP(i, k)
		{
			if (count[i] >= 2)
				ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
		}
		return ret;
	}

	//D[]�� �κ� �� �迭 psum[]�� k�� �־��� ��, ��ġ�� �ʰ� �� ���̳� �� �� �ִ��� ��ȯ
	//psum[]�� ù ��° ���� ���� 0�� �����ߴٰ� �����Ѵ�
	int maxBuys(const vector<int>& psum, int k)
	{
		//ret[i]= ù ��° ���ں��� i��° ���ڱ��� ������� �� �� �� �ִ� �ִ� Ƚ��
		vector<int> ret(psum.sz, 0);
		//prev[s]=psum[]�� s ���� ������ ��ġ
		vector<int> prev(k, -1);
		REP(i, psum.sz)
		{
			//i��° ���ڸ� �ƿ� ������� �ʴ� ���
			if (i > 0)
				ret[i] = ret[i - 1];
			else
				ret[i] = 0;
			
			//psum[i]�� ������ �� ���� ������, prev[psum[i]] + 1 ���� ������� �� �� ����
			int loc = prev[psum[i]];
			if (loc != -1)
				ret[i] = max(ret[i], ret[loc] + 1);
			//prev[]�� ���� ��ġ�� ����Ѵ�
			prev[psum[i]] = i;
		}
		return ret.back();
	}
};