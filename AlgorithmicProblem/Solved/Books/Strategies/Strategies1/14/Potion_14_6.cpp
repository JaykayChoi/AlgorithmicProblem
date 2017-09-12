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

//https://algospot.com/judge/problem/read/POTION

class Potion_14_6
{
public:

private:
	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}

	// �м� a/b ���� ���ų� ū �ּ��� �ڿ����� ��ȯ�Ѵ�
	int ceil(int a, int b) {
		return (a + b - 1) / b;
	}

	// ������ �� �����ǿ� �̹� ���� ����� ���� �־��� ��, �� ���� ����� ���� ���Ѵ�
	vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
		int n = recipe.size();
		// ��� recipe[] �� �ִ������� ���Ѵ�
		int b = recipe[0];
		for (int i = 1; i < n; i++) b = gcd(b, recipe[i]);
		// �ּ��� b/b = 1 ��� ������ �ϹǷ�, a �� �ʱⰪ�� b �� �д�
		int a = b;
		// X �� ���� ���ϴ� ��� ceil(put[i] * b, recipe[i]) �� �ִ밪�� ���Ѵ�
		for (int i = 0; i < n; i++)
			a = max(a, ceil(put[i] * b, recipe[i]));
		// a/b �� �з��� ����� �ȴ�
		vector<int> ret(n);
		for (int i = 0; i < n; i++)
			ret[i] = recipe[i] * a / b - put[i];
		return ret;
	}

	// ������ �� �����ǿ� �̹� ���� ����� ���� �־��� ��, �� ���� ����� ���� ���Ѵ�
	vector<int> solveSimulation(const vector<int>& recipe, vector<int> put) {
		vector<int> oa = put;
		int n = recipe.size();
		vector<int> ret(n);
		// �� ��Ḧ �ּ��� recipe �� ���� ��ŭ�� �־�� �Ѵ�
		for (int i = 0; i < n; i++) {
			ret[i] = max(recipe[i] - put[i], 0);
			put[i] += ret[i];
		}
		// ������ ���� ���� ������ ��Ḧ ��� �߰�����
		int iter = 0;
		while (true) {
			++iter;
			// ���� ��Ḧ �� ���� �ʾƵ� �� ������ �ݺ��Ѵ�
			bool ok = true;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j) {
					// i ��° ��ῡ ���ϸ� ��� ���� put[i] / recipe[i] = X �� �̻��� �־�� �Ѵ�.
					// ���� put[j] �� recipe[j] * X �̻��� ������ �Ǿ�� �Ѵ�.
					int required = (put[i] * recipe[j] + recipe[i] - 1) / recipe[i];
					// �� �־�� �ϴ°�?
					if (required > put[j]) {
						ret[j] += required - put[j];
						put[j] = required;
						ok = false;
					}
				}
			if (ok) break;
		}
		fprintf(stderr, "%d iterations.\n", iter);
		if (iter == 228) {
			for (int i = 0; i < n; i++) fprintf(stderr, "%d ", recipe[i]); fprintf(stderr, "\n");
			for (int i = 0; i < n; i++) fprintf(stderr, "%d ", oa[i]); fprintf(stderr, "\n");
		}
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int n;
			cin >> n;
			vector<int> recipe(n);
			vector<int> put(n);
			for (int i = 0; i < n; i++) cin >> recipe[i];
			for (int i = 0; i < n; i++) cin >> put[i];

			vector<int> ret = solve(recipe, put);
			vector<int> ret2 = solveSimulation(recipe, put);
			assert(ret == ret2);
			for (int i = 0; i < n; i++)
				printf("%s%d", (i ? " " : ""), ret[i]);
			printf("\n");
		}
	}
};
