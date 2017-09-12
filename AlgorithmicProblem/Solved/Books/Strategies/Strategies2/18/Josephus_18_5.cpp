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

//https://algospot.com/judge/problem/read/JOSEPHUS
//https://ko.wikipedia.org/wiki/%EC%9A%94%EC%84%B8%ED%91%B8%EC%8A%A4_%EB%AC%B8%EC%A0%9C

class Josephus_18_5
{
public:

private:
	void josephusQueue(int n, int k) {
		// 큐를 준비한다
		queue<int> survivors;
		for (int i = 1; i <= n; i++) survivors.push(i);

		// queue.size() 는 O(1) 이기 때문에
		while (survivors.size() > 2) {
			// 한명을 꺼내서 버린다
			survivors.pop();

			// k-1 명을 맨 앞에서 꺼내 큐의 뒤로 보낸다
			for (int i = 0; i < k - 1; i++) {
				survivors.push(survivors.front());
				survivors.pop();
			}
		}
		// 남은 두 사람이 생존자
		int a = survivors.front(); survivors.pop();
		int b = survivors.front();
		if (a > b) swap(a, b);
		cout << a << " " << b << endl;
	}

	void josephus(int n, int k) {
		// 리스트를 준비한다
		list<int> survivors;
		for (int i = 1; i <= n; i++) survivors.push_back(i);

		// 이번에 죽을 사람을 나타내는 포인터
		list<int>::iterator kill = survivors.begin();
		while (n > 2) {
			// 첫 번째 사람이 자살한다
			kill = survivors.erase(kill);
			if (kill == survivors.end()) kill = survivors.begin();
			--n;

			// k-1 번 다음 사람으로 옮긴다
			for (int i = 0; i < (k - 1) % n; i++) {
				++kill;
				if (kill == survivors.end()) kill = survivors.begin();
			}
		}

		// 오름차순 출력을 위해 정렬한다
		survivors.sort();
		cout << survivors.front() << " " << survivors.back() << endl;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int n, k;
			cin >> n >> k;
			josephus(n, k);
			josephusQueue(n, k);
		}
	}
};