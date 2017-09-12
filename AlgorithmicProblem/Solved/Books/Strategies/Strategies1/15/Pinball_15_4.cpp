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

//https://algospot.com/judge/problem/read/PINBALL

class Pinball_15_4
{
public:

private:
	// 2���� ���͸� ǥ���Ѵ�
	struct vector2 {
		double x, y;
		vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

		// �� ���Ͱ� ���� ���
		bool operator == (const vector2& rhs) const { return x == rhs.x && y == rhs.y; }

		// ������ ������ ����, ���� �������� ����
		vector2 operator + (const vector2& rhs) const { return vector2(x + rhs.x, y + rhs.y); }
		vector2 operator - (const vector2& rhs) const { return vector2(x - rhs.x, y - rhs.y); }
		vector2 operator - () const { return vector2(-x, -y); }

		// ��Į��� ����
		vector2 operator * (double rhs) const { return vector2(x * rhs, y * rhs); }

		// ������ ���̸� ��ȯ�Ѵ�
		double norm() const { return hypot(x, y); }

		// ������ ���� ���� ���� (unit vector) �� ��ȯ�Ѵ�
		vector2 normalize() const { double n = norm(); return vector2(x / n, y / n); }

		// ����/������ ����
		double dot(const vector2& rhs) const { return x * rhs.x + y * rhs.y; }
		double cross(const vector2& rhs) const { return x * rhs.y - rhs.x * y; }

		// �� ���͸� rhs �� �翵�� ���
		vector2 project(const vector2& rhs) const {
			vector2 r = rhs.normalize();
			return r * r.dot(*this);
		}
	};

	int n;
	// �� �� �߽��� ��ġ�� ������
	vector2 center[50];
	int radius[50];

	const double EPSILON = 1e-8;

	// 2�������� ax^2 + bx + c = 0 �� ��� �Ǳ��� ũ�� ������� ��ȯ�Ѵ�
	vector<double> solve2(double a, double b, double c)
	{
		double d = b*b - 4 * a*c;
		if (d < -EPSILON) return vector<double>();
		if (d < EPSILON) return vector<double>(1, -b / (2 * a));
		vector<double> ret;
		ret.push_back((-b - sqrt(d)) / (2 * a));
		ret.push_back((-b + sqrt(d)) / (2 * a));
		return ret;
	}

	const double INFTY = 1e200;

	// here �� �ִ� ���� 1�ʸ��� dir ��ŭ ������ ��, center �� �߽����� �ϰ�
	// ������ radius �� ��ֹ��� �� �� �Ŀ� �浹�ϴ��� ��ȯ�Ѵ�
	double hitCircle(vector2 here, vector2 dir, vector2 center, int radius) {
		double a = dir.dot(dir);
		double b = 2 * dir.dot(here - center);
		double c = center.dot(center) + here.dot(here) - 2 * here.dot(center) - radius * radius;
		vector<double> sols = solve2(a, b, c);
		if (sols.empty() || sols[0] < EPSILON) return INFTY;
		return sols[0];
	}

	// here �� �ִ� ���� dir �������� ������ center �� �߽����� �ϴ� ��ֹ�����
	// contact ��ġ���� �浹���� �� ���� ���ο� ������ ��ȯ�Ѵ�
	vector2 reflect(vector2 here, vector2 dir, vector2 center, vector2 contact) {
		return (dir - dir.project(contact - center) * 2).normalize();
	}

	// ���� ���� ��ġ�� ������ �־��� �� �ִ� 100���� �浹�� ����Ѵ�
	void simulate(vector2 here, vector2 dir) {

		// ������ �׻� ���� ���ͷ� ��������
		dir = dir.normalize();

		int hitCount = 0;
		while (hitCount < 100) {
			// fprintf(stderr, "here (%.2lf, %.2lf)\n", here.x, here.y);
			// �̹��� �浹�� ��ֹ��� ã�´�.
			int circle = -1;
			double time = INFTY*0.5;

			// �� ��ֹ��� ��ȸ�ϸ� ���� ���� ������ ��ֹ��� ã�´�
			for (int i = 0; i < n; ++i) {
				double cand = hitCircle(here, dir, center[i], radius[i] + 1);
				if (cand < time) {
					time = cand;
					circle = i;
				}
			}
			// �� �̻� ��ֹ��� �浹���� �ʰ� �������� ��� ���
			if (circle == -1) break;

			// �ε����� ��ֹ��� ��ȣ�� ����Ѵ�
			if (hitCount++) cout << " ";
			cout << circle;

			// ���� �� ��ġ�� ����Ѵ�
			vector2 contact = here + dir * time;

			// �ε��� ��ġ�� �� �������� here �� dir �� �����Ѵ�
			dir = reflect(here, dir, center[circle], contact);
			here = contact;
		}
		cout << endl;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int x, y, dx, dy;
			cin >> x >> y >> dx >> dy >> n;
			vector2 here, dir;
			here = vector2(x, y);
			dir = vector2(dx, dy).normalize();
			for (int i = 0; i < n; i++) {
				int x, y, r;
				cin >> x >> y >> radius[i];
				center[i] = vector2(x, y);
			}

			simulate(here, dir);
		}
	}
};