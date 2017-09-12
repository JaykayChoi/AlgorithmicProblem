#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

struct Pos
{
	double x, y;
	Pos() : x(0.0), y(0.0) {}
	Pos(double _x, double _y) : x(_x), y(_y) {}
};

double getDistance(const Pos& a, const Pos& b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double getSlopeBetweenPoints(const Pos& a, const Pos& b)
{
	return (b.y - a.y) / (b.x - a.x);
}

Pos getLineIntersect(const Pos& a, double aSlope, const Pos& b, double bSlope)
{
	Pos ret;
	ret.x = (aSlope * a.x - bSlope * b.x + b.y - a.y) / (aSlope - bSlope);
	ret.y = aSlope * (ret.x - a.x) + a.y;
	return ret;
}

Pos getLineIntersect(const Pos& a1, const Pos& a2, const Pos& b1, const Pos& b2)
{
	return getLineIntersect(a1, getSlopeBetweenPoints(a1, a2), b1, getSlopeBetweenPoints(b1, b2));
}

double getArea(const Pos& a, const Pos& b, const Pos& c)
{
	return 0.5 * abs(a.x * b.y + b.x * c.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y);
}
double getArea(const Pos& a, const Pos& b, const Pos& c, const Pos& d)
{
	return 0.5 * abs(a.x * b.y + b.x * c.y + c.x * d.y + d.x * a.y - b.x * a.y - c.x * b.y - d.x * c.y - a.x * d.y);
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Pos a, b, c, d, a_, b_, c_, d_;
		for (int j = 0; j < 5; j++)
		{
			double coordinate;
			cin >> coordinate;
			switch (j)
			{
			case 0:
				b.x = coordinate;
				break;
			case 1:
				c.x = coordinate;
				break;
			case 2:
				c.y = coordinate;
				break;
			case 3:
				d.x = coordinate;
				break;
			case 4:
				d.y = coordinate;
				break;
			}
		}
		a_.x = (b.x + c.x) / 2.0;
		a_.y = (b.y + c.y) / 2.0;
		b_.x = (c.x + d.x) / 2.0;
		b_.y = (c.y + d.y) / 2.0;
		c_.x = (d.x + a.x) / 2.0;
		c_.y = (d.y + a.y) / 2.0;
		d_.x = (a.x + b.x) / 2.0;
		d_.y = (a.y + b.y) / 2.0;


		Pos ab_ = getLineIntersect(a, a_, b, b_);
		Pos bc_ = getLineIntersect(b, b_, c, c_);
		Pos cd_ = getLineIntersect(c, c_, d, d_);
		Pos da_ = getLineIntersect(d, d_, a, a_);

		cout.precision(3);
		cout << fixed << getArea(a, b, ab_) << " ";
		cout << fixed << getArea(b, c, bc_) << " ";
		cout << fixed << getArea(c, d, cd_) << " ";
		cout << fixed << getArea(d, a, da_) << " ";
		cout << fixed << getArea(ab_, bc_, cd_, da_) << " ";
		cout << (int)ceil(getDistance(da_, ab_) + getDistance(ab_, bc_)
			+ getDistance(bc_, cd_) + getDistance(cd_, da_)) << endl;
	}

	return 0;
}