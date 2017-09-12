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
		// ť�� �غ��Ѵ�
		queue<int> survivors;
		for (int i = 1; i <= n; i++) survivors.push(i);

		// queue.size() �� O(1) �̱� ������
		while (survivors.size() > 2) {
			// �Ѹ��� ������ ������
			survivors.pop();

			// k-1 ���� �� �տ��� ���� ť�� �ڷ� ������
			for (int i = 0; i < k - 1; i++) {
				survivors.push(survivors.front());
				survivors.pop();
			}
		}
		// ���� �� ����� ������
		int a = survivors.front(); survivors.pop();
		int b = survivors.front();
		if (a > b) swap(a, b);
		cout << a << " " << b << endl;
	}

	void josephus(int n, int k) {
		// ����Ʈ�� �غ��Ѵ�
		list<int> survivors;
		for (int i = 1; i <= n; i++) survivors.push_back(i);

		// �̹��� ���� ����� ��Ÿ���� ������
		list<int>::iterator kill = survivors.begin();
		while (n > 2) {
			// ù ��° ����� �ڻ��Ѵ�
			kill = survivors.erase(kill);
			if (kill == survivors.end()) kill = survivors.begin();
			--n;

			// k-1 �� ���� ������� �ű��
			for (int i = 0; i < (k - 1) % n; i++) {
				++kill;
				if (kill == survivors.end()) kill = survivors.begin();
			}
		}

		// �������� ����� ���� �����Ѵ�
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