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
//문제
//
//와일드카드는 다양한 운영체제에서 파일 이름의 일부만으로 파일 이름을 지정하는 방법이다.와일드카드 문자열은 일반적인 파일명과 같지만, *나 ? 와 같은 특수 문자를 포함한다.
//
//와일드카드 문자열을 앞에서 한 글자씩 파일명과 비교해서, 모든 글자가 일치했을 때 해당 와일드카드 문자열이 파일명과 매치된다고 하자.단, 와일드카드 문자열에 포함된 ? 는 어떤 글자와 비교해도 일치한다고 가정하며, *는 0 글자 이상의 어떤 문자열에도 일치한다고 본다.
//
//예를 들어 와일드 카드 he ? p 는 파일명 help 에도, heap 에도 매치되지만, helpp 에는 매치되지 않는다.와일드 카드 *p* 는 파일명 help 에도, papa 에도 매치되지만, hello 에는 매치되지 않는다.
//
//와일드카드 문자열과 함께 파일명의 집합이 주어질 때, 그 중 매치되는 파일명들을 찾아내는 프로그램을 작성하시오.
//
//입력
//
//입력의 첫 줄에는 테스트 케이스의 수 C(1 <= C <= 10) 가 주어진다.각 테스트 케이스의 첫 줄에는 와일드카드 문자열 W 가 주어지며, 그 다음 줄에는 파일명의 수 N(1 <= N <= 50) 이 주어진다.그 후 N 줄에 하나씩 각 파일명이 주어진다.파일명은 공백 없이 알파벳 대소문자와 숫자만으로 이루어져 있으며, 와일드카드는 그 외에 * 와 ? 를 가질 수 있다.모든 문자열의 길이는 1 이상 100 이하이다.
//
//출력
//
//각 테스트 케이스마다 주어진 와일드카드에 매치되는 파일들의 이름을 한 줄에 하나씩 아스키 코드 순서(숫자, 대문자, 소문자 순)대로 출력한다.
//
//예제 입력
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
//예제 출력
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
		// w[pos] 와 s[pos] 를 맞춰나간다
		int pos = 0;
		while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
			++pos;
		// 더 이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다
		// 1. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
		if (pos == w.size())
			return pos == s.size();
		// 2. * 를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀호출하면서 확인한다
		if (w[pos] == '*') {
			for (int skip = 0; pos + skip <= s.size(); ++skip)
				if (match(w.substr(pos + 1), s.substr(pos + skip)))
					return true;
			return false;
		}
		// 3. 이외의 경우에는 모두 대응되지 않는다
		return false;
	}

	// 와일드카드 패턴 W[w..] 가 문자열 S[s..] 에 대응되는지 여부를 반환한다
	bool matchMemoized(int w, int s) {
		int& ret = cache[w][s];
		if (ret != -1) return ret;
		// W[w] 와 S[s] 를 맞춰나간다
		while (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
			++w;
			++s;
		}
		// 더 이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다
		// 1. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
		if (w == W.size()) return ret = (s == S.size());
		// 2. * 를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀호출하면서 확인한다
		if (W[w] == '*') {
			for (int skip = 0; skip + s <= S.size(); ++skip)
				if (matchMemoized(w + 1, s + skip))
					return ret = 1;
			return ret = 0;
		}
		// 3. 이외의 경우에는 모두 대응되지 않는다
		return ret = 0;
	}
	// 와일드카드 패턴 W[w..] 가 문자열 S[s..] 에 대응되는지 여부를 반환한다
	bool matchMemoized2(int w, int s) {
		int& ret = cache[w][s];
		if (ret != -1) return ret;
		if (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s]))
			return ret = matchMemoized2(w + 1, s + 1);
		// 더 이상 대응할 수 없으면 왜 while 문이 끝났는지 확인한다
		// 1. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
		if (w == W.size()) return ret = (s == S.size());
		// 2. * 를 만나서 끝난 경우: * 에 몇 글자를 대응해야 할지 재귀호출하면서 확인한다
		if (W[w] == '*') {
			if (matchMemoized2(w + 1, s) ||
				(s < S.size() && matchMemoized2(w, s + 1)))
				return ret = 1;
		}
		// 3. 이외의 경우에는 모두 대응되지 않는다
		return ret = 0;
	}

	string dequeue(queue<string>& queue)
	{
		string ret = queue.front();
		queue.pop();
		return ret;
	}
};