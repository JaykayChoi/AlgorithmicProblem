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

//https://algospot.com/judge/problem/read/GRADUATION

const int INF = 987654321;
const int MAXN = 20;
class Graduation_16_4
{
public:

private:
	void Input()
	{
		string filePath = "Graduation_16_4_Input.txt";
		queue<string> inputs = GetLine_InputFileAsQueue(filePath);

		int numberProblems = stoi(Dequeue(inputs));

		REP(i, numberProblems)
		{

		}
	}

	int n, k, m, l;
	// prerequisite[i] = i ��° ������ ���������� ����
	int prerequisite[MAXN];
	// classes[i] = i ��° �б⿡ �����Ǵ� ������ ����
	int classes[10];

	int cache[10][1 << MAXN];

	// n �� ������ ǥ������ ���� ��Ʈ�� ���� ��ȯ�Ѵ�
	int bitCount(int n) {
		return __builtin_popcount(n);
	}

	// �̹� �бⰡ semester �̰�, ���ݱ��� ���� ������ ������ taken �� ��
	// k �� �̻��� ������ ��� �������� �� �б⳪ �� �־�� �ϴ°�?
	int graduate(int semester, int taken) {
		// ���� ���: k �� �̻��� ������ �̹� ���� ���
		if (bitCount(taken) >= k) return 0;
		// ���� ���: m �бⰡ ���� ���� ���
		if (semester == m) return INF;

		// �޸������̼�
		int& ret = cache[semester][taken];
		if (ret != -1) return ret;
		ret = INF;

		// �̹� �б⿡ ���� �� �ִ� ���� �� ���� ���� ���� ������� ã�´�
		int canTake = (classes[semester] & ~taken);
		// ���� ������ �� ���� ���� ������� �ɷ�����
		for (int i = 0; i < n; i++)
			if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
				canTake &= ~(1 << i);
		// �� ������ ��� �κ������� ��ȸ�Ѵ�
		for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
			// �� �б⿡ l ��������� ���� �� �ִ�
			if (bitCount(take) > l) continue;
			ret = min(ret, graduate(semester + 1, taken | take) + 1);
		}

		// �̹� �б⿡ �ƹ� �͵� ���� ���� ���
		ret = min(ret, graduate(semester + 1, taken));
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n >> k >> m >> l;
			for (int i = 0; i < n; i++) {
				prerequisite[i] = 0;
				int r;
				cin >> r;
				for (int j = 0; j < r; j++) {
					int required;
					cin >> required;
					prerequisite[i] |= (1 << required);
				}
			}
			for (int i = 0; i < m; i++) {
				classes[i] = 0;
				int c;
				cin >> c;
				for (int j = 0; j < c; j++) {
					int open;
					cin >> open;
					classes[i] |= (1 << open);
				}
			}
			memset(cache, -1, sizeof(cache));
			int ret = graduate(0, 0);
			if (ret >= 987654321) ret = -1;
			cout << ret << endl;
		}
	}
};