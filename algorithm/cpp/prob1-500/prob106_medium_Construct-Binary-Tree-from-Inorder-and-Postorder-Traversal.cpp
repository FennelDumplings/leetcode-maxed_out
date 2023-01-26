// prob106: Construct Binary Tree from Inorder and Postorder Traversal

/*
 * Given inorder and postorder traversal of a tree, construct the binary tree.
 */

/*
 * Note:
 * You may assume that duplicates do not exist in the tree.
 */

/*
 * For example, given
 * inorder = [9,3,15,20,7]
 * postorder = [9,15,7,20,3]
 * Return the following binary tree:
 *
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.empty()) return nullptr;
        int n = inorder.size();
        unordered_map<int, int> position;
        for(int i = 0; i < n; ++i)
            position[inorder[i]] = i;
        return _buildTree(inorder, postorder, 0, n - 1, 0, n - 1, position);
    }

private:
    TreeNode* _buildTree(const vector<int>& inorder, const vector<int>& postorder,
            int i_in, int j_in, int i_post, int j_post, unordered_map<int, int>& position)
    {
        TreeNode *root = new TreeNode(postorder[j_post]);
        int pos = position[postorder[j_post]];
        int left_num = pos - i_in;
        int right_num = j_in - pos;
        if(left_num > 0)
        {
            TreeNode *left = _buildTree(inorder, postorder, i_in, pos - 1, i_post, i_post + left_num - 1, position);
            root -> left = left;
        }
        if(right_num > 0)
        {
            TreeNode *right = _buildTree(inorder, postorder, pos + 1, j_in, j_post - right_num, j_post - 1, position);
            root -> right = right;
        }
        return root;
    }
};
