// interview67: 二叉搜索树的最近公共祖先

/*
 * https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-zui-jin-gong-gong-zu-xian-lcof/
 */

#include "../../include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int l = min(p -> val, q -> val), r = max(p -> val, q -> val);
        return dfs(root, l, r);
    }

private:
    TreeNode* dfs(TreeNode* node, int l, int r)
    {
        int cur = node -> val;
        if(cur >= l && cur <= r)
            return node;
        if(cur > r)
            return dfs(node -> left, l, r);
        else
            return dfs(node -> right, l, r);
    }
};
