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

	// Ʈ���� ����Ž�� ����� ����Ž�� ����� �־��� �� ����Ž�� ����� ����Ѵ�
	void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
		// Ʈ���� ���Ե� ����� ��
		int N = preorder.size();
		// ���� ���: �� �� Ʈ���� ���� ����
		if (preorder.empty()) return;
		// �� Ʈ���� ��Ʈ�� ���� Ž�� ����κ��� ���� �� �� �ִ�
		int root = preorder[0];
		// �� Ʈ���� ���� ����Ʈ���� ũ��� ���� Ž�� ������� ��Ʈ�� ��ġ�� ã�Ƽ� �� �� �ִ�
		int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
		// ������ ����Ʈ���� ũ��� �ڿ������� �˰� �ȴ�
		int R = N - 1 - L;

		// ���ʰ� ������ ����Ʈ���� ��ȸ ����� ���
		printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
		printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
		// ���� ��ȸ�̹Ƿ� ��Ʈ�� ���� �������� ����Ѵ�
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