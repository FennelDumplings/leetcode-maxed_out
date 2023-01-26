// prob129: Sum Root to Leaf Numbers

/*
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
 * Find the total sum of all root-to-leaf numbers.
 * Note: A leaf is a node with no children.
 */

#include "include/Node.h"

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        int result = 0;
        int cur = 0;
        _preOrder(root, result, cur);
        return result;
    }

private:
    void _preOrder(TreeNode* root, int& result, int cur)
    {
        // 调用方保证 root 合法
        cur = cur * 10 + (root -> val);

        if(!(root -> left) && !(root -> right))
        {
            result += cur;
            return;
        }

        if(root -> left)
            _preOrder(root -> left, result, cur);
        if(root -> right)
            _preOrder(root -> right, result, cur);
    }
};
