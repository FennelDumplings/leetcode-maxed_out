// prob98: Validate Binary Search Tree

/*
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 * Assume a BST is defined as follows:
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;
        if(!(root -> left) && !(root -> right))
            return true;

        PBT result = _inOrder(root);
        return result.first;

    }

private:
    using PII = pair<int, int>;
    using PBT = pair<bool, PII>;

    PBT _inOrder(TreeNode* root) {
        // 调用方保证 root 不为空
        // 与前驱和后继对比
        // 若左子树为空，
        PBT result;
        result.first = true;
        result.second = PII(root -> val, root -> val);

        if(root -> left)
        {
            PBT result_left = _inOrder(root -> left);
            if(result_left.first && root -> val > result_left.second.second)
            {
                result.second.first = result_left.second.first;
            }
            else
            {
                result.first = false;
                return result;
            }
        }

        if(root -> right)
        {
            PBT result_right = _inOrder(root -> right);
            if(result_right.first && root -> val < result_right.second.first)
            {
                result.second.second = result_right.second.second;
            }
            else
            {
                result.first = false;
                return result;
            }
        }

        return result;
    }
};
