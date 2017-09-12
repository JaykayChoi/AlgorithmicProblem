
//https://en.wikipedia.org/wiki/Binomial_coefficient

class BinomialCoefficient_8_1
{
public:
	//-1 ���� �ʱ�ȭ �صξ�� ��
	int cache[30][30];

	int bino(int n, int k)
	{
		//n=r(��� ���Ҹ� �� ���� ���) Ȥ�� r=0(�� ���Ұ� ���� ���)
		if (n == k || k == 0)
			return 1;

		return bino(n - 1, k - 1) + bino(n - 1, k);
	}

	//memoization
	int bino2(int n, int k)
	{
		///n=r(��� ���Ҹ� �� ���� ���) Ȥ�� r=0(�� ���Ұ� ���� ���)
		if (n == k || k == 0)
			return 1;

		if (cache[n][k] != -1)
			return cache[n][k];

		return cache[n][k]  = bino2(n - 1, k - 1) + bino2(n - 1, k);
	}
};
