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

class Primes_14_2
{
public:

private:


	//http://blog.naver.com/inocent_xx/80181261544

	// 주어진 자연수 n 이 소수인지 확인한다
	bool isPrime(int n) {
		// 예외 처리: 1 과 2 는 예외로 처리한다
		if (n == 1) return false;
		if (n == 2) return true;
		// 2 를 제외한 모든 짝수는 소수가 아니다
		if (n % 2 == 0) return false;
		// 2 를 제외했으니 3 이상의 모든 홀수로 나누어보자
		int sqrtn = int(sqrt(n));
		for (int div = 3; div <= sqrtn; div += 2)
			if (n % div == 0)
				return false;
		return true;
	}

	int CInput() {
		cout << isPrime(2147483647) << endl;
		cout << isPrime(2147483647) << endl;
		for (int i = 1; i < 100; i++)
			if (isPrime(i))
				printf("%d ", i);
		printf("\n");
	}
};