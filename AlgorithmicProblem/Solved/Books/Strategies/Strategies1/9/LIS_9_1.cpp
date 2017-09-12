#include<cassert>
#include<vector>
#include<iostream>
#include<cstring>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include "Utils.h"
#include <ctime>
using namespace std;

//����
//
//� ���� �������� 0�� �̻��� ���ڸ� ����� �� ������ �κ� ����(subsequence) �� ���� �� �ִ�.���� ��� 10 7 4 9 �� �κ� �������� 7 4 9, 10 4, 10 9 ���� �ִ�.��, 10 4 7 �� ���� ������ ������ �ٸ��Ƿ� 10 7 4 9 �� �κ� ������ �ƴϴ�.
//
//� �κ� ������ �������� �� �� �κ� ������ ���� �κ� ����(increasing subsequence) ��� �Ѵ�.�־��� ������ ���� �κ� ���� �� ���� �� ���� ���̸� ����ϴ� ���α׷��� �ۼ��϶�.
//
//� ������ �� ���� ������ ������ Ŭ ��, �� ������ ������ �Ѵٰ� �Ѵ�.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(<= 50) �� �־�����.�� �׽�Ʈ ���̽��� ù �ٿ��� ������ ���Ե� ������ �� N(<= 500) �� �־�����.�� ���� �ٿ� ������ N���� ������ �־�����.�� ������ 1 �̻� 100, 000 ������ �ڿ����̴�.
//
//���
//
//�� �׽�Ʈ���̽����� �� �پ�, �־��� ������ ���� �� ���� �κ� ������ ���̸� ����Ѵ�.
//
//���� �Է�
//
//3
//4
//1 2 3 4
//8
//5 4 3 2 1 6 7 8
//8
//5 6 7 8 1 2 3 4
//���� ���
//
//4
//4
//4

class LIS_9_1
{
public:
	void Solve()
	{
		Input();
	}

private:
	int numbers;
	vector<int> lineNumbers;
	int cache[100];
	int choices[100];
	void Input()
	{
		memset(cache, -1, sizeof(cache));

		string filePath = "LIS_8_4_Input.txt";
		vector<string> vInputLines = Utils::GetLine_InputFile(filePath);

		numbers = stoi(vInputLines[0]);

		string delimiter = " ";
		lineNumbers = Utils::SplitStringToInt(vInputLines[1], delimiter);

		//cout << lis(lineNumbers) << endl;
		//cout << lis2(0) << endl;
		//cout << lis3(-1) - 1 << endl;
		cout << lis4(-1) - 1 << endl;

		vector<int> seq;
		reconstruct(-1, seq);
		for (int i = 0; i < seq.size(); ++i)
			cout << seq[i] << " ";
		cout << endl;
	}


	// S[start] ���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�
	int lis4(int start) {
		int& ret = cache[start + 1];
		if (ret != -1) return ret;
		// �׻� S[start] �� �ֱ� ������ ���̴� ���� 1
		ret = 1;
		int bestNext = -1;
		for (int next = start + 1; next < numbers; ++next)
		{
			if (start == -1 || lineNumbers[start] < lineNumbers[next])
			{
				int cand = lis4(next) + 1;
				if (cand > ret) 
				{
					ret = cand;
					bestNext = next;
				}
			}
		}
		choices[start + 1] = bestNext;
		return ret;
	}

	// S[start] ���� �����ϴ� LIS �� seq �� �����Ѵ�
	void reconstruct(int start, vector<int>& seq) 
	{
		if (start != -1) 
			seq.push_back(lineNumbers[start]);

		int next = choices[start + 1];

		if (next != -1) 
			reconstruct(next, seq);
	}
};