// interview04.05: 合法二叉搜索树

/*
 * https://leetcode-cn.com/problems/legal-binary-search-tree-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        int minx = 0;
        bool most_left = false;
        return _inOrder(root, minx, most_left);
    }

private:
    bool _inOrder(TreeNode* node, int& minx, bool& most_left)
    {
        bool result = true;
        if(node -> left)
            result = result && _inOrder(node -> left, minx, most_left);
        if(!most_left)
            most_left = true;
        else if(node -> val <= minx)
            return false;
        minx = node -> val;
        if(node -> right)
            result = result && _inOrder(node -> right, minx, most_left);
        return result;
    }
};
