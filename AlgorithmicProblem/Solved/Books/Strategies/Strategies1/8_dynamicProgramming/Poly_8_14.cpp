#include "Utils.h"
using namespace std;

//https://algospot.com/judge/problem/read/POLY

const int MOD = 10 * 1000 * 1000;

class Poly_8_14
{
public:

private:
	int cache[101][101];

	// n���� ���簢������ �̷������, �� �� �����ٿ� first ����
	// ���簢���� �����ϴ� �������̳��� ���� ��ȯ�Ѵ�
	int poly(int n, int first)
	{
		// ���� ���: n == first
		if (n == first) return 1;
		// �޸������̼�
		int& ret = cache[n][first];
		if (ret != -1) return ret;

		ret = 0;
		for (int second = 1; second <= n - first; ++second) {
			int add = second + first - 1;
			add *= poly(n - first, second);
			add %= MOD;
			ret += add;
			ret %= MOD;
		}
		return ret;
	}

	void CInput()
	{
		memset(cache, -1, sizeof(cache));

		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc)
		{
			int n;
			cin >> n;
			int ret = 0;
			for (int i = 0; i < n; i++)
				(ret += poly(n, i + 1)) %= MOD;
			cout << ret << endl;
		}
	}
};