// prob1602: Find Nearest Right Node in Binary Tree

/*
 * https://leetcode-cn.com/problems/find-nearest-right-node-in-binary-tree/
 */

#include "include/Node.h"

class Solution {
public:
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        TreeNode *result = nullptr;
        int max_level = -1;
        dfs(root, 0, max_level, u, result);
        return result;
    }

private:
    void dfs(TreeNode* node, int level, int& max_level, TreeNode* u, TreeNode*& result)
    {
        if(result != nullptr) return;
        if(max_level != -1 && level == max_level)
        {
            result = node;
            return;
        }
        // max_level == -1 || level < max_level
        if(max_level == -1 && node == u)
        {
            max_level = level;
            return;
        }
        if(node -> left)
            dfs(node -> left, level + 1, max_level, u, result);
        if(node -> right)
            dfs(node -> right, level + 1, max_level, u, result);
    }
};
