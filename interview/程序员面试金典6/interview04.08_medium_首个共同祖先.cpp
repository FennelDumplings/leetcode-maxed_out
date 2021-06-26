// interview04.08: 首个共同祖先

/*
 * https://leetcode-cn.com/problems/first-common-ancestor-lcci/
 */

#include "../../include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return nullptr;
        TreeNode *lca = nullptr;
        _postOrder(root, p, q, lca);
        return lca;
    }

private:
    using PBB = pair<bool, bool>;
    PBB _postOrder(TreeNode* node, const TreeNode* p, const TreeNode* q, TreeNode*& lca)
    {
        PBB result(false, false);
        PBB left(false, false);
        PBB right(false, false);
        if(node -> left)
        {
            left = _postOrder(node -> left, p, q, lca);
            if(lca) return left;
        }
        if(node -> right)
        {
            right = _postOrder(node -> right, p, q, lca);
            if(lca) return right;
        }
        result.first = left.first || right.first;
        result.second = left.second || right.second;
        if(node == p)
            result.first = true;
        if(node == q)
            result.second = true;
        if(!lca && result.first && result.second)
            lca = node;
        return result;
    }
};
