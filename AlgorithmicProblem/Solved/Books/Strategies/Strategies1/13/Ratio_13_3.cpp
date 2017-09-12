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

//https://algospot.com/judge/problem/read/RATIO

class Ratio_13_3
{
public:
	void Solve()
	{
		Input();
	}
private:

#pragma region answer
	// �����̰� �� ������ �ִ� �ִ� ���� ��
	long long L = 2000000000;

	// b���� �� a���� �¸����� ���� �·�
	int ratio(long long b, long long a) {
		return (a * 100) / b;
	}

	// �ּ� �� �����ؾ� �·��� �ö󰥱�?
	int neededGames(long long games, long long won) {
		// �Ұ����� ��츦 �̸� �ɷ�����
		if (ratio(games, won) == ratio(games + L, won + L))
			return -1;
		long long lo = 0, hi = L;
		// �ݺ��� �Һ���: 
		// 1. lo ���� �̱�� �·��� ������ �ʴ´�
		// 2. hi ���� �̱�� �·��� ���Ѵ�
		while (lo + 1 < hi) {
			long long mid = (lo + hi) / 2;
			if (ratio(games, won) == ratio(games + mid, won + mid))
				lo = mid;
			else
				hi = mid;
		}
		return hi;
	}

	long long ceil(long long a, long long b) {
		return (a + b - 1) / b;
	}

	long long neededGames2(long long N, long long M) {
		long long R = ratio(N, M) + 1;
		// ���� �·��� 100% �� ��� 101% �� �� �� ����.
		// ���� �·��� 99% ��� ���� 100% �� �Ǳ�� �Ұ����ϴ�.
		if (R >= 100) return -1;
		return ceil(R*N - 100 * M, 100 - R);
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int n, m;
			cin >> n >> m;
			int a = neededGames(n, m);
			int b = neededGames2(n, m);
			assert(a == b);
			cout << a << endl;


		}
	}
#pragma endregion

	ll maxGames = 2000000000;

	void Input()
	{
		string filePath = "Ratio_13_3_Input.txt";
		vector<string> lines = GetLine_InputFile(filePath);

		int ploblems = stoi(lines[0]);

		REP(i, ploblems)
		{
			vector<int> nm = SplitStringToInt(lines[1 + i]);
			cout << calcNeedGames(nm[0], nm[1]) << endl;
		}
	}

	int calcNeedGames(ll games, int won)
	{
		if (calcRatio(games, won) == calcRatio(games + maxGames, won + maxGames))
			return -1;

		ll lo = 0;
		ll hi = maxGames;

		while (lo + 1 < hi)
		{
			ll mid = (lo + hi) / 2;

			if (calcRatio(games, won) == calcRatio(games + mid, won + mid))
				lo = mid;
			else
				hi = mid;
		}

		return hi;
	}

	// b���� �� a���� �¸����� ���� �·�
	int calcRatio(long long b, long long a)
	{
		return (a * 100) / b;
	}
};