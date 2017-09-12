#include "Utils.h"
using namespace std;
using namespace Utils;
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
typedef long long ll;

//https://algospot.com/judge/problem/read/ALLERGY

class Allergy_11_5
{
public:

private:
	
	int n, m;
	// canEat[person] = person �� ���� �� �ִ� ���ĵ��� ��ȣ
	// eaters[food] = food �� ���� �� �ִ� ģ������ ��ȣ
	vector<int> canEat[50], eaters[50];

	int best;
	// chosen: ���ݱ��� ������ ������ ��
	// edible: �� �� �� ģ���� ���� �� �ִ� ������ ��
	void search(vector<int>& edible, int chosen) {
		// ������ ����ġ��
		if (chosen >= best) return;

		// ���� ���� ������ ���� ù ��° ģ���� ã�´�
		int first = 0;
		while (first < n && edible[first] > 0) ++first;

		// ��� ģ���� ���� ������ �ִ� ��� �����Ѵ�
		if (first == n) { best = chosen; return; }

		// �� ģ���� ���� �� �ִ� ������ �ϳ� �����
		for (int i = 0; i < canEat[first].size(); ++i) {
			int food = canEat[first][i];
			for (int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]++;
			search(edible, chosen + 1);
			for (int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]--;
		}
	}

	int solve() {
		vector<int> edible(n, 0);
		best = m;
		search(edible, 0);
		return best;
	}

	int greedy() {
		// greedy
		vector<int> satisfied(n, 0);
		int selected = 0;
		while (true) {
			if (find(satisfied.begin(), satisfied.end(), 0) == satisfied.end()) break;
			int bestFood = -1, bestBet = -1;
			for (int food = 0; food < m; ++food) {
				int canSatisfy = 0;
				for (int i = 0; i < eaters[food].size(); i++) {
					int person = eaters[food][i];
					if (satisfied[person] == 0) {
						canSatisfy++;
					}
				}
				if (canSatisfy >= bestBet) {
					bestFood = food;
					bestBet = canSatisfy;
				}
			}
			++selected;
			for (int i = 0; i < eaters[bestFood].size(); i++) {
				int person = eaters[bestFood][i];
				satisfied[person]++;
			}

		}
		return selected;
	}

	// food: �̹��� ����ؾ� �� ������ ��ȣ
	// edible: ���ݱ��� �� ���� �� �� ģ���� ���� �� �ִ� ������ ��
	// chosen: ���ݱ��� �� ������ ��
	void slowSearch(int food, vector<int>& edible, int chosen) {
		// ������ ����ġ��
		if (chosen >= best) return;

		// ���� ���: ��� ���Ŀ� ���� ������ ���θ� ����������,
		// ��� ģ���� ������ ���� �� �ִ��� Ȯ���ϰ� �׷��ٸ� �����ظ� �����Ѵ�
		if (food == m) {
			if (find(edible.begin(), edible.end(), 0) == edible.end())
				best = chosen;
			return;
		}

		// food ������ ������ �ʴ� ���
		slowSearch(food + 1, edible, chosen);

		// food �� ����� ���
		for (int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]++;
		slowSearch(food + 1, edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); ++j) edible[eaters[food][j]]--;
	}

	int solve2() {
		best = m;
		//greedy();
		vector<int> edible(n, 0);
		slowSearch(0, edible, 0);
	}

	int CInput(int argc, char* argv[]) 
	{
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n >> m;
			for (int i = 0; i < 50; i++) {
				canEat[i].clear();
				eaters[i].clear();
			}
			map<string, int> names;
			for (int i = 0; i < n; i++) {
				string name;
				cin >> name;
				names[name] = i;
			}


			for (int food = 0; food < m; food++) {
				int sz;
				cin >> sz;
				for (int j = 0; j < sz; j++) {
					string name;
					cin >> name;
					int eater = names[name];
					eaters[food].push_back(eater);
					canEat[eater].push_back(food);
				}
			}

			string algo = "search1";
			if (argc > 1) algo = argv[1];

			if (algo == "search1")
				cout << solve() << endl;
			else if (algo == "slowSearch")
				cout << solve2() << endl;
			else if (algo == "greedy")
				cout << greedy() << endl;
			else {
				printf("Unknown algo %s\n", algo.c_str());
				break;
			}

		}
	}
	
};
