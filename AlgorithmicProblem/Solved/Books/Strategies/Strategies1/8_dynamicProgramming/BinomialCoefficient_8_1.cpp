
//https://en.wikipedia.org/wiki/Binomial_coefficient

class BinomialCoefficient_8_1
{
public:
	//-1 으로 초기화 해두어야 됨
	int cache[30][30];

	int bino(int n, int k)
	{
		//n=r(모든 원소를 다 고르는 경우) 혹은 r=0(고를 원소가 없는 경우)
		if (n == k || k == 0)
			return 1;

		return bino(n - 1, k - 1) + bino(n - 1, k);
	}

	//memoization
	int bino2(int n, int k)
	{
		///n=r(모든 원소를 다 고르는 경우) 혹은 r=0(고를 원소가 없는 경우)
		if (n == k || k == 0)
			return 1;

		if (cache[n][k] != -1)
			return cache[n][k];

		return cache[n][k]  = bino2(n - 1, k - 1) + bino2(n - 1, k);
	}
};
