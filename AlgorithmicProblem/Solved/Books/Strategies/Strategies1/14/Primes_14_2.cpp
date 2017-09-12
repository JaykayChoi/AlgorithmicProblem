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

	// �־��� �ڿ��� n �� �Ҽ����� Ȯ���Ѵ�
	bool isPrime(int n) {
		// ���� ó��: 1 �� 2 �� ���ܷ� ó���Ѵ�
		if (n == 1) return false;
		if (n == 2) return true;
		// 2 �� ������ ��� ¦���� �Ҽ��� �ƴϴ�
		if (n % 2 == 0) return false;
		// 2 �� ���������� 3 �̻��� ��� Ȧ���� �������
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