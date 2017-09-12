#include<cassert>
#include<vector>
#include<iostream>
#include<cstring>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include "Utils.h"
#include <ctime>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

//https://algospot.com/judge/problem/read/WILDCARD
//����
//
//���ϵ�ī��� �پ��� �ü������ ���� �̸��� �Ϻθ����� ���� �̸��� �����ϴ� ����̴�.���ϵ�ī�� ���ڿ��� �Ϲ����� ���ϸ�� ������, *�� ? �� ���� Ư�� ���ڸ� �����Ѵ�.
//
//���ϵ�ī�� ���ڿ��� �տ��� �� ���ھ� ���ϸ�� ���ؼ�, ��� ���ڰ� ��ġ���� �� �ش� ���ϵ�ī�� ���ڿ��� ���ϸ�� ��ġ�ȴٰ� ����.��, ���ϵ�ī�� ���ڿ��� ���Ե� ? �� � ���ڿ� ���ص� ��ġ�Ѵٰ� �����ϸ�, *�� 0 ���� �̻��� � ���ڿ����� ��ġ�Ѵٰ� ����.
//
//���� ��� ���ϵ� ī�� he ? p �� ���ϸ� help ����, heap ���� ��ġ������, helpp ���� ��ġ���� �ʴ´�.���ϵ� ī�� *p* �� ���ϸ� help ����, papa ���� ��ġ������, hello ���� ��ġ���� �ʴ´�.
//
//���ϵ�ī�� ���ڿ��� �Բ� ���ϸ��� ������ �־��� ��, �� �� ��ġ�Ǵ� ���ϸ���� ã�Ƴ��� ���α׷��� �ۼ��Ͻÿ�.
//
//�Է�
//
//�Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� C(1 <= C <= 10) �� �־�����.�� �׽�Ʈ ���̽��� ù �ٿ��� ���ϵ�ī�� ���ڿ� W �� �־�����, �� ���� �ٿ��� ���ϸ��� �� N(1 <= N <= 50) �� �־�����.�� �� N �ٿ� �ϳ��� �� ���ϸ��� �־�����.���ϸ��� ���� ���� ���ĺ� ��ҹ��ڿ� ���ڸ����� �̷���� ������, ���ϵ�ī��� �� �ܿ� * �� ? �� ���� �� �ִ�.��� ���ڿ��� ���̴� 1 �̻� 100 �����̴�.
//
//���
//
//�� �׽�Ʈ ���̽����� �־��� ���ϵ�ī�忡 ��ġ�Ǵ� ���ϵ��� �̸��� �� �ٿ� �ϳ��� �ƽ�Ű �ڵ� ����(����, �빮��, �ҹ��� ��)��� ����Ѵ�.
//
//���� �Է�
//
//2
//he ? p
//3
//help
//heap
//helpp
//*p *
//3
//help
//papa
//hello
//���� ���
//
//heap
//help
//help
//papa

class WildCard_8_2
{
public:
	void Solve()
	{
		input();
	}
private:
	int problemsNumber;
	int cache[5001][5001];
	string W, S;

	void input()
	{
		string filePath = "WildCard_8_2_Input.txt";
		queue<string> vInputLines = Utils::GetLine_InputFileAsQueue(filePath);

		problemsNumber = stoi(dequeue(vInputLines));

		while (vInputLines.size() > 0)
		{
			string patternW = dequeue(vInputLines);

			int stringNumber = stoi(dequeue(vInputLines));
			vector<string> ret;
			for (int i = 0; i < stringNumber; i++)
			{
				string str = dequeue(vInputLines);
				if (match(patternW, str))
					ret.push_back(str);
			}

			for each (string str in ret)
			{
				cout << str << endl;
			}

			system("pause");
		}
	}


	bool match(const string& w, const string& s) {
		// w[pos] �� s[pos] �� ���糪����
		int pos = 0;
		while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
			++pos;
		// �� �̻� ������ �� ������ �� while ���� �������� Ȯ���Ѵ�
		// 1. ���� ���� �����ؼ� ���� ���: ���ڿ��� ������� ��
		if (pos == w.size())
			return pos == s.size();
		// 2. * �� ������ ���� ���: * �� �� ���ڸ� �����ؾ� ���� ���ȣ���ϸ鼭 Ȯ���Ѵ�
		if (w[pos] == '*') {
			for (int skip = 0; pos + skip <= s.size(); ++skip)
				if (match(w.substr(pos + 1), s.substr(pos + skip)))
					return true;
			return false;
		}
		// 3. �̿��� ��쿡�� ��� �������� �ʴ´�
		return false;
	}

	// ���ϵ�ī�� ���� W[w..] �� ���ڿ� S[s..] �� �����Ǵ��� ���θ� ��ȯ�Ѵ�
	bool matchMemoized(int w, int s) {
		int& ret = cache[w][s];
		if (ret != -1) return ret;
		// W[w] �� S[s] �� ���糪����
		while (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
			++w;
			++s;
		}
		// �� �̻� ������ �� ������ �� while ���� �������� Ȯ���Ѵ�
		// 1. ���� ���� �����ؼ� ���� ���: ���ڿ��� ������� ��
		if (w == W.size()) return ret = (s == S.size());
		// 2. * �� ������ ���� ���: * �� �� ���ڸ� �����ؾ� ���� ���ȣ���ϸ鼭 Ȯ���Ѵ�
		if (W[w] == '*') {
			for (int skip = 0; skip + s <= S.size(); ++skip)
				if (matchMemoized(w + 1, s + skip))
					return ret = 1;
			return ret = 0;
		}
		// 3. �̿��� ��쿡�� ��� �������� �ʴ´�
		return ret = 0;
	}
	// ���ϵ�ī�� ���� W[w..] �� ���ڿ� S[s..] �� �����Ǵ��� ���θ� ��ȯ�Ѵ�
	bool matchMemoized2(int w, int s) {
		int& ret = cache[w][s];
		if (ret != -1) return ret;
		if (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s]))
			return ret = matchMemoized2(w + 1, s + 1);
		// �� �̻� ������ �� ������ �� while ���� �������� Ȯ���Ѵ�
		// 1. ���� ���� �����ؼ� ���� ���: ���ڿ��� ������� ��
		if (w == W.size()) return ret = (s == S.size());
		// 2. * �� ������ ���� ���: * �� �� ���ڸ� �����ؾ� ���� ���ȣ���ϸ鼭 Ȯ���Ѵ�
		if (W[w] == '*') {
			if (matchMemoized2(w + 1, s) ||
				(s < S.size() && matchMemoized2(w, s + 1)))
				return ret = 1;
		}
		// 3. �̿��� ��쿡�� ��� �������� �ʴ´�
		return ret = 0;
	}

	string dequeue(queue<string>& queue)
	{
		string ret = queue.front();
		queue.pop();
		return ret;
	}
};