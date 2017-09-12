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
#pragma region 비트마스크를 사용하는 14-2에라토스테네스의 체의 구현
	int n;
	unsigned char sieve[(MAX_N + 7) / 8];

	inline bool isPrime(int k) {
		return sieve[k >> 3] & (1 << (k & 7));
	}

	inline void setComposite(int k) 
	{
		//정수를 오른쪽으로 3비트 시프트하는 것은 8로 나누는 것과 같고, 7과 and 연산하는 것은 8로 나눈 나머지를 구하는 것과 같다.
		sieve[k >> 3] &= ~(1 << (k & 7));	
	}

	// 비트마스크를 사용하는 14-2에라토스테네스의 체의 구현
	// 이 함수를 수행하고 난 뒤, isPrime() 을 이용해 각 수가 소수인지 알 수 있다.
	void eratosthenes() {
		memset(sieve, 255, sizeof(sieve));

		setComposite(0);
		setComposite(1);

		int sqrtn = int(sqrt(n));
		for (int i = 2; i <= sqrtn; ++i)
			// 이 수가 아직 지워지지 않았다면
			if (isPrime(i))
				// i 의 배수 j 들에 대해 isPrime[j] = false 로 둔다.
				// i*i 미만의 배수는 이미 지워졌으므로 신경쓰지 않는다.
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



#pragma region 64비트 정수를 4비트 정수 16개의 배열로 사용하기 위한 함수들
	typedef unsigned long long uint64;

	// idx 번째 숫자를 val 로 바꾼다. val 은 [0,15] 의 정수
	uint64 setArray(uint64 array, int idx, uint64 val) {
		return (array & ~(15ULL << (4 * idx))) | (val << (4 * idx));
	}

	// idx 번째 숫자를 반환한다. 반환값은 [0,15] 의 정수
	int getArray(uint64 array, int idx) {
		return (array >> (4 * idx)) & 15;
	}

#pragma endregion
};