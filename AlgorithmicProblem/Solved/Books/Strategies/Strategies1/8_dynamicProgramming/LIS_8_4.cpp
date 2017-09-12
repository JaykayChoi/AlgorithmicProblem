#include<cstring>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//https://algospot.com/judge/problem/read/LIS

int lis(const vector<int>& A) {
	// ���� ���: A �� �� ��� ���� ��
	if (A.empty()) return 0;
	int ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		vector<int> B;
		for (int j = i + 1; j < A.size(); ++j)
			if (A[i] < A[j])
				B.push_back(A[j]);
		ret = max(ret, 1 + lis(B));
	}
	return ret;
}

int n;
int cache[101], S[100], choices[101];

// S[start] ���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�
int lis2(int start) {
	int& ret = cache[start];
	if (ret != -1) return ret;
	// �׻� S[start] �� �ֱ� ������ ���̴� ���� 1
	ret = 1;
	for (int next = start + 1; next < n; ++next)
		if (S[start] < S[next])
			ret = max(ret, lis2(next) + 1);
	return ret;
}

// S[start] ���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�
int lis3(int start) {
	int& ret = cache[start + 1];
	if (ret != -1) return ret;
	// �׻� S[start] �� �ֱ� ������ ���̴� ���� 1
	ret = 1;
	for (int next = start + 1; next < n; ++next)
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next) + 1);
	return ret;
}

// S[start] ���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�
int lis4(int start) {
	int& ret = cache[start + 1];
	if (ret != -1) return ret;
	// �׻� S[start] �� �ֱ� ������ ���̴� ���� 1
	ret = 1;
	int bestNext = -1;
	for (int next = start + 1; next < n; ++next)
		if (start == -1 || S[start] < S[next]) {
			int cand = lis4(next) + 1;
			if (cand > ret) {
				ret = cand;
				bestNext = next;
			}
		}
	choices[start + 1] = bestNext;
	return ret;
}

// S[start] ���� �����ϴ� LIS �� seq �� �����Ѵ�
void reconstruct(int start, vector<int>& seq) {
	if (start != -1) seq.push_back(S[start]);
	int next = choices[start + 1];
	if (next != -1) reconstruct(next, seq);
}

int submain() {
	int cases;
	cin >> cases;
	for (int cc = 0; cc < cases; ++cc) {
		cin >> n;
		vector<int> A(n);
		for (int i = 0; i < n; i++) {
			cin >> A[i];
			S[i] = A[i];
		}
		memset(cache, -1, sizeof(cache));
		cout << lis4(-1) - 1 << endl;
		vector<int> seq;
		reconstruct(-1, seq);
		for (int i = 0; i < seq.size(); ++i)
			cout << seq[i] << " ";
		cout << endl;

	}
}

