#include "Utils.h"
using namespace std;
using namespace Utils;
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

const int MAX_N = 256 * 1024 * 1024;


class BitMaskEratosthenes_16_3
{
public:

private:
#pragma region ��Ʈ����ũ�� ����ϴ� 14-2�����佺�׳׽��� ü�� ����
	int n;
	unsigned char sieve[(MAX_N + 7) / 8];

	inline bool isPrime(int k) {
		return sieve[k >> 3] & (1 << (k & 7));
	}

	inline void setComposite(int k) 
	{
		//������ ���������� 3��Ʈ ����Ʈ�ϴ� ���� 8�� ������ �Ͱ� ����, 7�� and �����ϴ� ���� 8�� ���� �������� ���ϴ� �Ͱ� ����.
		sieve[k >> 3] &= ~(1 << (k & 7));	
	}

	// ��Ʈ����ũ�� ����ϴ� 14-2�����佺�׳׽��� ü�� ����
	// �� �Լ��� �����ϰ� �� ��, isPrime() �� �̿��� �� ���� �Ҽ����� �� �� �ִ�.
	void eratosthenes() {
		memset(sieve, 255, sizeof(sieve));

		setComposite(0);
		setComposite(1);

		int sqrtn = int(sqrt(n));
		for (int i = 2; i <= sqrtn; ++i)
			// �� ���� ���� �������� �ʾҴٸ�
			if (isPrime(i))
				// i �� ��� j �鿡 ���� isPrime[j] = false �� �д�.
				// i*i �̸��� ����� �̹� ���������Ƿ� �Ű澲�� �ʴ´�.
				for (int j = i*i; j <= n; j += i)
					setComposite(j);
	}

	int CInput() {
		n = MAX_N;
		eratosthenes();
		for (int i = 0; i < 100; i++)
			if (isPrime(i))
				printf("%d ", i);
		printf("\n");
	}
#pragma endregion



#pragma region 64��Ʈ ������ 4��Ʈ ���� 16���� �迭�� ����ϱ� ���� �Լ���
	typedef unsigned long long uint64;

	// idx ��° ���ڸ� val �� �ٲ۴�. val �� [0,15] �� ����
	uint64 setArray(uint64 array, int idx, uint64 val) {
		return (array & ~(15ULL << (4 * idx))) | (val << (4 * idx));
	}

	// idx ��° ���ڸ� ��ȯ�Ѵ�. ��ȯ���� [0,15] �� ����
	int getArray(uint64 array, int idx) {
		return (array >> (4 * idx)) & 15;
	}

#pragma endregion
};