// interview07: 重建二叉树

/*
 * 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
 */

/*
 * 例如，给出
 * 前序遍历 preorder = [3,9,20,15,7]
 * 中序遍历 inorder = [9,3,15,20,7]
 * 返回如下的二叉树：
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 */

/*
 * 限制：
 * 0 <= 节点个数 <= 5000
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "include/Node.h"
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return nullptr;
        unordered_map<int, int> mapping;
        int n = inorder.size();
        for(int i = 0; i < n; ++i)
            mapping[inorder[i]] = i;
        return build(preorder, 0, n - 1, 0, n - 1, mapping);
    }

private:
    TreeNode* build(const vector<int>& preorder, int pre_left, int pre_right, int in_left, int in_right, unordered_map<int, int>& mapping)
    {
        TreeNode *root = new TreeNode(preorder[pre_left]);
        if(pre_left == pre_right)
            return root;
        // 有子树
        int idx_root = mapping[preorder[pre_left]];
        int len_left = idx_root - in_left;
        int len_right =  in_right - idx_root;
        if(len_left > 0)
        {
            root -> left = build(preorder, pre_left + 1, pre_left + len_left, in_left, idx_root - 1, mapping);
        }
        if(len_right > 0)
        {
            root -> right = build(preorder, pre_left + len_left + 1, pre_right, idx_root + 1, in_right, mapping);
        }
        return root;
    }
};
