#include "Utils.h"
using namespace std;

class BitMask_16_2
{
public:


private:
	int _fullPizza = (1 << 20) - 1;
	int _toppings = 0;

	void AddTopping(int p)
	{
		_toppings |= (1 << p);
	}

	void RemoveTopping(int p)
	{
		_toppings &= ~(1 << p);
	}

	void ToogleTopping(int p)
	{
		_toppings ^= (1 << p);
	}

	bool CheckTopping(int p)
	{
		bool ret = false;
		if (_toppings & (1 << p))
		{
			ret = true;
			cout << p << " is in" << endl;
		}

		return ret;
	}

	int BitCount(int x)
	{
		if (x == 0)
			return 0;

		return x % 2 + BitCount(x / 2);
	}

	int FirstTopping()
	{
		return (_toppings & -_toppings);
	}

	void RemoveFirstTopping()
	{
		_toppings &= (_toppings - 1);
	}

	int getHammingDistance1(int a, int b)
	{
		int temp = a ^ b;
		return BitCount(temp);
	}

	int getHammingDistance2(int a, int b)
	{
		int ret = 0;
		while (a > 0 || b > 0)
		{
			if (a % 2 != b % 2)
				ret++;
			a /= 2;
			b /= 2;
		}
		return ret;
	}

};
