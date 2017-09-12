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

class RectUnion_15_11
{
public:

private:
	// x1 < x2, y1 < y2
	struct Rectangle {
		int x1, y1, x2, y2;
		Rectangle(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
		}
	};

	// ���簢������ ������ ����Ѵ�
	int unionArea(const vector<Rectangle>& rects) {
		if (rects.empty()) return 0;
		// �̺�Ʈ ����: (x ��ǥ, �����ΰ� �������ΰ�, �簢���� ��ȣ)
		typedef pair<int, pair<int, int> > Event;

		vector<Event> events;
		vector<int> ys;

		// �� �簢���� ��ȸ�ϸ鼭 y��ǥ�� ������ �̺�Ʈ�� ������ ã�´�
		for (int i = 0; i < rects.size(); i++) {
			ys.push_back(rects[i].y1);
			ys.push_back(rects[i].y2);
			events.push_back(Event(rects[i].x1, make_pair(1, i)));
			events.push_back(Event(rects[i].x2, make_pair(-1, i)));
		}

		// y��ǥ�� ������ �����ϰ� �ߺ��� ����
		sort(ys.begin(), ys.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());

		// �̺�Ʈ ����� ����
		sort(events.begin(), events.end());
		int ret = 0;
		// count[i] = ys[i]~ys[i+1] ������ ������ �簢���� ��
		vector<int> count(ys.size() - 1, 0);
		for (int i = 0; i < events.size(); ++i) {
			int x = events[i].first, delta = events[i].second.first, rectangle = events[i].second.second;
			// count[] �� ������Ʈ
			int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;
			for (int j = 0; j < ys.size(); ++j)
				if (y1 <= ys[j] && ys[j] < y2)
					count[j] += delta;
			// cutLength() ���� ����Ѵ�
			int cutLength = 0;
			for (int j = 0; j < ys.size() - 1; ++j)
				if (count[j] > 0)
					cutLength += ys[j + 1] - ys[j];
			// ���� �̺�Ʈ������ �Ÿ��� cutLength �� ���� ���� ret �� ���Ѵ�
			if (i + 1 < events.size())
				ret += cutLength * (events[i + 1].first - x);
		}
		return ret;
	}

	Rectangle getIntersection(const Rectangle& a, const Rectangle& b) {
		return Rectangle(max(a.x1, b.x1), max(a.y1, b.y1), min(a.x2, b.x2), min(a.y2, b.y2));
	}

	bool empty(const Rectangle& a) {
		return a.x1 >= a.x2 || a.y1 >= a.y2;
	}

	int area(const Rectangle& a) {
		return (a.x2 - a.x1) * (a.y2 - a.y1);
	}

	int unionAreaBrute(const vector<Rectangle>& rects, int here, int chosen, const Rectangle& intersection) {
		if (empty(intersection)) return 0;
		if (here == rects.size()) {
			if (chosen == 0) return 0;
			int a = area(intersection);
			return chosen % 2 == 1 ? a : -a;
		}

		int ret = unionAreaBrute(rects, here + 1, chosen, intersection);
		ret += unionAreaBrute(rects, here + 1, chosen + 1, getIntersection(intersection, rects[here]));
		return ret;
	}

	int CInput() {
		srand(12478);
		int TRIALS = 1000000;
		for (int tt = 0; tt < TRIALS; tt++) {
			if (tt % 9999 == 0) { printf("."); fflush(stdout); }
			vector<Rectangle> input;
			int n = rand() % 12 + 1;
			for (int i = 0; i < n; i++) {
				int x1 = rand() % 100;
				int x2 = rand() % 100;
				int y1 = rand() % 100;
				int y2 = rand() % 100;
				if (x1 == x2 || y1 == y2) continue;
				if (x1 > x2) swap(x1, x2);
				if (y1 > y2) swap(y1, y2);
				input.push_back(Rectangle(x1, y1, x2, y2));
			}

			assert(unionArea(input) == unionAreaBrute(input, 0, 0, Rectangle(0, 0, 100, 100)));
		}
		printf("\nall pass.\n");
	}
};