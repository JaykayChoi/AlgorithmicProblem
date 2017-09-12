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
	
	// amount원을 연 이율 rates퍼센트로 duration월간 한달에 monthlyPayment 로 
	// 남았을 때 대출 잔금은?
	double balance(double amount, int duration, double rates, double monthlyPayment) {
		double balance = amount;
		for (int i = 0; i < duration; ++i) {
			// 이자가 붙는다
			balance *= (1.0 + (rates / 12.0) / 100.0);
			// 상환액을 잔금에서 제한다
			balance -= monthlyPayment;
		}
		return balance;
	}

	// amount원을 연 이율 rates퍼센트로 duration월간 갚으려면 한달에
	// 얼마씩 갚아야 하나?
	double payment(double amount, int duration, double rates) {
		// 불변 조건: 
		// 1. lo원씩 갚으면 duration개월 안에 갚을 수 없다
		// 2. hi원씩 갚으면 duration개월 안에 갚을 수 있다
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