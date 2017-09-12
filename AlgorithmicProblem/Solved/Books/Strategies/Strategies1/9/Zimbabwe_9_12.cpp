#include "Utils.h"
using namespace std;
using namespace Utils;

//��ȹ ������ ���з� ���� �ְ��� ���÷��̼��� �ڶ��ϰ� �� ���� ���� ������������� �Ϸ� �߿��� ������ ��� ������ ������ ������ ������ �ǽð����� �ٲ�� �մϴ�.����������� ���� ū ������ ��Ʈ������ �׷��� ���� ���� �� ĭ�� ���� �ִ� �������� �ٿ����� ��� ������ ������ ����(��Ȯ���� ������� �޷��� ��ġ�� �߶��Կ� ����) �ǽð����� ���ڰ� ũ�� ���� �ö�ƽ ���� �� ĭ�� ���� ����ϴ�.���� ��� ��� �� ���� 35�� ������� �޷���� �ϸ�, 3�� ���� �� �� ��, 5�� ���� �� �� ��, 0�� ���� �� ���� ���� ��ĭ�� ������� ����� ������.
//
//������ ��Ʈ���� �Ƹ�����Ʈ�� �ϴ� �����̴� ��� �� ����� �մ��� �¾ҽ��ϴ�.�� �մ��� �Ʊ� �� ���� ����� ȯ���ϰڴٰ� ���ƿԴµ�, �������� �Ҿ�������� ����� �󸶿� ������� ��������� ���Ѵٰ� �ϴ±���.��� ���� �� ���� �� �� �� �ö��� ������ �����ǿ� ���� ������ �̹� �ٲ� ���Դϴ�.������ �����̴� �� ������ ����մϴ�.
//
//�������� ��� ������ �ö��� ��, �����̴� �����ǿ� ���� �ö�ƽ ���� ������ �ٲ���ϴ�.�ٸ� �ö�ƽ ���� �������ų� �ִ� �ö�ƽ ���� �� ���� �����ٴ� ������.
//������ ��� ������ ���鼭 '�� �̰Ÿ� ��Ȯ�� ���� m���� �� �� �ֱ���' ��� �����߽��ϴ�.���� ������ ��� ������ m�� ��������ϴ�. (���� ���ݵ� �̹� �ö��� ������ �̰� ������ ��� ������ ����� ���� �����ϴ�)
//���� ��� ���� e�� m�� �־��� �� ������ ���� ��� ������ �� ������ �ִ��� ����ϴ� ���α׷��� �ۼ��ϼ���.���� ��� ������ e ���� �׻� �۾ƾ� �մϴ�.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� c(c <= 50) �� �־����ϴ�.�� �� c�ٿ� ���� 2���� �ڿ��� e�� m(1 <= e <= 10 ^ 14, 2 <= m <= 20)�� �־����ϴ�.���� ��� ������ 0���� �������� ������, ���� ��� ������ 0���� ������ �� �ֽ��ϴ�.
//
//���
//
//�� �׽�Ʈ ���̽����� �� �ٿ� ������ ������ ���� 1, 000, 000, 007 �� ���� �������� ����ϼ���.
//
//���� �Է�
//
//4
//321 3
//123 3
//422 2
//12738173912 7
//���� ���
//
//5
//0
//2
//11033

const int MOD = 1000000007;

class Zimbabwe_9_12
{
public:

private:
#pragma region solve
	// digits: e �� �ڸ������� ������ ��
	string e, digits;
	int n, m;

	// e �� �ڸ����� ���� �� �ִ� ���ڵ��� ��� ����Ѵ�
	// price: ���ݱ��� ���� ����
	// taken: �� �ڸ����� ��� ����
	void generate(string price, bool taken[15]) {
		// ���� ���
		if (price.size() == n) {
			if (price < e && atoll(price.c_str()) % m == 0)
				cout << price << endl;
			return;
		}
		for (int i = 0; i < n; ++i)
			if (!taken[i] && (i == 0 || digits[i - 1] != digits[i] || taken[i - 1])) {
				taken[i] = true;
				generate(price + digits[i], taken);
				taken[i] = false;
			}
	}


	int cache[1 << 14][20][2];

	// ���� ������ �� �ڸ����� ä�������� �ִ�.
	// index: �̹��� ä�� �ڸ��� �ε���
	// taken: ���ݱ��� ����� �ڸ������� ����
	// mod: ���ݱ��� ���� ������ m �� ���� ������
	// less: ���ݱ��� ���� ������ �̹� e ���� ������ 1, �ƴϸ� 0
	int price(int index, int taken, int mod, int less) {
		// ���� ���
		if (index == n)
			return (less && mod == 0) ? 1 : 0;
		// �޸������̼�
		int& ret = cache[taken][mod][less];
		if (ret != -1) return ret;

		ret = 0;
		for (int next = 0; next < n; next++)
			if ((taken & (1 << next)) == 0) {
				// ���� ������ �� ���ݺ��� �׻� �۾ƾ߸� �Ѵ�
				if (!less && e[index] < digits[next])
					continue;
				// ���� ���ڴ� �� ���� �����Ѵ�
				if (next > 0 && digits[next - 1] == digits[next] && (taken & (1 << (next - 1))) == 0)
					continue;
				int nextTaken = taken | (1 << next);
				int nextMod = (mod * 10 + digits[next] - '0') % m;
				int nextLess = less || e[index] > digits[next];
				(ret += price(index + 1, nextTaken, nextMod, nextLess)) %= MOD;
			}
		return ret;
	}

	int brute(string price) {
		string digits = price;
		sort(digits.begin(), digits.end());
		int ret = 0;
		do {
			if (digits >= e) break;
			int rem = 0;
			for (int i = 0; i < digits.size(); i++)
				rem = (rem * 10 + digits[i] - '0') % m;
			if (rem == 0) ret++;
		} while (next_permutation(digits.begin(), digits.end()));
		printf("brute\n");
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> e >> m;
			n = e.size();
			digits = e;
			sort(digits.begin(), digits.end());
			bool taken[15] = { 0 };
			generate("", taken);
			memset(cache, -1, sizeof(cache));
			cout << price(0, 0, 0, 0) << endl;
			if (n <= 8) assert(brute(e) == price(0, 0, 0, 0));
		}
	}

#pragma endregion

};