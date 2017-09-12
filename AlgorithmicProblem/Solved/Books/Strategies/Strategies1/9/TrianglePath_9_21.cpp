#include "Utils.h"
using namespace std;
using namespace Utils;

//삼각형 위의 최대 경로 문제를 해결하는 반복적 동적 계획법 알고리즘

class TrianglePath_9_21
{
public:

private:
	int n, triangle[100][100];

	int C[100][100];
	int iterative() {
		// 기저 사례를 계산한다
		for (int x = 0; x < n; ++x)
			C[n - 1][x] = triangle[n - 1][x];
		// 다른 부분을 계산한다
		for (int y = n - 2; y >= 0; --y)
			for (int x = 0; x < y + 1; ++x)
				C[y][x] = max(C[y + 1][x], C[y + 1][x + 1]) + triangle[y][x];
		return C[0][0];
	}

	int C2[2][5000];
	//슬라이딩 윈도를 이용한 삼각형 위의 최대 경로 알고리즘. 공간 복잡도 줄이기.
	int iterative2() {
		// 기저 사례를 계산한다
		for (int x = 0; x < n; ++x)
			C2[(n - 1) % 2][x] = triangle[n - 1][x];
		// 다른 부분을 계산한다
		for (int y = n - 2; y >= 0; --y)
			for (int x = 0; x < y + 1; ++x)
				C2[y % 2][x] = max(C2[(y + 1) % 2][x], C2[(y + 1) % 2][x + 1]) + triangle[y][x];
		return C2[0][0];

	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc)
		{

			cin >> n;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i + 1; j++) {
					cin >> triangle[i][j];
				}
			}

			 cout << iterative() << endl;
			 cout << iterative2() << endl;

		}
	}
};