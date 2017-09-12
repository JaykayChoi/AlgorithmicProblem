#include "Utils.h"
using namespace std;
using namespace Utils;

//����
//
//����Ͽ� ����ؼ� �����ǿ��� ��� �ִ� ���п��� ��ȣ�� �Ǽ��� ���迡 ����ϴ� �����͸� �����ϰ� ���ҽ��ϴ�.���纻�� ���� �Ͷ� �̴�ζ�� �������� ���븦 �� ���� ���� ���� �ڸ��� ��, ���� ��ȣ�� �׷� ���� ���̴� �����͸� �����Ͽ� �������� �г븦 ���� ����� �մϴ�.�츮�� �����Ϳ� ���� �˰��ִ� ����, �����Ͱ� k���� ���ڿ� ������ �κ� ���ڿ��� �����ϸ�, ��� ���ĺ� �ҹ��ڷ� �����ȴٴ� ��� �ۿ� �����ϴ�. (� ���ڿ��� �κ� ���ڿ��� �ش� ���ڿ��� ���ӵ� �Ϻκ��Դϴ�.)
//
//�־��� ���ڿ� �������� ��� �κ� ���ڿ��� �����ϴ� ���ڿ� �� ���� ª�� ���� ����ϴ� ���α׷��� �ۼ��ϼ���.���� �̿� ���� ���ڿ��� �����̶�� �ƹ� ���ڿ��̳� ����ϸ� �˴ϴ�.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(C��50)�� �־����ϴ�.�� �׽�Ʈ ���̽��� ù �ٿ��� �κ� ���ڿ��� �� k(1��k��15)�� �־�����, ���� k�ٿ� ���ĺ� �ҹ��ڷθ� ������ ���ڿ� ������ �־����ϴ�.�� ���ڿ� ������ ���̴� 1 �̻� 40 �����Դϴ�.
//
//���
//
//�� �׽�Ʈ ���̽����� �� �ٷ�, �ش� ���ڿ��� ��� �����ϴ� ���� ª�� ���ڿ� �� �ϳ��� ����մϴ�.
//
//���� �Է�
//
//3
//3
//geo
//oji
//jing
//2
//world
//hello
//3
//abrac
//cadabra
//dabr
//���� ���
//
//geojing
//helloworld
//cadabrac

const int MAX_N = 16;

class Restore_9_14
{
public:

private:
	int k;
	string word[MAX_N];
	int cache[MAX_N][1 << MAX_N];
	int overlap[MAX_N][MAX_N];
	int restore(int last, int used) {
		// ���� ���
		if (used == (1 << k) - 1) return 0;
		// �޸������̼�
		int& ret = cache[last][used];
		if (ret != -1) return ret;
		ret = 0;
		for (int next = 0; next < k; ++next)
			if ((used & (1 << next)) == 0) {
				int cand = overlap[last][next] +
					restore(next, used + (1 << next));
				ret = max(ret, cand);
			}
		return ret;
	}

	string reconstruct(int last, int used) {
		// ���� ���
		if (used == (1 << k) - 1) return "";
		for (int next = 0; next < k; ++next)
			if ((used & (1 << next)) == 0 &&
				restore(last, used) ==
				overlap[last][next] + restore(next, used + (1 << next)))
				return word[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next));
		return "_oops_";
	}

	int getOverlap(const string& a, const string& b) {
		for (int len = min(a.size(), b.size()); len > 0; --len) {
			if (a.substr(a.size() - len) == b.substr(0, len))
				return len;
		}
		return 0;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> k;
			for (int i = 0; i < k; i++) cin >> word[i];
			memset(cache, -1, sizeof(cache));
			while (true) {
				bool removed = false;
				for (int i = 0; i < k && !removed; i++)
					for (int j = 0; j < k; j++)
						if (i != j && word[i].find(word[j]) != -1) {
							word[j] = word[k - 1];
							--k;
							removed = true;
						}

				if (!removed) break;
			}
			word[k] = "";
			sort(word, word + k);
			for (int i = 0; i <= k; i++)
				for (int j = 0; j <= k; j++)
					overlap[i][j] = getOverlap(word[i], word[j]);
			restore(k, 0);
			cout << reconstruct(k, 0) << endl;
		}
	}
};