// Prob101: Symmetric Tree

/*Description
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
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

#include <deque>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr) return true;

        deque<TreeNode*> left_nodes, right_nodes;

        int balance = twoEqualTreeNodes(root -> left, root -> right);
        if(balance == 0) return false;
        if(balance == 1) return true;

        left_nodes.push_back(root -> left);
        right_nodes.push_back(root -> right);

        while(!left_nodes.empty())
        {
            TreeNode *left_node = left_nodes.front();
            TreeNode *right_node = right_nodes.front();
            left_nodes.pop_front();
            right_nodes.pop_front();
            TreeNode *left_left = left_node -> left;
            TreeNode *left_right = left_node -> right;
            TreeNode *right_left = right_node -> left;
            TreeNode *right_right = right_node -> right;
            int balance;
            balance = twoEqualTreeNodes(left_left, right_right);
            if(balance == 0) return false;
            if(balance == 2)
            {
                left_nodes.push_back(left_left);
                right_nodes.push_back(right_right);
            }
            balance = twoEqualTreeNodes(left_right, right_left);
            if(balance == 0) return false;
            if(balance == 2)
            {
                left_nodes.push_back(left_right);
                right_nodes.push_back(right_left);
            }
        }
        return true;
    }

private:
    int twoEqualTreeNodes(TreeNode* left, TreeNode* right)
    {
        // 两个节点不相等，返回 0(包括一空一非空，两个均非空，但值不相等)
        // 两个节点相等，但是都为 nullptr, 返回 1
        // 两个节点相等，且都不为 nullptr, 返回 2
        if(left == nullptr && right != nullptr) return 0;
        if(right == nullptr && left != nullptr) return 0;
        if(left == nullptr && right == nullptr) return 1;
        if(left -> val != right -> val)
            return 0;
        else
            return 2;
    }
};
