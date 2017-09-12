#include "Utils.h"
using namespace std;
using namespace Utils;

//����
//
//� ���� �������� 0�� �̻��� ���ڸ� ����� �� ������ �κ� ����(subsequence) �� ���� �� �ִ�.���� ��� 10 7 4 9 �� �κ� �������� 7 4 9, 10 4, 10 9 ���� �ִ�.��, 10 4 7 �� ���� ������ ������ �ٸ��Ƿ� 10 7 4 9 �� �κ� ������ �ƴϴ�.
//
//� �κ� ������ _���� ����_�� �� �� �κ� ������ ���� �κ� ����(increasing subsequence) ��� �ϸ�, �� �� ���� �� ���� �ִ� ���� �κ� ����(LIS, longest increasing subsequence) ��� �Ѵ�.���� ���, 5 20 21 22 8 9 10 �� �ִ� ���� �κ� ������ 5 8 9 10 �̴�.
//
//� �������� LIS �� �� �� �̻� ���� �� �ִ�.���� ���, 4 5 6 1 2 3 �� LIS �� �� ���� �ִ�.
//
//��� ���ڰ� ���� �ٸ�(�ߺ� ���ڰ� ����) ������ �־��� ��, �� ������ LIS �� ���� ������� �� �տ��� k��° �ִ� LIS �� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(<= 50) �� �־�����.�� �׽�Ʈ ���̽��� ù �ٿ��� ������ ���Ե� ������ �� N(<= 500) �� K �� �־�����.K �� 32��Ʈ ��ȣ �ִ� ������ ������ �� �ִ�.�� ���� �ٿ� N���� ������ ������ �־�����.�� ������ 1 �̻� 100, 000 �����̸�, ���� ���� �� �� �������� �ʴ´�.
//
//�־��� ������ LIS �� �ּ� K �� �ִٰ� �����ص� ����.
//
//���
//
//�� �׽�Ʈ���̽����� �� ���� ����Ѵ�.ù �ٿ��� LIS �� ���� L �� ����ϰ�, �� ���� �ٿ� L ���� ������ K��° LIS �� ����Ѵ�.
//
//���� �Է�
//
//3
//9 2
//1 9 7 4 2 6 3 11 10
//8 4
//2 1 4 3 6 5 8 7
//8 2
//5 6 7 8 1 2 3 4
//���� ���
//
//4
//1 2 3 11
//4
//1 3 6 8
//4
//5 6 7 8
const int MAX = 2000000000 + 10;
class KLIS_9_8
{
public:


private:
	
	int n;
	int cacheLen[501], cacheCnt[501], S[500];

	// S[start] ���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�
	int lis(int start) {
		// �޸������̼�
		int& ret = cacheLen[start + 1];
		if (ret != -1) return ret;
		// �׻� S[start] �� �ֱ� ������ ���̴� ���� 1
		ret = 1;
		for (int next = start + 1; next < n; ++next)
			if (start == -1 || S[start] < S[next])
				ret = max(ret, lis(next) + 1);
		return ret;
	}

	// S[start] ���� �����ϴ� �ִ� ���� �κ� ������ ���� ��ȯ�Ѵ�
	int count(int start) {
		// ���� ���: LIS �� ���̰� 1 �� ���
		if (lis(start) == 1) return 1;
		// �޸������̼�
		int& ret = cacheCnt[start + 1];
		if (ret != -1) return ret;
		ret = 0;
		for (int next = start + 1; next < n; ++next) {
			if ((start == -1 || S[start] < S[next]) &&
				lis(start) == lis(next) + 1)
				ret = min<long long>(MAX, (long long)ret + count(next));
		}
		return ret;
	}

	// S[start] ���� �����ϴ� LIS �� ���� ������ skip �� �ǳʶ� ������
	// lis �� �����Ѵ�
	void reconstruct(int start, int skip, vector<int>& lis) {
		// S[start] �� �׻� LIS �� ���Եȴ�
		if (start != -1) lis.push_back(S[start]);
		// �ڿ� �� �� �ִ� ���ڵ�� ��ġ�� ����� �����
		// (����, ������ ��ġ) �� ����� �ȴ�
		vector<pair<int, int> > followers;
		for (int next = start; next < n; next++)
			if ((start == -1 || S[start] < S[next]) &&
				lis[start] == lis[next] + 1)
				followers.push_back(make_pair(S[next], next));
		// ���� ũ�⺰�� �����Ѵ�
		sort(followers.begin(), followers.end());
		for (int i = 0; i < followers.size(); ++i) {
			// �� ���ڸ� �ڿ� �̾ ���� �� �ִ� LIS �� ������ ����
			int idx = followers[i].second;
			int cnt = count(idx);
			if (cnt <= skip)
				skip -= cnt;
			else {
				// ���� ���ڴ� S[idx] ���� �˾Ҵ�
				reconstruct(idx, skip, lis);
				break;
			}
		}
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int k;
			cin >> n >> k;
			for (int i = 0; i < n; i++) {
				cin >> S[i];
			}
			memset(cacheLen, -1, sizeof(cacheLen));
			memset(cacheCnt, -1, sizeof(cacheCnt));
			//cout << lis(-1)-1 << endl;
			//cout << count(-1) << endl;
			vector<int> kth;
			reconstruct(-1, k - 1, kth);
			cout << kth.size() << endl;
			for (int i = 0; i < kth.size(); i++) {
				if (i) cout << ' ';
				cout << kth[i];
			}
			cout << endl;
		}
	}
};