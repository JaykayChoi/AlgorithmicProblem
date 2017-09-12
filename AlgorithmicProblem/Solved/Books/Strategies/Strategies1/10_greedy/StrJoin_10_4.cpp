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
	// lengths ���� �ּҰ��� ����� �� ���� ��ȯ�Ѵ�.
	int pop(vector<int>& lengths) {
		vector<int>::iterator min = min_element(lengths.begin(), lengths.end());
		int ret = *min;
		lengths.erase(min);
		return ret;
	}

	// ���ڿ����� ���̰� �־��� �� �ϳ��� ��ġ�� �ּ� ����� ��ȯ�Ѵ�.
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

	// ���ڿ����� ���̰� �־��� �� �ϳ��� ��ġ�� �ּ� ����� ��ȯ�Ѵ�.
	int concat(const vector<int>& lengths) {
		// �ּ� ť�� �����Ѵ�
		priority_queue<int, vector<int>, greater<int> > pq;
		for (int i = 0; i < lengths.size(); ++i)
			pq.push(lengths[i]);

		int ret = 0;
		// ���Ұ� 1�� �̻� ���� ���� �ݺ��Ѵ�
		while (pq.size() > 1) {
			// ���� ª�� ���ڿ� �� ���� ã�Ƽ� ��ġ�� ť�� �ִ´�
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