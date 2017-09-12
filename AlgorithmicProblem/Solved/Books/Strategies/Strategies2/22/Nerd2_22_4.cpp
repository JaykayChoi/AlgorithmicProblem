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

//https://algospot.com/judge/problem/read/NERD2

class Nerd2_22_4
{
public:

private:
	// ���� �ٸ� ���� ��������� �ʴ� ������ ����� �����Ѵ�
	// coords[x] = y
	map<int, int> coords;

	// ���ο� �� (x,y) �� ������ �ٸ� ���鿡 ������ϴ��� Ȯ���Ѵ�
	bool isDominated(int x, int y) {
		// x ���� �����ʿ� �ִ� �� �� ���� ���ʿ� �ִ� ���� ã�´�
		map<int, int>::iterator it = coords.lower_bound(x);
		// �׷� ���� ������ (x,y) �� ��������� �ʴ´�
		if (it == coords.end()) return false;
		// �� ���� x ���� �����ʿ� �ִ� �� �� ���� ���� �ִ� ���̹Ƿ�,
		// (x,y) �� ��� ���� ����Ƿ��� �� ������ ����Ǿ�� �Ѵ�
		return y < it->second;
	}

	// ���ο� �� (x,y) �� ������ϴ� ������ Ʈ������ �����
	void removeDominated(int x, int y) {
		map<int, int>::iterator it = coords.lower_bound(x);
		// (x,y) ���� ���ʿ� �ִ� ���� ����!
		if (it == coords.begin()) return;
		--it;
		// ���� �Һ� ����: it �� (x,y) ���� �ٷ� ���ʿ� �ִ� ��
		while (true) {
			// (x,y) �ٷ� ���ʿ� ���� ���� ã�´�
			// it �� ǥ���ϴ� ���� (x,y) �� ������� �ʴ´ٸ� ���� ����
			if (it->second > y) break;

			// ���� ���� �� �����Ƿ� it �� ����� �����Ѵ�
			if (it == coords.begin()) {
				coords.erase(it);
				break;
			}
			// ���� ������ ���ͷ����͸� �ϳ� �Ű� ���� it �� �����
			else {
				map<int, int>::iterator jt = it;
				--jt;
				coords.erase(it);
				it = jt;
			}
		}
	}

	// �� �� (x,y) �� �߰��Ǿ��� �� coords �� �����ϰ�,
	// �ٸ� ���� ��������� �ʴ� ������ ������ ��ȯ�Ѵ�
	int registered(int x, int y) {
		// (x,y) �� �̹� ������ϴ� ��쿡�� �׳� (x,y) �� ������
		if (isDominated(x, y)) return coords.size();
		// ������ �ִ� �� �� (x,y) �� ������ϴ� ������ �����
		removeDominated(x, y);
		coords[x] = y;
		return coords.size();
	}

	int CInput() {
		//int cases;
		//scanf("%d", &cases);
		//for (int cc = 0; cc < cases; ++cc) {
		//	int n;
		//	scanf("%d", &n);
		//	int ret = 0;
		//	coords.clear();
		//	for (int i = 0; i < n; i++) {
		//		int x, y;
		//		scanf("%d %d", &x, &y);
		//		ret += registered(x, y);
		//	}
		//	printf("%d\n", ret);
		//}
	}
};