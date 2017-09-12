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

//https://algospot.com/judge/problem/read/TRAVERSAL

class Traversal_21_3
{
public:

private:
	vector<int> slice(const vector<int>& v, int a, int b) {
		return vector<int>(v.begin() + a, v.begin() + b);
	}

	// 트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력한다
	void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
		// 트리에 포함된 노드의 수
		int N = preorder.size();
		// 기저 사례: 텅 빈 트리면 곧장 종료
		if (preorder.empty()) return;
		// 이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다
		int root = preorder[0];
		// 이 트리의 왼쪽 서브트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다
		int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
		// 오른쪽 서브트리의 크기는 자연스럽게 알게 된다
		int R = N - 1 - L;

		// 왼쪽과 오른쪽 서브트리의 순회 결과를 출력
		printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
		printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
		// 후위 순회이므로 루트를 가장 마지막에 출력한다
		cout << root << ' ';
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			int n;
			cin >> n;
			vector<int> preorder(n), inorder(n);
			for (int i = 0; i < n; i++) cin >> preorder[i];
			for (int i = 0; i < n; i++) cin >> inorder[i];

			printPostOrder(preorder, inorder);
			cout << endl;
		}
	}
};