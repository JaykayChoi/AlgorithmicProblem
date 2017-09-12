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

//https://algospot.com/judge/problem/read/QUANTIZE

//Quantization(����ȭ) ������, �� ���� ������ ���� ������ ���� ������ ���� ����� �ٻ��� ǥ�������ν� �ڷḦ �ս� �����ϴ� ������ ���Ѵ�.���� ��� 16��Ʈ JPG ������ 4�÷� GIF ���Ϸ� ��ȯ�ϴ� ���� RGB �� ������ ������ 4�÷� ���� �ϳ��� ����ȭ�ϴ� ���̰�, Ű�� 161, 164, 170, 178 �� �л� ���� '160�� ��, 170�� ��' �̶�� ����� ǥ���ϴ� �� ���� ����ȭ��� �� �� �ִ�.
//
//1000 ������ �ڿ������ ������ ������ �ִ� S���� �� ������ ����ϵ��� ����ȭ�ϰ� �ʹ�.�� �� ����ȭ�� ���ڴ� ���� ������ ���� ������ ���� �ִ�.����ȭ�� �ϴ� ����� ���� ������ �ִ�.���� 1 2 3 4 5 6 7 8 9 10 �� 2���� ���ڸ��� �Ἥ ǥ���Ϸ���, 3 3 3 3 3 7 7 7 7 7 �� ���� �� ���� �ְ�, 1 1 1 1 1 10 10 10 10 10 ���� �� ���� �ִ�.�츮�� �� ��, �� ���ں� ���� ������ ���� �ּ�ȭ�ϴ� ����ȭ ����� �˰� �ʹ�.
//
//���� ���, ���� 1 2 3 4 5 �� 1 1 3 3 3 ���� ����ȭ�ϸ� ���� ������ ���� 0 + 1 + 0 + 1 + 4 = 6 �� �ǰ�, 2 2 2 4 4 �� ����ȭ�ϸ� ���� ������ ���� 1 + 0 + 1 + 0 + 1 = 3 �� �ȴ�.
//
//������ S �� �־��� ��, ������ ���� ������ ���� �ּҰ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(1 <= C <= 50) �� �־�����.�� �׽�Ʈ ���̽��� ù �ٿ��� ������ ���� N(1 <= N <= 100), ����� ������ �� S(1 <= S <= 10) �� �־�����.�� ���� �ٿ� N���� ������ ������ ���ڵ��� �־�����.������ ��� ���� 1000 ������ �ڿ����̴�.
//
//���
//
//�� �׽�Ʈ ���̽�����, �־��� ������ �ִ� S ���� ���� ����ȭ�� �� ���� ������ ���� �ּҰ��� ����Ѵ�.
//
//���� �Է�
//
//2
//10 3
//3 3 3 1 2  3 2 2 2 1
//9 3
//1 744 755 4 897 902 890 6 777
//
//���� ���
//
//0
//651

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

class Quantization_8_9
{
public:
	void Solve()
	{
		Input();
	}

private:
	int parts = 0;
	void Input()
	{
		string filePath = "Quantization_8_9_Input.txt";
		vector<string> vInputLines = Utils::GetLine_InputFile(filePath);

		int problems = stoi(vInputLines[0]);

		for (int i = 0; i < problems; i++)
		{
			string delimiter = " ";
			vector<int> line1 = Utils::SplitStringToInt(vInputLines[i * 2 + 1], delimiter);
			n = line1[0];
			parts = line1[1];
			vector<int> numbersList = Utils::SplitStringToInt(vInputLines[i * 2 + 2], delimiter);

			REP(i, n)
			{
				A[i] = numbersList[i];
			}
			
			
			//����
			precalc();
			memset(cache, -1, sizeof(cache)); 
			cout << quantize(0, parts) << endl;
			
		}
	}



	//����
	// A[]: ����ȭ�ؾ� �� ����, ������ ����
	// pSum[]: A[] �� �κ����� �����Ѵ�. pSum[i] �� A[0] .. A[i] �� ��
	// pSqSum[]: A[] ������ �κ����� �����Ѵ�. pSqSum[i] �� A[0]^2 .. A[i]^2 �� ��
	int n;
	int A[101], pSum[101], pSqSum[101];

	// A �� �����ϰ� �� �κ����� ����Ѵ�
	void precalc() {
		sort(A, A + n);
		pSum[0] = A[0];
		pSqSum[0] = A[0] * A[0];
		for (int i = 1; i < n; ++i) {
			pSum[i] = pSum[i - 1] + A[i];
			pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
		}
	}

	// A[lo] .. A[hi] ������ �ϳ��� ���ڷ� ǥ���� �� �ּ� ���� ���� ����Ѵ�
	int minError(int lo, int hi) {
		// �κ����� �̿��� A[lo] ~ A[hi] ������ ���� ���Ѵ�
		int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
		int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);

		// ����� �ݿø��� ������ �� ������ ǥ���Ѵ�
		int m = int(0.5 + (double)sum / (hi - lo + 1));

		// sum (A[i] - m)^2 �� ������ ����� �κ� ������ ǥ��
		int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
		assert(ret >= 0);
		return ret;
	}

	int cache[101][11];

	int quantize(int from, int parts) {
		// ���� ���: ��� ���ڸ� �� ����ȭ���� ��
		if (from == n) return 0;
		// ���� ���: ���ڴ� ���� ���Ҵµ� �� ���� �� ���� ��
		if (parts == 0) return 987654321;

		int& ret = cache[from][parts];
		if (ret != -1) return ret;
		ret = 987654321;
		// ������ ���̸� ��ȭ���� ���� �ּҰ��� ã�´�
		for (int partSize = 1; from + partSize <= n; ++partSize)
			ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
		return ret;
	}
};
