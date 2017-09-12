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

	
#pragma region ��� �� ��ȣ�� ����� ���� Ž�� �˰���.
	//n �� �ʿ��� - �� ����
	//m �� �ʿ��� o �� ����
	//s ���ݱ��� ���� ��ȣ
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

#pragma region k-1 �� �ǳʶٰ� ù ��° ��ȣ�� ����ϴ� �˰���
	int skip;
	
	//skip ���� �ǳʶٰ� ����Ѵ�
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


#pragma region k-1 �� �ǳʶٰ� ù ��° ��ȣ�� ����ϴ� �˰���2
	//k �� �ִ밪 + 100. �����÷θ� ���� ���� �̺��� ū ���� ������ �ʴ´�.
	const int M = 1000000000 + 100;
	int bino[201][201];

	//�ʿ��� ���װ���� �̸� ����� �д�.
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
	// n���� -, m���� o �� ������ ��ȣ �� k��° ��ȣ�� ��ȯ�Ѵ� 
	// (k �� 0 ���� ����)
	string getKthSignal(int n, int m, int k) {
		if (n == 0 && m == 0) return "";
		// - �� �����ϴ� ��ȣ�� ��
		int dashes = bino[n + m - 1][n - 1];
		if (n > 0 && k < dashes)
			return "-" + getKthSignal(n - 1, m, k);
		return "o" + getKthSignal(n, m - 1, k - dashes);
	}
#pragma endregion
};