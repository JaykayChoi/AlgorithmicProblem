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

//���̻� �迭�� �̿��� �ٸ� �κ� ���ڿ��� ���� ���� �˰���
class SubstringCount_20_5
{
public:

private:
	// �� ���̻���� ù t ���ڸ� �������� �� �׷� ��ȣ�� �־��� ��,
	// �־��� �� ���̻縦 ù 2*t ���ڸ� �������� ���Ѵ�.
	struct Comparator {
		const vector<int>& group;
		int t;

		Comparator(const vector<int>& _group, int _h) : group(_group), t(_h) { }

		bool operator () (int a, int b) {
			// ù t ���ڰ� �ٸ��� �̵��� �̿��� ���Ѵ�
			if (group[a] != group[b]) return group[a] < group[b];
			// �ƴ϶�� S_(a+t) �� S_(b+t) �� ù t ���ڸ� ���Ѵ�
			return group[a + t] < group[b + t];
		}
	};


	// s �� ���̻� �迭�� ����Ѵ�
	vector<int> getSuffixArray(const string& s) {
		int n = s.size();

		// �� ���̻縦 ù ���ڸ� �������� ������ ��, ù ���ڰ� ���� �� ����
		// �׷����� ���� �� ���̻簡 � �׷쿡 ���ϴ����� �����ִ� group[] �迭�� �����..
		// ��ſ� group[i] = S_i �� ù ���ڷ� �ϸ� ���� ȿ���� �ִ�.
		vector<int> group(n + 1);
		for (int i = 0; i < n; i++) group[i] = s[i];
		group[n] = -987654321;

		// ��������� ���̻� �迭�� �� ��ȯ��. �� �迭�� lg(n) �� �����Ѵ�.
		vector<int> perm(n);
		for (int i = 0; i < n; i++) perm[i] = i;

		// group[] �� ù t ���ڸ� �������� �����Ǿ� �ִ�
		int t = 1;
		while (t < n) {
			// ù 2t ���ڸ� �������� perm �� �ٽ� �����Ѵ�
			Comparator compareUsing2T(group, t);
			sort(perm.begin(), perm.end(), compareUsing2T);

			// 2t ���ڰ� n �� �Ѵ´ٸ� ���� ���̻� �迭 �ϼ�!
			t *= 2;
			if (t >= n) break;

			// 2t ���ڸ� �������� �� �׷� ������ �����
			vector<int> newGroup(n);
			newGroup[perm[0]] = 0;
			for (int i = 1; i < perm.size(); i++)
				if (compareUsing2T(perm[i - 1], perm[i]))
					newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
				else
					newGroup[perm[i]] = newGroup[perm[i - 1]];
			group = newGroup;
		}
		return perm;
	}

	int countSubstringsNaive(const string& s) {
		set<string> m;
		for (int i = 0; i < s.size(); i++)
			for (int j = i; j < s.size(); j++)
				m.insert(s.substr(i, j - i + 1));
		return m.size();
	}

	// s[i..] �� s[j..] �� ���� ���λ��� �ִ� ���̸� ����Ѵ�
	int commonPrefix(const string& s, int i, int j) {
		int k = 0;
		while (i < s.size() && j < s.size() && s[i] == s[j]) { ++i; ++j; ++k; }
		return k;
	}

	
	// s �� ���� �ٸ� �κ� ���ڿ��� ���� ����
	int countSubstrings(const string& s) {
		vector<int> a = getSuffixArray(s);
		int ret = 0;
		int n = s.size();
		for (int i = 0; i < a.size(); ++i) {
			int cp = 0;
			if (i > 0) cp = commonPrefix(s, a[i - 1], a[i]);
			// a[i] �� (n - a[i]) ���� ���λ�� �߿��� cp ���� �ߺ��̴�.
			ret += s.size() - a[i] - cp;
		}
		return ret;
	}

	int CInput() {
		string s;
		while (cin >> s) {
			cout << countSubstrings(s) << endl;
		}
		const int ITER = 100000;
		for (int i = 0; i < ITER; i++) {
			int n = rand() % 100 + 1;
			string s;
			for (int j = 0; j < n; j++)
				s += char('a' + rand() % 2);
			int a = countSubstrings(s);
			int b = countSubstringsNaive(s);
			if (a != b) {
				cout << s << " expected " << b << " result " << a << endl;
				break;
			}

		}
		printf("all good.\n");
	}
};
