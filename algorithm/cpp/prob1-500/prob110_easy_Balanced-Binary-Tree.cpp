// prob110: Balanced Binary Tree

/*
 * Given a binary tree, determine if it is height-balanced.
 * For this problem, a height-balanced binary tree is defined as:
 * a binary tree in which the left and right subtrees of every node differ in height by no more than 1.
 */

#include <cmath>
#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return _isBalanced(root);
    }

private:
    bool _isBalanced(TreeNode* root)
    {
        auto result = _height(root);
        return result.second;
    }

    pair<int, bool> _height(TreeNode* root)
    {
        if(!root) return pair<int, bool>(0, true);

        pair<int, bool> record_left = _height(root -> left);
        if(!record_left.second) return record_left;
        pair<int, bool> record_right = _height(root -> right);
        if(!record_right.second) return record_right;

        bool balance = abs(record_left.first - record_right.first) <= 1;
        int height = max(record_left.first, record_right.first) + 1;
        return pair<int, bool>(height, balance);
    }
};
