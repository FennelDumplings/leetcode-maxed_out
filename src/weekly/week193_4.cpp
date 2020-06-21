// 20200614
// 4. 树节点的第 K 个祖先

/*
 * 给你一棵树，树上有 n 个节点，按从 0 到 n-1 编号。树以父节点数组的形式给出，在父节点数组中的元素 parent[i] 是节点 i 的父节点。树的根节点是编号为 0 的节点。
 *
 * 请你设计并实现 getKthAncestor(int node, int k) 函数，函数返回节点 node 的第 k 个祖先节点。如果不存在这样的祖先节点，返回 -1 。
 *
 * 树节点的第 k 个祖先节点是从该节点到根节点路径上的第 k 个节点。
 */

#include <vector>

using namespace std;


// node.ancestors[k] = node.fa.ancestors[k-1]
// node.ancestors[0] = node

struct Node
{
    int id;
    int fa;
    int h; // 根节点 h = 1
    vector<int> ancestors;
    Node(int id, int fa, int h):id(id),fa(fa),h(h)
    {
        ancestors = vector<int>(h, -1); // k = 0 ~ h-1
        ancestors[0] = id;
    }
    Node()
    {
        id = -1, fa = -1, h = -1;
        ancestors = {};
    }
};

class TreeAncestor {
public:
    TreeAncestor(int n, vector<int>& parent) {
        tree = vector<Node>(n);
        for(int i = 0; i < n; ++i)
        {
            if(tree[i].id != -1)
                continue;
            build(tree, i, parent);
        }
    }

    int getKthAncestor(int node, int k) {
        // 1 <= k <= n
        Node &cur = tree[node];
        if(k >= cur.h)
            return -1;
        return _process(cur, k);
    }

private:
    vector<Node> tree;

    void build(vector<Node>& tree, int i, const vector<int>& parent)
    {
        if(i == -1)
            return;

        if(tree[i].id != -1)
            return;

        build(tree, parent[i], parent);

        tree[i].id = i;
        tree[i].fa = parent[i];
        if(parent[i] == -1)
            tree[i].h = 1;
        else
            tree[i].h = tree[tree[i].fa].h + 1;
        // tree[i].ancestors = vector<int>(tree[i].h, -1);
        // tree[i].ancestors[0] = tree[i].id;
        // for(int k = 1; k < tree[i].h; ++k)
        // {
        //     tree[i].ancestors[k] = tree[tree[i].fa].ancestors[k - 1];
        // }
    }

    int _process(Node& cur, int k)
    {
        // cur.ancestors[k];
        if(cur.ancestors.empty())
        {
            cur.ancestors = vector<int>(cur.h, -1);
            cur.ancestors[0] = cur.id;
        }
        if(cur.ancestors[k] != -1)
            return cur.ancestors[k];

        cur.ancestors[k] = _process(tree[cur.fa], k - 1);
        return cur.ancestors[k];
    }
};
