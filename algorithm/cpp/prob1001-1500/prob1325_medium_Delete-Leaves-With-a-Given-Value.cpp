// prob1325: Delete Leaves With a Given Value

/*
 * https://leetcode-cn.com/problems/delete-leaves-with-a-given-value/
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        if(!root) return nullptr;
        root =  _postOrder(root, target);
        return root;
    }

private:
    bool _is_leaf(TreeNode* node)
    {
        return (!node -> left && !node -> right);
    }

    TreeNode* _postOrder(TreeNode* node, int target)
    {
        if(node -> left)
            node -> left = _postOrder(node -> left, target);
        if(node -> right)
            node -> right = _postOrder(node -> right, target);
        if(_is_leaf(node) && node -> val ==  target)
            node = nullptr;
        return node;
    }
};
