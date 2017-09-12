#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class RecursiveFunction_6_2
{
public:
	void Solve()
	{
		comb(5, 2);
		cout << endl;
		vector<int> v;
		pick(5, v, 2, 2);
		cout << endl;
		comb(5, 2, 0, 0);
		cout << endl;
		unsigned char buf[100];
		comb(5, 2, buf);
	}
private:
	//1���� n������ ���� ��ȯ.
	int sum(int n)
	{
		int ret = 0;
		for (int i = 0; i <= n; i++)
			ret += i;
		
		return ret;
	}

	int recursiveSum(int n)
	{
		if (n == 1)
			return 1;

		return n + recursiveSum(n - 1);
	}

	////////////////////////////
	//0���� ���ʴ�� ��ȣ �Ű��� n ���� ���� �� �� ���� ���� ��� ��츦 ���.
	void ploblem(int n)
	{
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = j + 1; k < n; k++)
					for (int l = k + 1; l < n; l++)
						cout << i << " " << j << " " << k << " " << l << endl;
	}

	//n ��ü ������ ��
	//picked ���ݱ��� �� ���ҵ��� ��ȣ
	//toPick �� �� ������ �� �� �� ������ toPick ���� ���Ҹ� ���� ��� ��� ���.
	void pick(int n, vector<int>& picked, int toPick, int m)
	{
		//cout << num << " / tPic : " << toPick << " / picked size : " << picked.size() << endl;
		//�� �� ���Ұ� ���� �� �� ���ҵ��� ���.
		if (toPick == 0)
		{
			for (int i = 0; i < picked.size(); i++)
			{
				cout << picked[i];
				if (i % m == (m-1))
					cout << endl;
				else
					cout << " ";
			}
		}
		//�� �� �ִ� ���� ���� ��ȣ�� ���.
		int smallest = picked.empty() ? 0 : picked.back() + 1;

		//�� �ܰ迡�� ���� �ϳ��� ����.
		for (int next = smallest; next < n; next++)
		{
			picked.push_back(next);
			pick(n, picked, toPick - 1, m);
			picked.pop_back();
		}
	}

	//https://rosettacode.org/wiki/Combinations
	//0���� ���ʴ�� ��ȣ �Ű��� n ���� ���� �� k���� ���� ��� ��츦 ���.
	void comb(int N, int K)
	{
		string bitmask(K, 1); // K leading 1's
		bitmask.resize(N, 0); // N-K trailing 0's

							  // print integers and permute bitmask
		do 
		{
			for (int i = 0; i < N; ++i) // [0..N-1] integers
			{
				if (bitmask[i]) std::cout << " " << i;
			}

			cout << endl;
		} 
		while (prev_permutation(bitmask.begin(), bitmask.end()));
	}

	void comb(int pool, int need, unsigned long chosen, int at)
	{
		if (pool < need + at) return; /* not enough bits left */

		if (!need) {
			/* got all we needed; print the thing.  if other actions are
			* desired, we could have passed in a callback function. */
			for (at = 0; at < pool; at++)
				if (chosen & (1 << at)) printf("%d ", at);
			printf("\n");
			return;
		}
		/* if we choose the current item, "or" (|) the bit to mark it so. */
		comb(pool, need - 1, chosen | (1 << at), at + 1);
		comb(pool, need, chosen, at + 1);  /* or don't choose it, go to next */
	}

	void comb(int m, int n, unsigned char *c)
	{
		int i;
		for (i = 0; i < n; i++)
			c[i] = n - i;

		while (true)
		{
			for (i = n; i--;)
				printf("%d%c", c[i], i ? ' ' : '\n');

			/* this check is not strictly necessary, but if m is not close to n,
			it makes the whole thing quite a bit faster */
			if (c[i]++ < m)
				continue;

			for (i = 0; c[i] >= m - i;)
				if (++i >= n) return;

			for (c[i]++; i; i--)
				c[i - 1] = c[i] + 1;
		}

	}
};