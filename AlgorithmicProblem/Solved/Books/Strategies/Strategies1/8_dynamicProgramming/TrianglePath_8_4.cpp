#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include <algorithm>
using namespace std;

const int MAX_NUMBER = 10;
int n, numbers[100][100];
int cache[100][100][MAX_NUMBER * 100 + 1];
int cache2[100][100];

// (0,0) ���� (y,x) ���� �������� �κ� ����� ���� sum �� ��
// �� ��θ� �� �Ʒ��ٱ��� �̾ ���� �� �ִ� �ִ� ����� ����
// ��ȯ�Ѵ�
int path(int y, int x, int sum) {
	// ���� ���: �� �Ʒ� �ٱ��� �������� ���
	if (y == n - 1) return sum + numbers[y][x];

	// �޸������̼�
	int& ret = cache[y][x][sum];
	if (ret != -1) return ret;

	sum += numbers[y][x];
	return ret = max(path(y + 1, x + 1, sum), path(y + 1, x, sum));
}

// (y,x) ��ġ���� �� �Ʒ��ٱ��� �������鼭 ���� �� �ִ� �ִ� ��θ� ��ȯ�Ѵ�
int path2(int y, int x) {
	// ���� ���
	if (y == n - 1) return numbers[y][x];

	int& ret = cache2[y][x];
	if (ret != -1) return ret;
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + numbers[y][x];
}

int C[100][100];
int iterative() {
	// ���� ��ʸ� ����Ѵ�
	for (int x = 0; x < n; ++x)
		C[n - 1][x] = numbers[n - 1][x];
	// �ٸ� �κ��� ����Ѵ�
	for (int y = n - 2; y >= 0; --y)
		for (int x = 0; x < y + 1; ++x)
			C[y][x] = max(C[y + 1][x], C[y + 1][x + 1]) + numbers[y][x];
	return C[0][0];
}

int C2[2][5000];
int iterative2() {
	// ���� ��ʸ� ����Ѵ�
	for (int x = 0; x < n; ++x)
		C2[(n - 1) % 2][x] = numbers[n - 1][x];
	// �ٸ� �κ��� ����Ѵ�
	for (int y = n - 2; y >= 0; --y)
		for (int x = 0; x < y + 1; ++x)
			C2[y % 2][x] = max(C2[(y + 1) % 2][x], C2[(y + 1) % 2][x + 1]) + numbers[y][x];
	return C2[0][0];

}

int countCache[100][100];
// (y, x)���� �����ؼ� �� �Ʒ��ٱ��� �������� ��� �� �ִ� �����
// ������ ��ȯ�Ѵ�.
int count(int y, int x) {
	// ���� ���: �� �Ʒ��ٿ� ������ ���
	if (y == n - 1) return 1;
	// �޸������̼�
	int& ret = countCache[y][x];
	if (ret != -1) return ret;
	ret = 0;
	if (path2(y + 1, x + 1) >= path2(y + 1, x)) ret += count(y + 1, x + 1);
	if (path2(y + 1, x + 1) <= path2(y + 1, x)) ret += count(y + 1, x);
	return ret;
}

int submain() {
	int cases;
	cin >> cases;
	for (int cc = 0; cc < cases; ++cc) {
		memset(cache, -1, sizeof(cache));
		memset(cache2, -1, sizeof(cache2));
		memset(countCache, -1, sizeof(countCache));
		cin >> n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i + 1; j++) {
				cin >> numbers[i][j];
			}
		}
		// cout << path2(0, 0) << endl;
		cout << count(0, 0) << endl;

		// cout << iterative() << endl;
		// cout << iterative2() << endl;

	}
}

