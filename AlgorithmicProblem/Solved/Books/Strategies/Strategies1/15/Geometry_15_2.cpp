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

const double EPSILON = 1e-8;
const double PI = 2.0 * acos(0.0);
class Geometry_15_2
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
		// �����Ϳ� ���� ȣ���� ��� ������� ���ǵ��� �ʴ´�
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

	// �������� ���� b �� ���� a �� �ݽð� �����̸� ���, �ð� �����̸� ����, �����̸� 0 �� ��ȯ�Ѵ�
	double ccw(vector2 a, vector2 b) {
		return a.cross(b);
	}

	// �� p �� �������� ���� b �� ���� a �� �ݽð� �����̸� ���, �ð� �����̸� ����, �����̸� 0 �� ��ȯ�Ѵ�
	double ccw(vector2 p, vector2 a, vector2 b) {
		return ccw(a - p, b - p);
	}


	// (a,b) �� �����ϴ� ���� (c,d) �� �����ϴ� ���� ������ x �� ��ȯ�Ѵ�.
	// �� ���� �����̸� (��ġ�� ��츦 ����) ������, �ƴϸ� ���� ��ȯ�Ѵ�.
	bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
		double det = (b - a).cross(d - c);
		if (det == 0) return false;
		x = a + (b - a) * ((c - a).cross(d - c) / det);
		return true;
	}

	// (a,b) �� (c,d) �� ������ �� ������ �� �̵��� �� ������ ��ġ�� Ȯ���Ѵ�
	bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		// �� ������ ��ġ�� �ʴ� ��츦 �켱 �ɷ�����
		if (b < c || d < a) return false;
		// �� ������ Ȯ���� ��ģ��. �������� �ϳ� ã��.
		if (a < c) p = c; else p = a;
		return true;
	}

	// p �� (a,b) �� ���θ鼭 �� ���� x,y�࿡ ������ �ּ� �簢�� ���ο� �ִ��� Ȯ���Ѵ�.
	// a, b, p �� ������ �� �ִٰ� �����Ѵ�.
	bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
		if (b < a) swap(a, b);
		return p == a || p == b || (a < p && p < b);
	}

	// (a,b) ���а� (c,d) ������ ������ p �� ��ȯ�Ѵ�.
	// ������ ���� �� ���� ��� �ƹ� ���̳� ��ȯ�Ѵ�.
	// �� ������ �������� ���� ��� false �� ��ȯ�Ѵ�.
	bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
		// �� ������ ������ ��츦 �켱 ���ܷ� ó���Ѵ�
		if (!lineIntersection(a, b, c, d, p)) return parallelSegments(a, b, c, d, p);
		// p �� �� ���п� ���ԵǾ� �ִ� ��쿡�� ���� ��ȯ�Ѵ�
		return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);

	}

	// �� ������ ���� �����ϴ��� ���θ� ��ȯ�Ѵ�
	bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
		double ab = ccw(a, b, c) * ccw(a, b, d);
		double cd = ccw(c, d, a) * ccw(c, d, b);
		// �� ������ �� ���� ���� �ִ� ���
		if (ab == 0 && cd == 0) {
			if (b < a) swap(a, b);
			if (d < c) swap(c, d);
			return !(b < c || d < a);
		}
		return ab <= 0 && cd <= 0;
	}

	// �� p ���� (a,b) ������ ���� ������ ���� ���Ѵ�
	vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
		return a + (p - a).project(b - a);
	}

	// �� p �� (a,b) ���� ������ �Ÿ��� ���Ѵ�
	double pointToLine(vector2 p, vector2 a, vector2 b) {
		return (p - perpendicularFoot(p, a, b)).norm();
	}

	// �־��� �ܼ� �ٰ��� p �� ���̸� ���Ѵ�. p �� �� �������� ��ġ ������ �������� �־�����.
	double area(const vector<vector2>& p) {
		double ret = 0;
		for (int i = 0; i < p.size(); ++i) {
			int j = (i + 1) % p.size();
			ret = ret + (p[i].x * p[j].y - p[j].x * p[i].y);
		}
		return fabs(ret) / 2.0;
	}

	// �� q �� �ٰ��� p �ȿ� ���ԵǾ� ���� ��� ��, �ƴ� ��� ������ ��ȯ�Ѵ�.
	// q �� �ٰ����� ��� ���� �ִ� ����� ��ȯ���� ���ǵǾ� ���� �ʴ�.
	bool isInside(vector2 q, const vector<vector2>& p) {
		int crosses = 0;
		for (int i = 0; i < p.size(); ++i) {
			int j = (i + 1) % p.size();
			// (p[i], p[j]) �� �������� ���η� ���������°�?
			if ((p[i].y > q.y) != (p[j].y > q.y)) {
				double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
				if (q.x < atX)
					++crosses;
			}
		}
		return crosses % 2 > 0;
	}


	typedef vector<vector2> polygon;

	// points �� �ִ� ������ ��� �����ϴ� �ּ��� ���� �ٰ����� ã�´�.
	// ���� �ٰ����� �������� ���� ���� �Ʒ� ������ �����ؼ� �ð� �������� ��ȯ�ȴ�.
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
				double cross = ccw(ph, next, points[i]);
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


	// (a,b) �� �����ϴ� �������� �ٰ��� p �� �ڸ� ��, (a,b) �� ���ʿ� �ִ� �κе��� ��ȯ�Ѵ�
	polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
		int n = p.size();
		vector<bool> inside(n);
		for (int i = 0; i < n; ++i)
			inside[i] = ccw(a, b, p[i]) >= 0;
		// �̿��� ��쿡�� �Ϻδ� ���� ���ʿ�, �Ϻδ� ���� �����ʿ� ��������
		polygon ret;
		for (int i = 0; i < n; ++i) {
			int j = (i + 1) % n;
			if (inside[i]) ret.push_back(p[i]);
			if (inside[i] != inside[j]) {
				vector2 intersection;
				assert(lineIntersection(p[i], p[j], a, b, intersection));
				ret.push_back(intersection);
			}
		}
		return ret;
	}

	polygon readPoly() {
		int n;
		cin >> n;
		polygon p(n);
		for (int i = 0; i < n; i++)
			cin >> p[i].x >> p[i].y;
		return p;
	}

	vector2 readVector() {
		vector2 ret;
		cin >> ret.x >> ret.y;
		return ret;
	}

	void writePoly(const polygon& p) {
		for (int i = 0; i < p.size(); i++)
			printf("%s%.15lf %.15lf", (i ? " " : ""), p[i].x, p[i].y);
		printf("\n");
	}

	void testConvexHull() {
		polygon p = readPoly();
		writePoly(giftWrap(p));
	}

	void testPolyCut() {
		double x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		polygon p = readPoly();

		p = cutPoly(p, vector2(x1, y1), vector2(x2, y1));
		p = cutPoly(p, vector2(x2, y1), vector2(x2, y2));
		p = cutPoly(p, vector2(x2, y2), vector2(x1, y2));
		p = cutPoly(p, vector2(x1, y2), vector2(x1, y1));
		writePoly(p);
	}

	bool approx(vector2 a, vector2 b) {
		return fabs((a - b).norm()) < 1e-7;
	}

	int CInput(int argc, char* argv[]) {
		assert(vector2(1, 0).cross(vector2(0, 1)) > 0);
		assert(vector2(0, 1).cross(vector2(1, 1)) < 0);
		assert(fabs(vector2(1, 1).polar() - PI / 4) < 1e-9);
		vector2 a(1, 1), b(0, 1), c(1, 0);
		assert(fabs((a - b - c).norm()) < 1e-9);
		assert(b.norm() == 1);
		assert(approx(vector2(4, 0), vector2(4, 9).project(vector2(127, 0))));
		assert(ccw(vector2(1, 1), vector2(-1, 1)) > 0);
		assert(ccw(vector2(4, 4), vector2(5, 5), vector2(3, 5)) > 0);
		assert(ccw(vector2(-1, 1), vector2(1, 1)) < 0);
		{
			vector2 a(1, 0), b(-1, 0), c(0.5, -1), d(0.5, 1);
			vector2 p, q(0.5, 0);
			assert(lineIntersection(a, b, c, d, p) && approx(q, p));
			assert(lineIntersection(a, b, d, c, p) && approx(q, p));
			assert(lineIntersection(b, a, c, d, p) && approx(q, p));
			assert(lineIntersection(b, a, d, c, p) && approx(q, p));
			assert(lineIntersection(d, c, b, a, p) && approx(q, p));
			assert(!lineIntersection(a, b, vector2(2, 0), vector2(3, 0), p));
			assert(!lineIntersection(c, d, vector2(4, -7), vector2(4, -8), p));
			assert(segmentIntersection(a, b, c, d, p) && approx(q, p));
			assert(segmentIntersection(a, b, d, c, p) && approx(q, p));
			assert(segmentIntersection(b, a, c, d, p) && approx(q, p));
			assert(segmentIntersection(b, a, d, c, p) && approx(q, p));
			assert(segmentIntersection(d, c, b, a, p) && approx(q, p));
			assert(segmentIntersects(a, b, c, d));
			assert(!segmentIntersects(a, c, b, d));
			assert(!segmentIntersection(a, b, vector2(2, 0), vector2(3, 0), p));
			assert(!segmentIntersection(c, d, vector2(4, -7), vector2(4, -8), p));

			vector2 w(-1, -1), x(0, 0), y(1, 1), z(2, 2);
			assert(!segmentIntersection(w, x, y, z, p));
			assert(segmentIntersection(w, x, x, z, p) && approx(x, p));
			assert(segmentIntersection(x, z, x, w, p) && approx(x, p));
			assert(segmentIntersection(x, y, x, z, p));
			assert(segmentIntersection(w, z, x, y, p));
			assert(segmentIntersection(z, w, x, y, p));
			assert(!segmentIntersects(w, x, y, z));
			assert(segmentIntersects(w, z, x, y));
			assert(segmentIntersects(w, x, x, y));
			assert(segmentIntersects(w, y, x, z));
		}

		assert(approx(perpendicularFoot(vector2(7, 6), vector2(0, 0), vector2(12, 3)), vector2(8, 2)));
		vector<vector2> poly;
		poly.push_back(vector2(0, 0));
		poly.push_back(vector2(1, 1));
		poly.push_back(vector2(1, 2));
		poly.push_back(vector2(-1, 1));
		assert(area(poly) == 2);

		// convex hull tests
		{
#define NOPAREN(...) __VA_ARGS__
#define TEST(_poly, _hull) {\
	vector2 poly[] = {NOPAREN _poly}, hull[] = {NOPAREN _hull}; \
	polygon res = giftWrap(polygon(poly, poly + sizeof(poly) / sizeof(vector2)));\
	if(res.size() != sizeof(hull) / sizeof(vector2)) \
		fprintf(stderr, "Expected %d Result %d\n", int(sizeof(hull) / sizeof(vector2)), int(res.size())); \
	assert(res.size() == sizeof(hull) / sizeof(vector2)); \
	for(int i = 0; i < res.size(); ++i) {\
		if(!(res[i] == hull[i])) \
			printf("Expected (%g,%g) Result (%g,%g)\n", hull[i].x, hull[i].y, res[i].x, res[i].y); \
		assert(res[i] == hull[i]); \
	} fprintf(stderr, "PASS\n"); }

			vector2 a(0, 0), b(1, 0), c(1, 1), d(0, 1), e(0.5, 0.5), f(0.5, 1.5);
			vector2 poly1[] = { b, a, c }, poly1h[] = { a, c, b };

			TEST((b, a, c), (a, c, b));
			TEST((c, b, a), (a, c, b));
			TEST((d, a, b, c), (a, d, c, b));
			TEST((b, d, a, c), (a, d, c, b));
			TEST((d, e, b, a, c), (a, d, c, b));
			TEST((d, b, e, f, a, c), (a, d, f, c, b));
			TEST((a, c, e, b), (a, c, b));
			TEST((a, d, c, e), (a, d, c));
			TEST((a, e, c), (a, c));
		}

		fprintf(stderr, "all good.\n");

		vector2 v;

		if (argc == 2 && strcmp(argv[1], "polycut") == 0)
			testPolyCut();
		else if (argc == 2 && strcmp(argv[1], "convex") == 0)
			testConvexHull();

	}
};