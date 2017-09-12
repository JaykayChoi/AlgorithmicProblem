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

const int MAX_N = 1000000;

//���μ�����
class PrimeFactorization_14_2
{
public:

private:
	int n;
	bool isPrime[MAX_N];

	// ���� �ܼ��� ������ �����佺�׳׽��� ü�� ���� (�Ҽ� �Ǻ�)
	// ������ �� isPrime[i] = i �� �Ҽ��ΰ�?
	void eratosthenes() {
		memset(isPrime, 1, sizeof(isPrime));

		// 1 �� �׻� ���� ó��!
		isPrime[0] = isPrime[1] = false;

		int sqrtn = int(sqrt(n));
		for (int i = 2; i <= sqrtn; ++i)
			// �� ���� ���� �������� �ʾҴٸ�
			if (isPrime[i])
				// i �� ��� j �鿡 ���� isPrime[j] = false �� �д�.
				// i*i �̸��� ����� �̹� ���������Ƿ� �Ű澲�� �ʴ´�.
				for (int j = i*i; j <= n; j += i)
					isPrime[j] = false;
	}

	// minFactor[i] = i �� ���� ���� ���μ� (i �� �Ҽ��� ��� �ڱ� �ڽ�)
	int minFactor[MAX_N];

	// �����佺�׳׽��� ü�� �����ϸ鼭 ���μ����ظ� ���� ������ �����Ѵ�
	void eratosthenes2() {
		// 1 �� �׻� ���� ó��
		minFactor[0] = minFactor[1] = -1;

		// ��� ���ڸ� ó������ �Ҽ��� ǥ���� �д�
		for (int i = 2; i <= n; ++i)
			minFactor[i] = i;

		// �����佺�׳׽��� ü�� �����Ѵ�
		int sqrtn = int(sqrt(n));
		for (int i = 2; i <= sqrtn; ++i) {
			if (minFactor[i] == i) {
				for (int j = i*i; j <= n; j += i)
					// ���� ����� �� �� ���� ������ ��� i �� �� �д�
					if (minFactor[j] == j)
						minFactor[j] = i;
			}
		}
	}

	// 2 �̻��� �ڿ��� n �� ���μ������� ����� ��ȯ�Ѵ�.
	vector<int> factor(int n) {
		vector<int> ret;
		// n �� 1 �� �� ������ ���� ���� ���μ��� ������ ���� �ݺ��Ѵ�
		while (n > 1) {
			ret.push_back(minFactor[n]);
			n /= minFactor[n];
		}
		return ret;
	}

	// �־��� ���� n �� ���μ������ϴ� ������ �˰���
	vector<int> factorSimple(int n) {
		vector<int> ret;
		int sqrtn = int(sqrt(n));
		for (int div = 2; div <= sqrtn; ++div)
			while (n % div == 0) {
				n /= div;
				ret.push_back(div);
			}
		if (n > 1) ret.push_back(n);
		return ret;
	}

	int CInput() {
		n = 1000;

		eratosthenes();
		for (int i = 0; i < 100; i++)
			if (isPrime[i])
				printf("%d ", i);
		printf("\n");

		eratosthenes2();
		for (int i = 1; i < n; ++i) {
			vector<int> a = factor(i);
			vector<int> b = factorSimple(i);
			if (a != b) {
				printf("Factoring %d:\n", i);
				printf("sieve:"); for (int j = 0; j < a.size(); j++) printf(" %d", a[j]); printf("\n");
				printf("naive:"); for (int j = 0; j < b.size(); j++) printf(" %d", b[j]); printf("\n");
				return 0;
			}
		}
		printf("all good.\n");
	}

};