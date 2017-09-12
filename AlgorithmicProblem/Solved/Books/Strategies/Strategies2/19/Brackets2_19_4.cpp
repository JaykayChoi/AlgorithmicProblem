#include "Utils.h"
using namespace std;
using namespace Utils;
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define CLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

//https://algospot.com/judge/problem/read/BRACKETS2

class Brackets2_19_4
{
public:
	void Solve()
	{
		Input();
	}
private:
	void Input()
	{
		string filePath = "Brackets2_19_4_Input.txt";
		queue<string> inputs = GetLine_InputFileAsQueue(filePath);

		int problems = stoi(Dequeue(inputs));

		REP(i, problems)
		{
			string str = Dequeue(inputs);
			cout << wellMatched(str) << endl;
		}
	}

	bool wellMatched(const string& formula)
	{
		//여는 괄호 문자들과 닫는 괄호 문자들
		const string opening("({["), closing(")}]");

		//이미 열린 괄호들을 순서대로 담는 스택
		stack<char> openStack;

		REP(i, formula.sz)
		{
			//여는 괄호인지 닫는 괄호인지 확인
			if (opening.find(formula[i]) != -1)
			{
				//여는 괄호라면 무조건 스택에 집어넣는다.
				openStack.push(formula[i]);
			}
			else
			{
				//이 외의 경우 스택 맨 위의 문자와 맞춰보자
				//스택이 비어 있는 경우에는 실패
				if (openStack.empty())
					return false;

				//서로 짝이 맞지 않아도 실패
				if (opening.find(openStack.top()) != closing.find(formula[i]))
					return false;

				//짝을 맞춘 괄호는 스택에서 뺀다
				openStack.pop();
			}
		}
		return openStack.empty();
	}
};
