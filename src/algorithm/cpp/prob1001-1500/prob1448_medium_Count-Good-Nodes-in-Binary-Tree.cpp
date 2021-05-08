// prob1448: Count Good Nodes in Binary Tree

/*
 * https://leetcode-cn.com/problems/count-good-nodes-in-binary-tree/
 */

#include "include/Node.h"

class Solution {
public:
    int goodNodes(TreeNode* root) {
        int ans = 0;
        _preOrder(root, -1e5, ans);
        return ans;
    }

private:
    void _preOrder(TreeNode* node, int max_val, int& ans)
    {
        if(node -> val >= max_val)
        {
            ++ans;
            max_val = node -> val;
        }
        if(node -> left)
            _preOrder(node -> left, max_val, ans);
        if(node -> right)
            _preOrder(node -> right, max_val, ans);
    }
};
