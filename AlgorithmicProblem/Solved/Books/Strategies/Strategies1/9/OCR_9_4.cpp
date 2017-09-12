#include "Utils.h"
using namespace std;
using namespace Utils;

//https://algospot.com/judge/problem/read/OCR

class OCR_9_4
{
public:

private:
	string corpus[1001];

	int n, m;

	// �з��Ⱑ ��ȯ�� ����
	int R[100];
	// T[i][j] = i�ܾ� ���Ŀ� j�ܾ ���� Ȯ��
	double T[1001][1001];
	// M[i][j] = i�ܾ j�ܾ�� �з��� Ȯ��
	double M[1001][1001];

	int choice[102][1002];
	double cache[102][1002];

	// Q[segment] ���ĸ� ä���� ���� �� �ִ� �ִ� Ȯ����
	// Q[segment-1] == previousMatch ��� �����Ѵ�
	double recognize(int segment, int previousMatch) {
		if (segment == n) return 0;
		double& ret = cache[segment][previousMatch];
		if (ret < 0.5) return ret;
		ret = -1e200;
		int& choose = choice[segment][previousMatch];

		// R[segment] �� �����Ǵ� �ܾ ã�´�
		for (int thisMatch = 0; thisMatch < m; ++thisMatch) {
			// g(thisMatch) = T(previousMatch, thisMatch) *
			//                M(thisMatch, R[segment])
			double cand = T[previousMatch][thisMatch]
				+ M[thisMatch][R[segment]]
				+ recognize(segment + 1, thisMatch);
			if (ret < cand) {
				ret = cand;
				choose = thisMatch;
			}
		}
		return ret;
	}

	string reconstruct(int segment, int previousMatch) {
		if (segment == n) return "";
		int choose = choice[segment][previousMatch];
		double sol = recognize(segment, previousMatch);
		for (int next = 0; next < m; ++next) {
			if (next != choose) {
				double cand = T[previousMatch][next] + M[next][R[segment]] + recognize(segment + 1, next);
				if (fabs(cand - sol) < 1e-6)
					assert(false);
			}
		}
		return corpus[choose] + " " + reconstruct(segment + 1, choose);
	}

	int CInput() {
		int queries;
		cin >> m >> queries;
		assert(m <= 1000);
		assert(queries <= 100);
		for (int i = 0; i < m; i++) {
			cin >> corpus[i];
		}
		corpus[m] = "";
		for (int i = 0; i < m; i++) {
			cin >> T[m][i];
			T[m][i] = log(T[m][i]);
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				cin >> T[i][j];
				T[i][j] = log(T[i][j]);
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				cin >> M[i][j];
				M[i][j] = log(M[i][j]);
			}
		}
		while (queries--) {
			cin >> n;
			assert(1 <= n && n <= 100);
			for (int i = 0; i < n; i++) {
				string recognizedWord;
				cin >> recognizedWord;
				for (int j = 0; j < m; ++j)
					if (corpus[j] == recognizedWord) {
						R[i] = j;
						break;
					}
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m + 1; j++) {
					cache[i][j] = 1;
				}
			}

			recognize(0, m);
			string original = reconstruct(0, m);
			printf("%s\n", original.substr(0, original.size() - 1).c_str());
		}
	}
};
