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
        return build(preorder, 0, n - 1, mapping);
    }

private:
    TreeNode* build(const vector<int>& preorder, int left, int right, unordered_map<int, int>& mapping)
    {
        TreeNode *root = new TreeNode(preorder[left]);
        if(left == right)
            return root;
        int idx = mapping[preorder[left]];
        if(mapping[preorder[left + 1]] < idx)
            root -> left = build(preorder, left + 1, idx, mapping);
        root -> right = build(preorder, idx + 1, right, mapping);
        return root;
    }
};
