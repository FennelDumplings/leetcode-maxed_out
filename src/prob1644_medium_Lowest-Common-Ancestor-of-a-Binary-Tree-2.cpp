// prob1644: Lowest Common Ancestor of a Binary Tree II

/*
 * https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return nullptr;
        bool flag_p = false, flag_q = false;
        TreeNode *cand = _postOeder(root, p, q, flag_p, flag_q);
        if(cand && flag_p && flag_q)
            return cand;
        else
            return nullptr;
    }

private:
    TreeNode* _postOeder(TreeNode* node, TreeNode* p, TreeNode* q, bool& flag_p, bool& flag_q)
    {
        TreeNode *left = nullptr, *right = nullptr;
        if(node -> left)
            left = _postOeder(node -> left, p, q, flag_p, flag_q);
        if(node -> right)
            right = _postOeder(node -> right, p, q, flag_p, flag_q);
        if(node == p || node == q)
        {
            if(node == p)
                flag_p = true;
            if(node == q)
                flag_q = true;
            return node;
        }
        if(left && right)
            return node;
        else if(left)
            return left;
        else if(right)
            return right;
        else
            return nullptr;
    }
};
