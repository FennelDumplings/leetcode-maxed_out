// prob105: Construct Binary Tree from Preorder and Inorder Traversal

/*
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 */

/*
 * Note:
 * You may assume that duplicates do not exist in the tree.
 */

/*
 * For example, given
 * preorder = [3,9,20,15,7]
 * inorder = [9,3,15,20,7]
 * Return the following binary tree:
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 */

#include <vector>
#include <unordered_map>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return nullptr;
        int n = inorder.size();
        unordered_map<int, int> position;
        for(int i = 0; i < n; ++i)
            position[inorder[i]] = i;
        return _buildTree(preorder, inorder, 0, n - 1, 0, n - 1, position);
    }

private:
    TreeNode* _buildTree(const vector<int>& preorder, const vector<int>& inorder,
            int i_pre, int j_pre, int i_in, int j_in, unordered_map<int, int>& position)
    {
        TreeNode *root = new TreeNode(preorder[i_pre]);
        int pos = position[preorder[i_pre]];
        int left_num = pos - i_in;
        int right_num = j_in - pos;
        if(left_num > 0) // 有左子树
        {
            TreeNode *left = _buildTree(preorder, inorder, i_pre + 1, i_pre + left_num, i_in, position[preorder[i_pre]] - 1, position);
            root -> left = left;
        }
        if(right_num > 0) // 有右子树
        {
            TreeNode *right = _buildTree(preorder, inorder, i_pre + left_num + 1, j_pre, position[preorder[i_pre]] + 1, j_in, position);
            root -> right = right;
        }
        return root;
    }
};
