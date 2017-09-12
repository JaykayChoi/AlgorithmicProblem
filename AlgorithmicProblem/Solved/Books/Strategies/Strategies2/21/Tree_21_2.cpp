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

class Tree_21_2
{
public:

private:
	struct TreeNode {
		string label; // 저장할 자료
		TreeNode* parent; // 부모 노드를 가리키는 포인터
		vector<TreeNode*> children; // 자손 노드들을 가리키는 포인터의 배열
	};

	// 주어진 트리의 각 노드에 저장된 정보를 모두 출력한다
	void printLabels(TreeNode* root) {
		// 루트에 저장된 정보를 출력한다
		cout << root->label << endl;
		// 각 자손들을 루트로 하는 서브트리를 재귀적으로 출력한다
		for (int i = 0; i < root->children.size(); ++i)
			printLabels(root->children[i]);
	}

	// root 를 루트로 하는 트리의 높이를 구한다
	int height(TreeNode* root) {
		int h = 0;
		for (int i = 0; i < root->children.size(); ++i)
			h = max(h, 1 + height(root->children[i]));
		return h;
	}
};