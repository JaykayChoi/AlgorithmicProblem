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

class SuffixArray_20_5
{
public:


private:
	// �� ���̻��� ���� ��ġ i, j �� �־��� �� �� ���̻� �� ��� ���� �տ� �;� �� �� ���Ѵ�
	struct SuffixComparator {
		const string& s;
		SuffixComparator(const string& s) : s(s) {}
		bool operator () (int i, int j) {
			// s.substr() ��ſ� strcmp() �� ���� �ӽ� ��ü�� ����� ����� ����ȴ�
			return strcmp(s.c_str() + i, s.c_str() + j) < 0;
		}
	};

	//���̻� �迭�� ����ϴ� �ܼ��� �˰���
	// s �� ���̻� �迭�� ����Ѵ�
	vector<int> getSuffixArrayNaive(const string& s) {
		// ���̻� ���� ��ġ�� ���� �迭�� �����
		vector<int> perm;
		for (int i = 0; i < s.size(); i++) perm.push_back(i);
		// ���̻縦 ���ϴ� ���ڸ� �̿��� �����ϸ� �ϼ�!
		sort(perm.begin(), perm.end(), SuffixComparator(s));
		return perm;
	}

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

	//���̻� �迭�� �輭�����ϴ� ����� ���̾�� �˰���
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
			vector<int> newGroup(n + 1);
			newGroup[n] = -1;
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

	int search(const string& H, const vector<int>& a, const string& N) {
		int lo = -1, hi = H.size();
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (strncmp(H.c_str() + a[mid], N.c_str(), N.size()) < 0)
				lo = mid;
			else
				hi = mid;
		}
		// ���� ���� ã�ҳ� Ȯ������.
		if (hi == H.size() || strncmp(H.c_str() + a[hi], N.c_str(), N.size()) != 0)
			return -1;
		return a[hi];
	}

	string toString(int mask, int len) {
		string ret;
		for (int i = 0; i < len; i++)
			if (mask & (1 << i))
				ret += 'a';
			else
				ret += 'b';
		return ret;
	}

	void testAll() {
		for (int len = 1; len <= 20; ++len) {
			for (int mask = 0; mask < (1 << len); ++mask) {
				string S = toString(mask, len);
				vector<int> a = getSuffixArrayNaive(S);
				vector<int> b = getSuffixArray(S);
				assert(a == b);
			}
		}
	}

	void testSearch() {
		for (int len = 1; len <= 14; ++len) {
			printf("Haystack length=%d\n", len);
			for (int mask = 0; mask < (1 << len); ++mask) {
				string H = toString(mask, len);
				vector<int> A = getSuffixArray(H);
				for (int nl = 1; nl <= len; ++nl) {
					for (int nmask = 0; nmask < (1 << nl); ++nmask) {
						string N = toString(nmask, nl);

						int f = search(H, A, N);
						if (f == -1) {
							if (H.find(N) != -1) {
								printf("Could not find N=%s from H=%s\n", N.c_str(), H.c_str());
								assert(false);
							}
						}
						else {
							string H2 = H.substr(f, N.size());
							if (H2 != N) {
								printf("Wrong return finding N=%s from H=%s, returned %d where substring is %s\n",
									N.c_str(), H.c_str(), f, H2.c_str());
								search(H, A, N);
								assert(false);
							}
						}
					}
				}
			}
		}
	}


	int CInput() {
		/*
		string s;
		while(cin >> s) {
		vector<int> perm = getSuffixArray(s);
		for(int i = 0; i < perm.size(); i++)
		printf("%d: %s\n", perm[i], s.c_str() + perm[i]);

		}*/
		testSearch();
		testAll();
		printf("all good.\n");
	}
};
