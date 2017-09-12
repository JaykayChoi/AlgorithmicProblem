#include "Utils.h"
using namespace std;

const int MAX_N = 100;
class SnailClimb_8_11
{
public:


private:
	int n, m;
	int cache[101][101];


	// days �� ���� climbed ���͸� ���ö� �Դٰ� �� ��,
	// m �� ������ n���͸� ���ö� �� �ִ� ����� ��
	int climb(int days, int climbed) {
		// ���� ���: m���� ��� ���� ���
		if (days == m) return climbed >= n ? 1 : 0;
		// �޸������̼�
		int& ret = cache[days][climbed];
		if (ret != -1) return ret;
		return ret = climb(days + 1, climbed + 1) + climb(days + 1, climbed + 2);
	}

	double cache2[MAX_N][MAX_N + 1];
	// days �� ���� climbed ���͸� ���ö� �Դٰ� �� ��,
	// m �� ������ n���͸� ���ö� �� ���� Ȯ��
	double climb2(int days, int climbed) {
		// ���� ���: m���� ��� ���� ���
		if (days == m) return climbed >= n ? 1 : 0;
		// �޸������̼�
		double& ret = cache2[days][climbed];
		if (ret >= 0) return ret;
		return ret = 0.5 * climb2(days + 1, climbed + 1) + 0.5 * climb2(days + 1, climbed + 2);
	}
};
