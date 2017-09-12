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

//https://algospot.com/judge/problem/read/FORTRESS

class Fortress_21_5
{
public:

private:
	// �Է� ������
	int n, y[100], x[100], radius[100];

	// x^2 �� ��ȯ�Ѵ�
	int sqr(int x) { return x*x; }

	// �� ���� a, b �� �߽��� ���� �Ÿ��� ������ ��ȯ�Ѵ�
	int sqrdist(int a, int b) { return sqr(y[a] - y[b]) + sqr(x[a] - x[b]); }

	// ���� a �� ���� b �� �����ϴ��� Ȯ���Ѵ�.
	bool encloses(int a, int b) {
		return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
	}

	// Ʈ���� ��Ʈ�� �� �ܼ����� ��ȣ�� ã�´�
	int getRoot() {
		for (int i = 0; i < n; i++) {
			bool isRoot = true;
			for (int j = 0; j < n; j++)
				if (i != j && encloses(j, i)) {
					isRoot = false;
					break;
				}
			if (isRoot)
				return i;
		}
		return -1;
	}

	// "����" Ʈ������ parent �� child �� �θ����� Ȯ���Ѵ�.
	// parent �� child �� �� ���� �����ؾ� �Ѵ�.
	bool isChild(int parent, int child) {
		if (!encloses(parent, child)) return false;
		for (int i = 0; i < n; i++)
			if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
				return false;
		return true;
	}

	struct TreeNode {
		vector<TreeNode*> children;
	};

	// root ������ ��Ʈ�� �ϴ� Ʈ���� �����Ѵ�
	TreeNode* getTree(int root) {
		TreeNode* ret = new TreeNode();
		for (int ch = 0; ch < n; ++ch)
			if (isChild(root, ch))
				ret->children.push_back(getTree(ch));
		return ret;
	}

	int longest;

	// root �� ��Ʈ�� �ϴ� ����Ʈ���� ���̸� ��ȯ�Ѵ�
	int depth(TreeNode* root) {
		// �� �ڽ��� ��Ʈ�� �ϴ� ����Ʈ���� ���̸� ����Ѵ�
		vector<int> heights;
		for (int i = 0; i < root->children.size(); ++i)
			heights.push_back(depth(root->children[i]));
		// ���� �ڽ��� �ϳ��� ���ٸ� 0 �� ��ȯ�Ѵ�
		if (heights.empty()) return 0;
		sort(heights.begin(), heights.end());
		// root �� �ֻ��� ���� �ϴ� ��θ� �������
		if (heights.size() >= 2)
			longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
		// Ʈ���� ���̴� ����Ʈ�� ������ �ִ밪�� 1 �� ���� ����Ѵ�
		return heights.back() + 1;
	}

	int solve() {
		// �켱 �ܼ����� ã�� �� ������ ��Ʈ�� �ϴ� Ʈ���� �����Ѵ�
		TreeNode* tree = getTree(getRoot());
		longest = 0;
		return max(longest, depth(tree));
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> n;
			for (int i = 0; i < n; i++)
				cin >> x[i] >> y[i] >> radius[i];
			cout << solve() << endl;
		}
	}
};