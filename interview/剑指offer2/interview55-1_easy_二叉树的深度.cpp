// interview55-1: 二叉树的深度

/*
 * https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof/
 */

#include "../../include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        int result = 0;
        _preOrder(root, 1, result);
        return result;
    }

private:
    void _preOrder(TreeNode* node, int deep, int& result)
    {
        if(!node -> left && !node -> right)
        {
            result = max(result, deep);
            return;
        }

        if(node -> left)
            _preOrder(node -> left, deep + 1, result);
        if(node -> right)
            _preOrder(node -> right, deep + 1, result);
    }
};
