// prob1302: Deepest Leaves Sum

/*
 * https://leetcode-cn.com/problems/deepest-leaves-sum/
 */

#include "include/Node.h"

class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        int max_deep = 1;
        _preOrder(root, 1, max_deep, ans);
        return ans;
    }

private:
    void _preOrder(TreeNode* node, int deep, int& max_deep, int& ans)
    {
        if(deep == max_deep)
            ans += node -> val;
        else if(deep > max_deep)
        {
            max_deep = deep;
            ans = node -> val;
        }
        if(node -> left)
            _preOrder(node -> left, deep + 1, max_deep, ans);
        if(node -> right)
            _preOrder(node -> right, deep + 1, max_deep, ans);
    }
};
