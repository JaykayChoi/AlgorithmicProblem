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

//https://algospot.com/judge/problem/read/PASS486

const int TM = 1000 * 1000 * 10;

class Pass486_14_3
{
public:

private:
	// minFactor[i] = i �� ���� ���� ���μ� (i �� �Ҽ��� ��� �ڱ� �ڽ�)
	int minFactor[TM + 1];

	// �����佺�׳׽��� ü�� �����ϸ鼭 ���μ����ظ� ���� ������ �����Ѵ�
	void eratosthenes2() {
		// 1 �� �׻� ���� ó��
		minFactor[0] = minFactor[1] = -1;

		// ��� ���ڸ� ó������ �Ҽ��� ǥ���� �д�
		for (int i = 2; i <= TM; ++i)
			minFactor[i] = i;

		// �����佺�׳׽��� ü�� �����Ѵ�
		for (int i = 2; i*i <= TM; ++i) {
			if (minFactor[i] == i) {
				minFactor[i] = i;
				for (int j = i*i; j <= TM; j += i)
					// ���� ����� �� �� ���� ������ ��� i �� �� �д�
					if (minFactor[j] == j)
						minFactor[j] = i;
			}
		}
	}

	// minFactorPower[i] = i �� ���μ����ؿ��� minFactor[i] �� �� ���� ���ԵǾ� �ִ°�?
	int minFactorPower[TM + 1];

	// factors[i] = i �� ���� ����� ��
	int factors[TM + 1];

	void getFactorsSmart() {
		factors[1] = 1;
		for (int n = 2; n <= TM; ++n) {
			// �Ҽ��� ��� ����� �ΰ��ۿ� ����
			if (minFactor[n] == n) {
				minFactorPower[n] = 1;
				factors[n] = 2;
			}
			// �Ҽ��� �ƴ� ���, ���� ���� ���μ��� ���� �� (m) ��
			// ����� ���� ������ n �� ����� ���� ã�´�
			else {
				int p = minFactor[n];
				int m = n / p;
				// m �� p �� ���̻� ���������� �ʴ� ���
				if (p != minFactor[m])
					minFactorPower[n] = 1;
				else
					minFactorPower[n] = minFactorPower[m] + 1;
				int a = minFactorPower[n];
				factors[n] = (factors[m] / a) * (a + 1);
			}
		}
	}

	void getFactorsBrute() {
		memset(factors, 0, sizeof(factors));
		for (int div = 1; div <= TM; ++div)
			for (int multiple = div; multiple <= TM; multiple += div)
				factors[multiple] += 1;
	}

	int CInput(int argc, char* argv[]) {
		if (argc > 1 && argv[1][0] == 'n')
			getFactorsBrute();
		else {
			eratosthenes2();
			getFactorsSmart();
		}
		//for(int i = 2; i <= 20; ++i) printf("factors[%d] = %d\n", i, factors[i]);
		int cases;
		cin >> cases;
		for (int i = 0; i < cases; i++) {
			int n, lo, hi, ret = 0;
			cin >> n >> lo >> hi;
			for (int j = lo; j < hi + 1; j++)
				if (factors[j] == n)
					++ret;
			cout << ret << endl;
		}

	}
};