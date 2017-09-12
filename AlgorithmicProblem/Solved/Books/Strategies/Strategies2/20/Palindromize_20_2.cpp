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

//https://algospot.com/judge/problem/read/PALINDROMIZE

class Palindromize_20_2
{
public:

private:
	// N ���� �ڱ� �ڽ��� ã���鼭 ��Ÿ���� �κ� ��ġ�� �̿���
	// pi[] �� ����Ѵ�.
	// pi[i] = N[..i] �� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
	vector<int> getPartialMatch(const string& N) {
		int m = N.size();
		vector<int> pi(m, 0);

		// KMP �� �ڱ� �ڽ��� ã�´�

		// N �� N ���� ã�´�. begin=0 �̸� �ڱ� �ڽ��� ã�ƹ����ϱ� �ȵ�!
		int begin = 1, matched = 0;
		// ���� ���ڰ� N �� ���� ������ ������ ã���鼭 �κ� ��ġ�� ��� ����Ѵ�.
		while (begin + matched < m) {
			if (N[begin + matched] == N[matched]) {
				++matched;
				pi[begin + matched - 1] = matched;
			}
			else {
				if (matched == 0)
					++begin;
				else {
					begin += matched - pi[matched - 1];
					matched = pi[matched - 1];
				}
			}
		}
		return pi;
	}

	// a �� ���̻��̸鼭 b �� ���λ��� ���ڿ��� �ִ� ���̸� ���Ѵ�
	int maxOverlap(const string& a, const string& b) {
		int n = a.size(), m = b.size();
		vector<int> pi = getPartialMatch(b);
		// begin = matched = 0 �������� ��������
		int begin = 0, matched = 0;
		while (begin < n) {
			// ���� ¤������ �ش� ���ڰ� �ٴ��� �ش� ���ڿ� ���ٸ�
			if (matched < m && a[begin + matched] == b[matched]) {
				++matched;
				if (begin + matched == n)
					return matched;
			}
			else {
				if (matched == 0)
					++begin;
				else {
					begin += matched - pi[matched - 1];
					matched = pi[matched - 1];
				}
			}
		}
		return 0;
	}

	void CInput() {
		string s;
		while (cin >> s) {
			string sr = s;
			reverse(sr.begin(), sr.end());
			if (sr == s)
				cout << s << endl;
			else {
				int ov = maxOverlap(s, sr);
				cout << s << sr.substr(ov) << endl;
			}
		}

	}
};
