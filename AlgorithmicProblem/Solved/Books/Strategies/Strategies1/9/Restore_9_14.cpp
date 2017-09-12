#include "Utils.h"
using namespace std;
using namespace Utils;

//문제
//
//토요일에 출근해서 연구실에서 놀고 있던 대학원생 진호는 실수로 실험에 사용하던 데이터를 삭제하고 말았습니다.복사본도 없는 터라 이대로라면 교수님의 진노를 한 몸에 받을 것은 자명한 일, 따라서 진호는 그럴 듯해 보이는 데이터를 위조하여 교수님의 분노를 피해 가기로 합니다.우리가 데이터에 대해 알고있는 것은, 데이터가 k개의 문자열 조각을 부분 문자열로 포함하며, 모두 알파벳 소문자로 구성된다는 사실 밖에 없습니다. (어떤 문자열의 부분 문자열은 해당 문자열의 연속된 일부분입니다.)
//
//주어진 문자열 조각들을 모두 부분 문자열로 포함하는 문자열 중 가장 짧은 것을 계산하는 프로그램을 작성하세요.만약 이와 같은 문자열이 여럿이라면 아무 문자열이나 출력하면 됩니다.
//
//입력
//
//입력의 첫 줄에는 테스트 케이스의 수 C(C≤50)가 주어집니다.각 테스트 케이스의 첫 줄에는 부분 문자열의 수 k(1≤k≤15)가 주어지고, 다음 k줄에 알파벳 소문자로만 구성된 문자열 조각이 주어집니다.각 문자열 조각의 길이는 1 이상 40 이하입니다.
//
//출력
//
//각 테스트 케이스마다 한 줄로, 해당 문자열을 모두 포함하는 가장 짧은 문자열 중 하나를 출력합니다.
//
//예제 입력
//
//3
//3
//geo
//oji
//jing
//2
//world
//hello
//3
//abrac
//cadabra
//dabr
//예제 출력
//
//geojing
//helloworld
//cadabrac

const int MAX_N = 16;

class Restore_9_14
{
public:

private:
	int k;
	string word[MAX_N];
	int cache[MAX_N][1 << MAX_N];
	int overlap[MAX_N][MAX_N];
	int restore(int last, int used) {
		// 기저 사례
		if (used == (1 << k) - 1) return 0;
		// 메모이제이션
		int& ret = cache[last][used];
		if (ret != -1) return ret;
		ret = 0;
		for (int next = 0; next < k; ++next)
			if ((used & (1 << next)) == 0) {
				int cand = overlap[last][next] +
					restore(next, used + (1 << next));
				ret = max(ret, cand);
			}
		return ret;
	}

	string reconstruct(int last, int used) {
		// 기저 사례
		if (used == (1 << k) - 1) return "";
		for (int next = 0; next < k; ++next)
			if ((used & (1 << next)) == 0 &&
				restore(last, used) ==
				overlap[last][next] + restore(next, used + (1 << next)))
				return word[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next));
		return "_oops_";
	}

	int getOverlap(const string& a, const string& b) {
		for (int len = min(a.size(), b.size()); len > 0; --len) {
			if (a.substr(a.size() - len) == b.substr(0, len))
				return len;
		}
		return 0;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> k;
			for (int i = 0; i < k; i++) cin >> word[i];
			memset(cache, -1, sizeof(cache));
			while (true) {
				bool removed = false;
				for (int i = 0; i < k && !removed; i++)
					for (int j = 0; j < k; j++)
						if (i != j && word[i].find(word[j]) != -1) {
							word[j] = word[k - 1];
							--k;
							removed = true;
						}

				if (!removed) break;
			}
			word[k] = "";
			sort(word, word + k);
			for (int i = 0; i <= k; i++)
				for (int j = 0; j <= k; j++)
					overlap[i][j] = getOverlap(word[i], word[j]);
			restore(k, 0);
			cout << reconstruct(k, 0) << endl;
		}
	}
};