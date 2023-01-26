// prob112: Path Sum

/*
 * Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
 * Note: A leaf is a node with no children.
 */

#include "include/Node.h"

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        int cur_sum = root -> val;
        return _preOrder(root, cur_sum, sum);
    }

private:
    bool _preOrder(TreeNode* root, int& sum, int target)
    {
        // 调用方保证 root 合法

        if(!(root -> left ) && !(root -> right))
            return sum == target;

        bool result = false;
        if(root -> left)
        {
            sum += root -> left -> val;
            result = result || _preOrder(root -> left, sum, target);
            sum -= root -> left -> val;
        }
        if(result) return true;
        if(root -> right)
        {
            sum += root -> right -> val;
            result = result || _preOrder(root -> right, sum, target);
            sum -= root -> right -> val;
        }
        return result;
    }
};
