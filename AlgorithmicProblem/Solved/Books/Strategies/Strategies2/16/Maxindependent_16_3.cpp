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


const int MAXN = 25;

class Maxindependent_16_3
{
public:

private:
	int n;
	// explodes[i] �� i �� ���� �ξ��� �� �����ϴ� ������ ����
	int explodes[MAXN];

	// �־��� ������ ���������� Ȯ���Ѵ�
	bool isStable(int set) {
		for (int i = 0; i < n; ++i)
			if ((set & (1 << i)) && (set & explodes[i]))
				return false;
		return true;
	}

	// ��� �������� ������ ���� ����
	int countStableSet() {
		int ret = 0;
		// ��� ������ ����� ����
		for (int set = 1; set < (1 << n); ++set) {
			// �켱 �������� �ƴ϶�� �� �ʿ䰡 ����.
			if (!isStable(set)) continue;
			// �ش� ���� �������� Ȯ���ϱ� ����, ���� �� �ִ� �ٸ� ������ �ֳ� Ȯ���Ѵ�
			bool canExtend = false;
			for (int add = 0; add < n; ++add)
				// add �� ���տ� ���ԵǾ� ���� �ʰ�, set �� add �� �־ �������̶��
				if ((set & (1 << add)) == 0 && (explodes[add] & set) == 0) {
					canExtend = true;
					break;
				}
			if (!canExtend)
				++ret;
		}
		return ret;
	}

	// � �κ������� �� ���� �ִ��� ǥ���Ѵ�
	bool seen[1 << MAXN];

	int countStableSet2() {
		int ret = 0;
		memset(seen, 0, sizeof(seen));
		// �� �� ���պ��� �����ؼ� ������ �����´�
		for (int set = (1 << n) - 1; set > 0; --set) {
			// �� ������ � �ش� ���� ������ �κ� �����̰ų�, ���������� ���� ��� �����Ѵ�
			if (seen[set] || !isStable(set)) continue;
			// �� ������ ��� ������ ������ �����Ѵ�
			for (int subset = (set - 1) & set; subset > 0; subset = (subset - 1) & set)
				seen[subset] = true;
			++ret;
		}
		return ret;
	}

	int CInput(int argc, char* argv[]) {
		const int TRIALS = 20;
		srand(12743);
		n = MAXN;
		memset(explodes, 0, sizeof(explodes));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				if (rand() % 3 == 0) {
					explodes[i] |= (1 << j);
					explodes[j] |= (1 << i);
				}
		for (int it = 0; it < TRIALS; ++it) {
			//clock_t timer1 = clock();
			int a = countStableSet();
			printf("."); fflush(stdout);

		}

		printf("\n");

	}
};