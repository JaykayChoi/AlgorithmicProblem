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

//https://algospot.com/judge/problem/read/LOAN

class Loan_13_2
{
public:

private:
	
	// amount���� �� ���� rates�ۼ�Ʈ�� duration���� �Ѵ޿� monthlyPayment �� 
	// ������ �� ���� �ܱ���?
	double balance(double amount, int duration, double rates, double monthlyPayment) {
		double balance = amount;
		for (int i = 0; i < duration; ++i) {
			// ���ڰ� �ٴ´�
			balance *= (1.0 + (rates / 12.0) / 100.0);
			// ��ȯ���� �ܱݿ��� ���Ѵ�
			balance -= monthlyPayment;
		}
		return balance;
	}

	// amount���� �� ���� rates�ۼ�Ʈ�� duration���� �������� �Ѵ޿�
	// �󸶾� ���ƾ� �ϳ�?
	double payment(double amount, int duration, double rates) {
		// �Һ� ����: 
		// 1. lo���� ������ duration���� �ȿ� ���� �� ����
		// 2. hi���� ������ duration���� �ȿ� ���� �� �ִ�
		double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100.0);
		for (int iter = 0; iter < 100; ++iter) {
			double mid = (lo + hi) / 2.0;
			if (balance(amount, duration, rates, mid) <= 0)
				hi = mid;
			else
				lo = mid;
		}
		return hi;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			double N, P;
			int M;
			cin >> N >> M >> P;
			cout << payment(N, M, P) << endl;
		}
	}
	
};