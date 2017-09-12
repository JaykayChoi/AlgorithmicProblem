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

//https://algospot.com/judge/problem/read/GENIUS

/*
struct SquareMatrix {
	int N;
	vector<vector<double> > v;
	SquareMatrix(int _N);
	~SquareMatrix();
	static SquareMatrix identity(int N);
	SquareMatrix operator * (const SquareMatrix& rhs) const;
	SquareMatrix pow(int n) const;
	double* operator [] (int idx);
};

SquareMatrix::SquareMatrix(int _N) {
	N = _N;
	v.resize(N, vector<double>(N, 0));
}

SquareMatrix::~SquareMatrix() {
}

SquareMatrix SquareMatrix::identity(int N) {
	SquareMatrix ret = SquareMatrix(N);
	for (int i = 0; i < N; i++) ret.v[i][i] = 1;
	return ret;
}

SquareMatrix SquareMatrix::operator * (const SquareMatrix& rhs) const {
	assert(N == rhs.N);

	SquareMatrix ret = SquareMatrix(N);
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				ret.v[i][j] += v[i][k] * rhs.v[k][j];
	return ret;
}

SquareMatrix SquareMatrix::pow(int n) const {
	if (n == 0) return identity(N);
	if (n % 2 > 0) return (*this) * pow(n - 1);
	SquareMatrix half = pow(n / 2);
	return half * half;
}

double* SquareMatrix::operator [] (int idx) {
	return &v[idx][0];
}

class Genius_9_24
{
public:

private:
	int n, k, length[50];
	double T[50][50];

	vector<double> getProb1() {
		// c[time][song] = time�� �Ŀ� song�� �뷡�� ������ Ȯ��
		double c[5][50];

		memset(c, 0, sizeof(c));
		c[0][0] = 1.0;
		for (int time = 1; time <= k; ++time)
			for (int song = 0; song < n; ++song) {
				double& prob = c[time % 5][song];
				prob = 0;
				for (int last = 0; last < n; last++)
					prob += c[(time - length[last] + 5) % 5][last] * T[last][song];
			}
		vector<double> ret(n);
		// song�� �뷡�� ����ǰ� ���� Ȯ���� ����Ѵ�
		for (int song = 0; song < n; song++)
			// song�� �뷡�� �������� �ð��� ��� ã�� ���Ѵ�
			for (int start = k - length[song] + 1; start <= k; start++)
				ret[song] += c[start % 5][song];
		return ret;
	}

	// k�� 30�� �Ŀ� �� ���� ����ǰ� ���� Ȯ���� ��ȯ�Ѵ�
	vector<double> getProb2() {
		SquareMatrix W(4 * n);
		// ù 3*n���� ���Ҵ� �״�� �����ؿ´�
		for (int i = 0; i < 3 * n; ++i)
			W[i][i + n] = 1.0;
		// ������ n���� ���Ҵ� ���� ���ҵ��� ���� �������� �̷������
		for (int i = 0; i < n; ++i)
			// C[time+1][i] = C[time+1-length[j]][j] * T[j][i];
			for (int j = 0; j < n; ++j)
				W[3 * n + i][(4 - length[j])*n + j] = T[j][i];

		SquareMatrix Wk = W.pow(k);
		vector<double> ret(n);
		// song�� �뷡�� ����ǰ� ���� Ȯ���� ����Ѵ�
		for (int song = 0; song < n; ++song)
			// song�� �뷡�� �������� �ð��� ��� ã�� ���Ѵ�
			for (int start = 0; start < length[song]; ++start)
				ret[song] += Wk[(3 - start)*n + song][3 * n];
		return ret;
	}

	bool eq(double a, double b) {
		return fabs(a - b) <= 1e-7;
	}

	int CInput(int argc, char* argv[]) 
	{
		//bool verify = (argc > 1) && (strcmp(argv[1], "verify") == 0);
		//int cases;
		//scanf("%d", &cases);
		//for (int cc = 0; cc < cases; ++cc) {
		//	int m;
		//	scanf("%d %d %d", &n, &k, &m);
		//	for (int i = 0; i < n; i++) scanf("%d", &length[i]);
		//	for (int i = 0; i < n; i++) {
		//		double rowSum = 0;
		//		for (int j = 0; j < n; j++) {
		//			scanf("%lf", &T[i][j]);
		//			rowSum += T[i][j];
		//		}
		//		if (!eq(1.0, rowSum)) {
		//			printf("rowsum(%d) = %.8lf\n", i, rowSum);
		//		}
		//	}

		//	vector<double> sol2 = getProb2();

		//	if (verify) {
		//		vector<double> sol1 = getProb1();
		//		for (int i = 0; i < n; i++)
		//			if (!eq(sol1[i], sol2[i])) {
		//				printf("Case %d\n", cc);
		//				for (int j = 0; j < n; j++)
		//					printf("sol1[%d] = %.8lf, sol2[%d] = %.8lf\n",
		//						j, sol1[j], j, sol2[j]);
		//				return 0;
		//			}
		//	}
		//	for (int i = 0; i < m; i++) {
		//		int song;
		//		scanf("%d", &song);
		//		printf("%s%.8lf", (i ? " " : ""), sol2[song]);
		//	}
		//	printf("\n");
		//}
	}
};
*/