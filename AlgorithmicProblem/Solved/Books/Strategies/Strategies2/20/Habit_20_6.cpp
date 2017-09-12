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

//https://algospot.com/judge/problem/read/HABIT

class Habit_20_6
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
			// �ƴ϶�� S[a+t..] �� S[b+t..] �� ù t ���ڸ� ���Ѵ�
			return group[a + t] < group[b + t];
		}
	};


	// s �� ���̻� �迭�� ����Ѵ�
	vector<int> getSuffixArray(const string& s) {
		int n = s.size();

		// group[i] = ���̻���� ù t ���ڸ� �������� �������� ��,
		//            S[i..] �� ���� �׷� ��ȣ.
		// t = 1 �� ���� ������ �� ���� S[i..] �� ù ���ڷ� �׷� ��ȣ�� ���� �൵
		// ���� ȿ���� �ִ�.
		int t = 1;
		vector<int> group(n + 1);
		for (int i = 0; i < n; i++) group[i] = s[i];
		group[n] = -1;

		// ��������� ���̻� �迭�� �� ��ȯ��. �� �迭�� lg(n) �� �����Ѵ�.
		vector<int> perm(n);
		for (int i = 0; i < n; i++) perm[i] = i;

		while (t < n) {
			// group[] �� ù t ���ڸ� �������� ����� �״�.
			// ù 2t ���ڸ� �������� perm �� �ٽ� �����Ѵ�
			Comparator compareUsing2T(group, t);
			sort(perm.begin(), perm.end(), compareUsing2T);

			// 2t ���ڰ� n �� �Ѵ´ٸ� ���� ���̻� �迭 �ϼ�!
			t *= 2;
			if (t >= n) break;

			// 2t ���ڸ� �������� �� �׷� ������ �����
			vector<int> newGroup(n);
			newGroup[perm[0]] = 0;
			for (int i = 1; i < n; i++)
				if (compareUsing2T(perm[i - 1], perm[i]))
					newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
				else
					newGroup[perm[i]] = newGroup[perm[i - 1]];
			group = newGroup;
		}
		return perm;
	}

	// s[i..] �� s[j..] �� ���� ���λ��� �ִ� ���̸� ����Ѵ�
	int commonPrefix(const string& s, int i, int j) {
		int k = 0;
		while (i < s.size() && j < s.size() && s[i] == s[j]) { ++i; ++j; ++k; }
		return k;
	}

	// k �� �̻� �����ϴ� s �� �κ� ���ڿ� �� �ִ� ���̸� ã�´�
	int longestFrequent(int k, const string& s) {
		vector<int> a = getSuffixArray(s);
		int ret = 0;
		for (int i = 0; i + k <= s.size(); ++i)
			ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		while (cases--) {
			int k;
			string s;
			cin >> k >> s;
			cout << longestFrequent(k, s) << endl;
		}
	}
};
