// prob285: Inorder Successor in BST

/*
 * Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
 * The successor of a node p is the node with the smallest key greater than p.val.
 */

/*
 * Note:
 * If the given node has no in-order successor in the tree, return null.
 * It's guaranteed that the values of the tree are unique.
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root) return nullptr;
        if(p -> right)
        {
            TreeNode *iter = p -> right;
            while(iter -> left)
                iter = iter -> left;
            return iter;
        }
        return _inorderSuccessor(root, p);
    }


private:
    TreeNode* _inorderSuccessor(TreeNode* root, TreeNode* p)
    {
        // 调用方保证 root 不为空
        // 询问 root 的前驱是否是 p
        if(root -> left)
        {
            TreeNode *iter = root -> left;
            while(iter -> right)
                iter = iter -> right;
            if(iter == p)
                return root;
        }
        TreeNode *result_left = nullptr;
        TreeNode *result_right = nullptr;
        if(root -> left)
            result_left = _inorderSuccessor(root -> left, p);
        if(root -> right)
            result_right = _inorderSuccessor(root -> right, p);

        if(!result_left && !result_right)
            return nullptr;
        if(!result_left)
            return result_right;
        return result_left;
    }
};

class Solution_2 {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root) return nullptr;
        TreeNode *iter = root;
        TreeNode *result = nullptr;
        while(true)
        {
            if(iter -> val <= p -> val)
            {
                if(iter -> right)
                    iter = iter -> right;
                else
                    break;
            }
            else
            {
                result = iter;
                if(iter -> left)
                    iter = iter -> left;
                else
                    break;
            }
        }
        return result;
    }
};
