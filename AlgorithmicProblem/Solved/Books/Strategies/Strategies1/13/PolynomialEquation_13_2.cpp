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

//�ܺ��� ���׹������� ��ġ�� �ع�
class PolynomialEquation_13_2
{
public:

private:
	// ���� ���� ���׽� p�� ����� �־��� �� �̺��� ��� p' �� ����� ��ȯ�Ѵ�
	vector<double> differentiate(const vector<double>& poly) {
		// n�� �������̴�~
		int n = poly.size() - 1;
		vector<double> q(n);
		for (int i = 1; i <= n; ++i) {
			// poly[i]*x^i �� �̺��ϸ� i*poly[i]*x^(i-1) �� �ȴ�
			q[i - 1] = i * poly[i];
		}
		return q;
	}

	// 1�� Ȥ�� 2�� �������� Ǭ��
	vector<double> solveNaive(const vector<double>& poly) {
		int n = poly.size() - 1;
		if (n == 1) {
			double a = poly[1], b = poly[0];
			// ax + b = 0
			if (fabs(a) < 1e-8) return vector<double>();
			return vector<double>(1, -b / a);
		}
		double a = poly[2], b = poly[1], c = poly[0];
		double d = b*b - 4 * a*c;
		vector<double> ret;
		if (d >= 0) {
			double sqrtd = sqrt(d);
			ret.push_back((-b - sqrtd) / (2 * a));
			if (sqrtd > 1e-8)
				ret.push_back((-b + sqrtd) / (2 * a));
		}
		return ret;
	}

	// ���׽� f(x) �� ��� poly�� �־��� ��, f(x0) �� ��ȯ�Ѵ�
	double evaluate(const vector<double>& poly, double x0) {
		double ret = poly.back();
		for (int i = int(poly.size()) - 2; i >= 0; --i)
			ret = ret * x0 + poly[i];
		return ret;
	}

	// �������� ���� ���밪�� L���Ͽ��� �Ѵ�
	const double L = 25;

	vector<double> solve(const vector<double>& poly) {
		int n = poly.size() - 1;
		// ���� ���: 2�� ������ �����ĵ��� Ǯ �� �ִ�
		if (n <= 2) return solveNaive(poly);

		// �������� �̺��ؼ� n-1�� �������� ��´�
		vector<double> derivative = differentiate(poly);
		vector<double> sols = solve(derivative);
		// �� ������ ���̸� �ϳ��ϳ� �˻��ϸ� ���� �ֳ� Ȯ���Ѵ�.
		sols.insert(sols.begin(), -L - 1);
		sols.insert(sols.end(), L + 1);
		vector<double> ret;
		for (int i = 0; i + 1 < sols.size(); ++i) {
			double x1 = sols[i], x2 = sols[i + 1];
			double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
			// f(x1) �� f(x2) �� ��ȣ�� ���� ��� ���� ����
			if (y1*y2 > 0) continue;
			// �Һ� ����: f(x1) <= 0 < f(x2)
			if (y1 > y2) { swap(y1, y2); swap(x1, x2); }
			// �̺й��� �������
			for (int iter = 0; iter < 100; ++iter) {
				double mx = (x1 + x2) / 2;
				double my = evaluate(poly, mx);
				if (y1*my > 0) {
					y1 = my;
					x1 = mx;
				}
				else {
					y2 = my;
					x2 = mx;
				}
			}
			ret.push_back((x1 + x2) / 2);
		}
		sort(ret.begin(), ret.end());
		return ret;
	}

	int CInput() {
		int n, cc = 0;
		while (cin >> n) {
			if (n == 0) break;
			vector<double> coef(n + 1);
			for (int i = 0; i <= n; ++i)
				cin >> coef[n - i];
			vector<double> sols = solve(coef);
			printf("Equation %d:", ++cc);
			for (int i = 0; i < sols.size(); ++i)
				printf(" %.4lf", sols[i]);
			printf("\n");

		}
	}
};