#include "Utils.h"
using namespace std;
using namespace Utils;

//https://algospot.com/judge/problem/read/FENCE

class Fence_7_4
{
public:

private:
	// �� ������ ���̸� �����ϴ� �迭
	vector<int> h;

	// ������ ����� O(n) �ع�
	int solveStack() {
		// ���� �ִ� ���ڵ��� ��ġ���� �����Ѵ�
		stack<int> remaining;
		h.push_back(0);

		int ret = 0;
		for (int i = 0; i < h.size(); ++i) {
			// ���� �ִ� ���ڵ� �� ������ �� ���ڰ� h[i] ���� ���ٸ�
			// �� ������ �ִ� �簢���� i ���� ������.
			while (!remaining.empty() && h[remaining.top()] >= h[i]) {
				int j = remaining.top();
				remaining.pop();

				int width = -1;
				// j ��° ���� ���ʿ� ���ڰ� �ϳ��� �� ���� �ִ� ���,
				// left[j] = -1, �ƴ� ��� left[j] = ���� �ִ� ���� ��
				// ���� �����ʿ� �ִ� ������ ��ȣ �� �ȴ�.
				if (remaining.empty())
					width = i;
				else
					width = (i - remaining.top() - 1);
				ret = max(ret, h[j] * width);
			}
			remaining.push(i);
		}
		return ret;
	}

	// h[left..right] �������� ã�Ƴ� �� �ִ� ���� ū �簢���� ���̸� ��ȯ�Ѵ�
	int solve(int left, int right) {
		// ���� ���: ���ڰ� �ϳ��ۿ� ���� ���
		if (left == right) return h[left];

		// [left,mid], [mid+1,right] �� �� �������� ������ �����Ѵ�
		int mid = (left + right) / 2;
		// ������ ������ ��������
		int ret = max(solve(left, mid), solve(mid + 1, right));
		// �κ� ���� 3: �� �κп� ��� ��ġ�� �簢�� �� ���� ū ���� ã�´�.
		int lo = mid, hi = mid + 1;
		int height = min(h[lo], h[hi]);
		// [mid,mid+1] �� �����ϴ� �ʺ� 2�� �簢���� ����Ѵ�
		ret = max(ret, height * 2);
		// �簢���� �Է� ��ü�� ���� ������ Ȯ���� ������
		while (left < lo || hi < right) {
			// �׻� ���̰� �� ���� ������ Ȯ���Ѵ�
			if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
				++hi;
				height = min(height, h[hi]);
			}
			else {
				--lo;
				height = min(height, h[lo]);
			}
			// Ȯ���� �� �簢���� ����
			ret = max(ret, height * (hi - lo + 1));
		}
		return ret;
	}

	int n;
	// ������ ���̸� ���� �迭 h[] �� �־��� �� �簢���� �ִ� �ʺ� ��ȯ�Ѵ�
	int bruteForce(const vector<int>& h) {
		int ret = 0;
		int N = h.size();
		for (int left = 0; left < N; left++) {
			int minHeight = h[left];
			for (int right = left; right < N; right++) {
				minHeight = min(minHeight, h[right]);
				ret = max(ret, (right - left + 1) * minHeight);
			}
		}
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		while (cases--) {
			cin >> n;
			h.resize(n);
			for (int i = 0; i < n; i++) {
				cin >> h[i];
			}
			//cout << bruteForce(h) << endl;
			// int sol1 = solve(0, n-1);
			int sol2 = solveStack();
			// if(sol1 != sol2) {

			// 	printf("solve %d solveStack %d\n", sol1, sol2);
			// }
			// assert(sol1 == sol2);
			cout << sol2 << endl;
		}
	}
};