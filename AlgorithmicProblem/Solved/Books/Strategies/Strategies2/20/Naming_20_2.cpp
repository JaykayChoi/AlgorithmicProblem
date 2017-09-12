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

//https://algospot.com/judge/problem/read/NAMING

class Naming_20_2
{
public:
	void Solve()
	{
		CInput();
	}
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
		// ���ڿ��� ���� ������ ������ ã���鼭 �κ� ��ġ�� ��� ����Ѵ�.
		while (begin + matched < m) {
			if (N[begin + matched] == N[matched]) {
				++matched;
				pi[begin + matched - 1] = matched;
			}
			else {
				if (matched == 0)
					++begin;
				else {
					begin += max(1, matched - pi[matched - 1]);
					matched = pi[matched - 1];
				}
			}
		}
		return pi;
	}

	// s �� ���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ����� ���̸� ��ȯ�Ѵ�
	vector<int> getPrefixSuffix(const string& s) {
		vector<int> ret, pi = getPartialMatch(s);

		int k = s.size();
		while (k > 0) {
			// s[..k-1] �� ���̴�
			ret.push_back(k);
			// s[..k-1] �� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� ���̴�
			k = pi[k - 1];
		}
		return ret;
	}

	void CInput() 
	{
		string s = "abc";

		vector<int> ret = getPrefixSuffix(s);
		reverse(ret.begin(), ret.end());
		for (int i = 0; i < ret.size(); i++)
			printf("%s%d", (i ? " " : ""), ret[i]);
		printf("\n");
	}

};