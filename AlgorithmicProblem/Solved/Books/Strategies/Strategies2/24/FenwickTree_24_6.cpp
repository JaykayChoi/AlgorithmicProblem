#include<cassert>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// ���� Ʈ���� ����. ������ �迭 A[] �� �κ� ����
// ������ ������ �� �ֵ��� �Ѵ�. �ʱ�ȭ�ÿ��� A[] ��
// ���Ұ� ���� 0 �̶�� �����Ѵ�.
class FenwickTree_24_6
{
public:
	struct FenwickTree {
		vector<int> tree;
		FenwickTree(int n) : tree(n + 1) {}

		// A[0..pos] �� �κ� ���� ���Ѵ�
		int sum(int pos) {
			// �ε����� 1 ���� �����ϴ� ���̶�� ��������
			++pos;
			int ret = 0;
			while (pos > 0) {
				ret += tree[pos];
				// ���� ������ ã�� ���� ���� ��Ʈ�� �����
				pos &= (pos - 1);
			}
			return ret;
		}

		// A[pos] �� val �� ���Ѵ�
		void add(int pos, int val) {
			++pos;
			while (pos < tree.size()) {
				tree[pos] += val;
				pos += (pos & -pos);
			}
		}
	};

	int sub_main() {
		const int n = 100;
		vector<int> arr(n);
		FenwickTree tree(n);
		for (int it = 0; it < 100000; it++) {
			if (it % 2 == 0) {
				int a = rand() % n, b = rand() % n;
				if (a > b) swap(a, b);
				int arrsum = 0;
				for (int i = 0; i <= b - a; i++) arrsum += arr[a + i];
				int treesum = tree.sum(b) - tree.sum(a - 1);
				assert(arrsum == treesum);
			}
			else {
				int a = rand() % n, b = rand() % 100 - 50;
				arr[a] += b;
				tree.add(a, b);
			}
		}
		printf("all good.\n");
		return 0;
	}
};
