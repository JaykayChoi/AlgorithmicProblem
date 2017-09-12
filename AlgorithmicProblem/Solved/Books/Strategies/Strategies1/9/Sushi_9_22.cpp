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

//https://algospot.com/judge/problem/read/SUSHI

const int MAX_BUDGET = 10000;
class Sushi_9_22
{
public:
	void Solve()
	{
		Input();
	}
private:
	int n, m, price[50], pref[50];
	
	void Input()
	{
		string filePath = "Sushi_9_22_Input.txt";
		queue<string> inputLines = GetLine_InputFileAsQueue(filePath);

		int ploblems = stoi(Dequeue(inputLines));

		REP(i, 1)
		{
			vector<int> nm = SplitStringToInt(Dequeue(inputLines));
			n = nm[0];
			m = nm[1] / 100;

			REP(j, n)
			{
				vector<int> item = SplitStringToInt(Dequeue(inputLines));
				price[j] = item[0] / 100;
				pref[j] = item[1];
			}
			CLEAR(cache, -1);
			cout << sushi(m) << endl;

			cout << sushi2() << endl;
			cout << sushi3() << endl;
		}
	}

	int cache[MAX_BUDGET + 1];

	// budget 만큼의 예산으로 초밥을 먹어서 얻을 수 있는 최대 선호도
	int sushi(int budget) {
		// 메모이제이션
		int& ret = cache[budget];
		if (ret != -1) return ret;
		ret = 0;
		for (int dish = 0; dish < n; ++dish) {
			if (budget < price[dish]) continue;
			ret = max(ret, sushi(budget - price[dish]) + pref[dish]);
		}
		return ret;
	}

	int c[MAX_BUDGET + 1];
	// sushi() 를 반복적 동적 계획법으로 구현하기
	int sushi2() {
		int ret = 0;
		for (int budget = 1; budget <= m; ++budget) {
			c[budget] = 0;
			for (int dish = 0; dish < n; ++dish)
				if (budget >= price[dish])
					c[budget] = max(c[budget],
						c[budget - price[dish]] + pref[dish]);
			ret = max(ret, c[budget]);
		}
		return ret;
	}

	//int c[201];
	int sushi3() {
		int ret = 0;
		c[0] = 0;
		for (int budget = 1; budget <= m; ++budget) {
			int cand = 0;
			for (int dish = 0; dish < n; ++dish)
				if (budget >= price[dish])
					cand = max(cand, c[(budget - price[dish]) % 201] + pref[dish]);
			c[budget % 201] = cand;
			ret = max(ret, cand);
		}
		return ret;
	}
};