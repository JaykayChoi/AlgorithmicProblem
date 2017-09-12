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

//https://algospot.com/judge/problem/read/MATCHORDER

class MatchOrder_10_1
{
public:
	void Solve()
	{
		Input();
	}
private:

#pragma region answer
	int brute(const vector<int>& russian, vector<int> korean) {
		sort(korean.begin(), korean.end());
		int ret = 0;
		do {
			int wins = 0;
			for (int i = 0; i < korean.size(); i++)
				if (korean[i] >= russian[i])
					++wins;
			ret = max(wins, ret);
		} while (next_permutation(korean.begin(), korean.end()));
		return ret;
	}

	int greedy(const vector<int>& russian, vector<int> korean) {
		int n = russian.size();
		vector<bool> taken(n, false);
		sort(korean.begin(), korean.end(), greater<int>());
		int ret = 0;
		for (int kor = 0; kor < n; kor++) {
			int opponent = -1;
			for (int rus = 0; rus < n; rus++)
				if (!taken[rus] && russian[rus] <= korean[kor] &&
					(opponent == -1 || russian[opponent] <= russian[rus]))
					opponent = rus;
			if (opponent == -1) break;
			++ret;
			taken[opponent] = true;
		}
		return ret;
	}

	int greedy2(const vector<int>& russian, const vector<int>& korean) {
		int n = russian.size(), wins = 0;
		// 아직 남아 있는 선수들의 레이팅
		multiset<int> ratings(korean.begin(), korean.end());
		for (int rus = 0; rus < n; rus++) {
			// 가장 레이팅이 높은 한국 선수가 이길 수 없는 경우 가장 레이팅이 낮은 선수와 경기시킨다.
			if (*ratings.rbegin() < russian[rus])
				ratings.erase(ratings.begin());
			// 그 외의 경우 이길 수 있는 선수 중 가장 레이팅이 낮은 선수와 경기시킨다.
			else {
				ratings.erase(ratings.lower_bound(russian[rus]));
				++wins;
			}
		}
		return wins;
	}
#pragma endregion

	void Input()
	{
		string filePath = "MatchOrder_10_1_Input.txt";
		vector<string> inputs = GetLine_InputFile(filePath);

		int problems = stoi(inputs[0]);

		REP(i, problems)
		{
			vector<int> rus = SplitStringToInt(inputs[2 + i * 3]);
			vector<int> kor = SplitStringToInt(inputs[3 + i * 3]);

			cout << Greedy(rus, kor) << endl;
		}
	}

	int bruteForce(const vector<int>& rus, vector<int> kor)
	{
		sort(kor.begin(), kor.end());

		int ret = 0;

		do
		{
			int wins = 0;
			REP(i, kor.size())
			{
				if (kor[i] >= rus[i])
					wins++;
			}
			ret = max(ret, wins);

		} while (next_permutation(kor.begin(), kor.end()));
		return ret;
	}

	int Greedy(const vector<int>& rus, vector<int> kor)
	{
		int n = rus.size();
		vector<bool> taken(n, false);
		sort(kor.begin(), kor.end(), greater<int>());

		int ret = 0;
		REP(korean, n)
		{
			int opponent = -1;
			REP(russian, n)
			{
				if (taken[russian] == false && rus[russian] <= kor[korean] &&
					(opponent == -1 || rus[opponent] <= rus[russian]))
					opponent = russian;
			}

			if (opponent == -1)
				break;

			ret++;
			taken[opponent] = true;
		}
		return ret;
	}
};