#include "Utils.h"
using namespace std;


class GetMaxFrequency
{
public:
	void Solve()
	{
		Input();
	}
private:
	void Input()
	{
		string filePath = "GetMaxFrequency_Input.txt";
		vector<string> vInputLines = Utils::GetLine_InputFile(filePath);

		string delimiter = " ";
		vector<int> numbers = Utils::SplitStringToInt(vInputLines[0], delimiter);

		cout << majority(numbers) << endl;
	}

	//A�� �� ���Ұ� 0���� 100 ������ ���� ��� ���� ���� �����ϴ� ���ڸ� ��ȯ.
	int majority(const vector<int>& A)
	{
		int N = A.size();
		vector<int> count(101, 0);	// 101 ints with value 0
		for (int i = 0; i < N; i++)
		{
			count[A[i]]++;
		}

		int majority = 0;
		for (int i = 1; i <= 100; i++)
		{
			if (count[i] > count[majority])
				majority = i;
		}
		return majority;
	}
};