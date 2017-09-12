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

const double PI = 2.0 * acos(0.0);
class ConvPolyDia_15_11
{
public:

private:
	// 2���� ���͸� ǥ���Ѵ�
	struct vector2 {
		double x, y;
		explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

		// �� ������ ��
		bool operator == (const vector2& rhs) const { return x == rhs.x && y == rhs.y; }
		bool operator < (const vector2& rhs) const { if (x != rhs.x) return x < rhs.x; return y < rhs.y; }

		// ������ ������ ����
		vector2 operator + (const vector2& rhs) const { return vector2(x + rhs.x, y + rhs.y); }
		vector2 operator - (const vector2& rhs) const { return vector2(x - rhs.x, y - rhs.y); }
		vector2 operator - () const { return vector2(-x, -y); }

		// ��Į��� ����
		vector2 operator * (double rhs) const { return vector2(x * rhs, y * rhs); }

		// ������ ���̸� ��ȯ�Ѵ�
		double norm() const { return hypot(x, y); }

		// ������ ���� ���� ���� (unit vector) �� ��ȯ�Ѵ�
		vector2 normalize() const { double n = norm(); return vector2(x / n, y / n); }

		// x���� ���� �������κ��� �� ���ͱ��� �ݽð�������� �� ����
		double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

		// ����/������ ����
		double dot(const vector2& rhs) const { return x * rhs.x + y * rhs.y; }
		double cross(const vector2& rhs) const { return x * rhs.y - rhs.x * y; }

		// �� ���͸� rhs �� �翵�� ���
		vector2 project(const vector2& rhs) const {
			vector2 r = rhs.normalize();
			return r * r.dot(*this);
		}
	};

	typedef vector<vector2> polygon;

	// �ð� �ݴ�������� �־��� ���� �ٰ������� ���� �� ������ �� ������ �Ÿ��� ��ȯ�Ѵ�.
	double diameter(const polygon& p) {
		int n = p.size();

		// ���� ���ʿ� �ִ� ���� �����ʿ� �ִ� ���� �켱 ã�´�
		int left = min_element(p.begin(), p.end()) - p.begin();
		int right = max_element(p.begin(), p.end()) - p.begin();

		// p[left] �� p[right] �� ���� �������� ���δ�. �� �������� ���� ���ݴ� ������ ����Ű�Ƿ�,
		// A �� ���⸸�� ǥ���ϸ� �ȴ�.
		vector2 calipersA(0, 1);
		double ret = (p[right] - p[left]).norm();

		// toNext[i] = p[i] ���� ���� �������� ������ ��Ÿ���� ��������
		vector<vector2> toNext(n);
		for (int i = 0; i < n; i++)
			toNext[i] = (p[(i + 1) % n] - p[i]).normalize();

		// a �� b �� ���� �� ������ ��� ���� ä�� ȸ���ϰ� �ִ°��� ��Ÿ����
		int a = left, b = right;
		// �� ���� ���Ƽ� �� ������ ���� ��ġ�� �ٲ� ������ ����Ѵ�
		while (a != right || b != left) {
			// a ���� ���� �������� ������ b ���� ���� �������� ���� �� ��� ���� ������ Ȯ��
			double cosThetaA = calipersA.dot(toNext[a]);
			double cosThetaB = -calipersA.dot(toNext[b]);
			if (cosThetaA > cosThetaB) { // thetaA < thetaB
				calipersA = toNext[a];
				a = (a + 1) % n;
			}
			else {
				calipersA = -toNext[b];
				b = (b + 1) % n;
			}
			ret = max(ret, (p[a] - p[b]).norm());
		}
		return ret;
	}

	// (a,b,c) �� �׸��� �ﰢ���� ����
	double area(const vector2& a, const vector2& b, const vector2& c) {
		return fabs((b - a).cross(c - a)) / 2.0;
	}

	// ���� �ٰ��� ������ ���ϴ� Shamos �˰���
	double diameter2(const polygon& p) {

		int n = p.size();
		int b = 1;
		double ret = 0;
		for (int a = 0; a < n; ++a) {
			while (area(p[(b + 1) % n], p[a], p[(a + 1) % n]) > area(p[b], p[a], p[(a + 1) % n]))
				b = (b + 1) % n;
			ret = max(ret, (p[a] - p[b]).norm());
		}
		return ret;
	}

	typedef vector<vector2> polygon;

	// points �� �ִ� ������ ��� �����ϴ� �ּ��� ���� �ٰ����� ã�´�.
	// ���� �ٰ����� �������� ���� ���� �Ʒ� ������ �����ؼ� �ݽð� �������� ��ȯ�ȴ�.
	// �� ���� ���� �� �� �̻��� ���� ���� ��� ��� �͵��� ���õȴ�.
	polygon giftWrap(const vector<vector2>& points) {
		int n = points.size();
		polygon hull;

		// ���� ���� �Ʒ� ���� ã�´�. �� ���� ������ �ݵ�� ���Եȴ�.
		vector2 pivot = *min_element(points.begin(), points.end());
		hull.push_back(pivot);

		while (true) {
			// (p - ph) �� ���� ������ ���� ã�´�. ������ ���� ���� �� ������
			// ���� �� ���� �����Ѵ�.
			vector2 ph = hull.back(), next = points[0];
			for (int i = 1; i < n; i++) {
				double cross = (next - ph).cross(points[i] - ph);
				double dist = (next - ph).norm() - (points[i] - ph).norm();
				if (cross > 0 || (cross == 0 && dist < 0))
					next = points[i];
			}
			// ���������� ���ƿ����� �����Ѵ�.
			if (next == pivot) break;
			hull.push_back(next);
		}

		return hull;
	}

	void testPoly(const polygon& p) {
		polygon hull = giftWrap(p);
		double brute = 0;
		for (int i = 0; i < hull.size(); i++)
			for (int j = 0; j < i; j++)
				brute = max(brute, (hull[i] - hull[j]).norm());
		assert(fabs(brute - diameter(hull)) < 1e-8);
		if (fabs(brute - diameter2(hull)) > 1e-8) {
			printf("damn\n");
			diameter2(hull);
			assert(false);

		}
		//printf("PASS %.10lf\n", brute);
	}

	int CInput() {
		vector<vector2> points;
		points.push_back(vector2(0, 0));
		points.push_back(vector2(1, 0));
		points.push_back(vector2(0, 2));
		points.push_back(vector2(-1, 0));
		testPoly(points);
		points.clear();
		points.push_back(vector2(0, 0));
		points.push_back(vector2(1, 0));
		points.push_back(vector2(1, 1)); testPoly(points);
		points.push_back(vector2(0, 1)); testPoly(points);
		points.push_back(vector2(0, 1)); testPoly(points);
		points.push_back(vector2(0.5, 0.5)); testPoly(points);
		points.push_back(vector2(1.5, 0.5)); testPoly(points);
		points.push_back(vector2(1.5, 2)); testPoly(points);
		points.push_back(vector2(2, 1)); testPoly(points);
		points.push_back(vector2(1, 2)); testPoly(points);


		int TRIALS = 1000000;
		for (int cc = 0; cc < TRIALS; cc++) {
			vector<vector2> points;
			points.push_back(vector2(50, 50));
			points.push_back(vector2(51, 50));
			points.push_back(vector2(51, 51));
			for (int i = 0; i < 50; ++i) {
				int y = rand() % 100, x = rand() % 100;
				points.push_back(vector2(x, y));
				testPoly(points);
			}
			if (cc % 100 == 99) { printf("."); fflush(stdout); }
		}

		printf("\nall good.\n");
	}

};
