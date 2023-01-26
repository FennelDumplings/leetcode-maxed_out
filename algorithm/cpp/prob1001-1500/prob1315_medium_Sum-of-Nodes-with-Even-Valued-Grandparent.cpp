// prob1315: Sum of Nodes with Even-Valued Grandparent

/*
 * https://leetcode-cn.com/problems/sum-of-nodes-with-even-valued-grandparent/
 */

#include "include/Node.h"

class Solution {
public:
    int sumEvenGrandparent(TreeNode* root) {
        int ans = 0;
        _preOrder(root, nullptr, nullptr, ans);
        return ans;
    }

private:
    void _preOrder(TreeNode* node, TreeNode* fa, TreeNode* grandfa, int& ans)
    {
        if(grandfa && (grandfa -> val & 1) == 0)
            ans += node -> val;
        if(node -> left)
            _preOrder(node -> left, node, fa, ans);
        if(node -> right)
            _preOrder(node -> right, node, fa, ans);
    }
};
