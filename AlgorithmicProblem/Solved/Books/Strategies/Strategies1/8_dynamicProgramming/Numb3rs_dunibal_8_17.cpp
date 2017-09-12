#include "Utils.h"
   

using namespace std;

//https://algospot.com/judge/problem/read/NUMB3RS

class Numb3rs_dunibal_8_17
{
public:

private:
	int n;	//���� ����
	int d;	//Ż�� �� ���� �ϼ�
	int p;	//���� ��ġ
	int q;	//Ȯ���� ������ ���� ��ȣ
	double cache[51][101];

	// connected[i][j] = ���� i, j �� ����Ǿ� �ֳ� ����
	// deg[i] = ���� i �� ����� ������ ����
	int connected[51][51], deg[51];

	double search(vector<int>& path) 
	{
		// ���� ���: d���� ���� ���
		if (path.size() == d + 1) 
		{
			// �� �ó������� q ���� ������ �ʴ´ٸ� ��ȿ
			if (path.back() != q) 
				return 0.0;
			// path �� ���� Ȯ���� ����Ѵ�
			double ret = 1.0;
			for (int i = 0; i + 1 < path.size(); ++i)
				ret /= deg[path[i]];
			return ret;
		}
		double ret = 0;
		// ����� ���� ��ġ�� �����Ѵ�
		for (int there = 0; there < n; there++)
			if (connected[path.back()][there]) {
				path.push_back(there);
				ret += search(path);
				path.pop_back();
			}
		return ret;
	}

	double search2(int here, int days) {
		// ���� ���: d ���� ���� ���
		if (days == d) return (here == q ? 1.0 : 0.0);
		// �޸������̼�
		double& ret = cache[here][days];
		if (ret > -0.5) return ret;
		ret = 0.0;
		for (int there = 0; there < n; ++there)
			if (connected[here][there])
				ret += search2(there, days + 1) / deg[here];
		return ret;
	}

	double search3(int here, int days) {
		// ���� ���: 0 ��°
		if (days == 0) return (here == p ? 1.0 : 0.0);
		// �޸������̼�
		double& ret = cache[here][days];
		if (ret > -0.5) return ret;
		ret = 0.0;
		for (int there = 0; there < n; ++there)
			if (connected[here][there])
				ret += search3(there, days - 1) / deg[there];
		return ret;
	}
	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n >> d >> p;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					cin >> connected[i][j];
				deg[i] = accumulate(connected[i], connected[i] + n, 0);
			}
			int queries;
			cin >> queries;
			for (int i = 0; i < n; i++)
				for (int j = 0; j <= d; j++)
					cache[i][j] = -1;
			for (int i = 0; i < queries; i++) {
				cin >> q;
				if (i) printf(" ");
				vector<int> path(1, p);
				printf("%.8lf", search3(q, d));
			}
			printf("\n");
		}
	}
};
