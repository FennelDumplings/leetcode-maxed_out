// prob543: Diameter of Binary Tree

/*
 * Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary
 * tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
 */

/*
 * Note: The length of path between two nodes is represented by the number of edges between them.
 */

#include "include/Node.h"
#include <vector>

using namespace std;

// 后序遍历
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        int result = 0;
        _postOrder(root, result);
        return result - 1;
    }

private:
    int _postOrder(TreeNode *root, int& result)
    {
        int height = 1;
        int path = 1;
        if(root -> left)
        {
            int left_height = _postOrder(root -> left, result);
            height = max(height, left_height + 1);
            path += left_height;
        }
        if(root -> right)
        {
            int right_height = _postOrder(root -> right, result);
            height = max(height, right_height + 1);
            path += right_height;
        }
        result = max(result, path);
        return height;
    }
};
