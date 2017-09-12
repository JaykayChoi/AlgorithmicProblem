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

//https://algospot.com/judge/problem/read/JAEHASAFE

class JaehaSafe_20_3
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

	// "¤����" H �� �κ� ���ڿ��� "�ٴ�" N �� �����ϴ� ���� ��ġ���� ��� ��ȯ�Ѵ�.
	vector<int> kmpSearch(const string& H, const string& N) {
		int n = H.size(), m = N.size();
		vector<int> ret;

		// pi[] �� �̸� ����Ѵ�
		// pi[i] = N[..i] �� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
		vector<int> pi = getPartialMatch(N);

		// begin = matched = 0 �������� ��������
		int begin = 0, matched = 0;
		// begin �� �ִ밪�� n - m
		while (begin <= n - m) {
			// ���� ¤������ �ش� ���ڰ� �ٴ��� �ش� ���ڿ� ���ٸ�
			if (matched < m && H[begin + matched] == N[matched]) {
				++matched;
				// ��������� m ���ڰ� ��� ��ġ�ߴٸ� �信 �߰��Ѵ�
				if (matched == m) ret.push_back(begin);
			}
			else {
				// ����: matched �� 0 �� ��쿡�� ���� ĭ�������� ���
				if (matched == 0)
					++begin;
				else {
					// begin �� matched - pi[matched-1] ��ŭ �ű� �� �ִ�
					begin += matched - pi[matched - 1];
					// begin �� �Ű�ٰ� ó������ �ٽ� ���� �ʿ䰡 ����.
					// �ű� �Ŀ��� pi[matched-1] ��ŭ�� �׻� ��ġ�ϱ� �����̴�.
					matched = pi[matched - 1];
				}
			}
		}
		return ret;
	}


	int shifts(const string& original, const string& next) {
		return kmpSearch(original + original, next)[0];
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			string current, next;
			int n;
			cin >> n;
			cin >> current;
			int ret = 0;
			for (int i = 0; i < n; ++i) {
				cin >> next;
				if (i % 2 == 1)
					ret += shifts(current, next);
				else
					ret += shifts(next, current);
				current = next;
			}
			cout << ret << endl;

		}
	}
};