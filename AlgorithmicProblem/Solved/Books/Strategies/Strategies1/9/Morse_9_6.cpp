#include "Utils.h"
using namespace std;
using namespace Utils;

//https://algospot.com/judge/problem/read/MORSE

class Morse_9_6
{
public:
	void Solve()
	{
		Input();
	}

private:
	void Input()
	{
		string filePath = "Morse_9_6_Input.txt";
		queue<string> vInputLines = GetLine_InputFileAsQueue(filePath);

		int numPloblems = stoi(Dequeue(vInputLines));

		for (int i = 0; i < numPloblems; i++)
		{
			vector<int> numbers = SplitStringToInt(Dequeue(vInputLines));
			//generate(numbers[0], numbers[1], string(""));

			skip = numbers[2] - 1;
			generate2(numbers[0], numbers[1], string(""));
		}
	}

	
#pragma region 모든 모스 신호를 만드는 완전 탐색 알고리즘.
	//n 더 필요한 - 의 개수
	//m 더 필요한 o 의 개수
	//s 지금까지 만든 신호
	void generate(int n, int m, string s)
	{
		if (n == 0 && m == 0)
		{
			cout << s << endl;
			return;
		}

		if (n > 0)
			generate(n - 1, m, s + "-");

		if (m > 0)
			generate(n, m - 1, s + "o");
	}
#pragma endregion

#pragma region k-1 개 건너뛰고 첫 번째 신호를 출력하는 알고리즘
	int skip;
	
	//skip 개를 건너뛰고 출력한다
	void generate2(int n, int m, string s)
	{
		if (skip < 0)
			return;

		if (n == 0 && m == 0)
		{
			if (skip == 0)
				cout << s << endl;

			--skip;
			return;
		}

		if (n > 0)
			generate2(n - 1, m, s + "-");

		if (m > 0)
			generate2(n, m - 1, s + "o");
	}
#pragma endregion


#pragma region k-1 개 건너뛰고 첫 번째 신호를 출력하는 알고리즘2
	//k 의 최대값 + 100. 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다.
	const int M = 1000000000 + 100;
	int bino[201][201];

	//필요한 이항계수를 미리 계산해 둔다.
	void calcBino()
	{
		memset(bino, 0, sizeof(bino));
		for (int i = 0; i <= 200; i++)
		{
			bino[i][0] = bino[i][i] = 1;
			for (int j = 1; j < i; j++)
			{
				bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
			}
		}
	}


	void generate3(int n, int m, string s)
	{
		if (skip < 0)
			return;

		if (n == 0 && m == 0)
		{
			if (skip == 0)
				cout << s << endl;

			--skip;
			return;
		}

		if (bino[n + m][n] <= skip)
		{
			skip -= bino[n + m][n];
			return;
		}

		if (n > 0)
			generate3(n - 1, m, s + "-");

		if (m > 0)
			generate3(n, m - 1, s + "o");
	}
#pragma endregion

#pragma region smartest method
	// n개의 -, m개의 o 로 구성된 신호 중 k번째 신호를 반환한다 
	// (k 는 0 부터 시작)
	string getKthSignal(int n, int m, int k) {
		if (n == 0 && m == 0) return "";
		// - 로 시작하는 신호의 수
		int dashes = bino[n + m - 1][n - 1];
		if (n > 0 && k < dashes)
			return "-" + getKthSignal(n - 1, m, k);
		return "o" + getKthSignal(n, m - 1, k - dashes);
	}
#pragma endregion
};