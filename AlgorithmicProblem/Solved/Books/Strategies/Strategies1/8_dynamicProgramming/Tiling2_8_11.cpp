#include "Utils.h"
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

//2xn ũ���� �簢���� 2x1 ũ���� �簢������ ��ƴ���� ä��� ����� ���� ���ϴ� ���α׷��� �ۼ��ϼ���.
//
//���� ��� n = 5��� �ϸ� ���� �׸��� ���� ���� ������ ����� �ֽ��ϴ�.
//
//����� ���� n�� Ŀ���� ���� Ŀ�� �� �����Ƿ�, 1000000007���� ���� ���� ��� ����ϼ���.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� ��(C <= 50)�� �־����ϴ�.���� C�ٿ� ���� 1���� �ڿ����� n(1 <= n <= 100)�� �־����ϴ�.
//
//���
//
//�� �׽�Ʈ ���̽����� �� �ٿ� ����� ���� 1000000007�� ���� �������� ����մϴ�.
//
//���� �Է�
//
//3
//1
//5
//100
//���� ���
//
//1
//8
//782204094

class Tiling2_8_11
{
public:


private:
	const int MOD = 1000000007;
	int cache[101];

	void Input()
	{
		memset(cache, -1, sizeof(cache));
	}

	// 2*width ũ���� �簢���� ä��� ����� ���� MOD �� ���� �������� ��ȯ�Ѵ�
	int tiling(int width) {
		// ���� ���: width �� 1 ������ ��
		if (width <= 1) return 1;
		// �޸������̼�
		int& ret = cache[width];
		if (ret != -1) return ret;
		return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
	}
};
