// prob1609: Even Odd Tree

/*
 * https://leetcode-cn.com/problems/even-odd-tree/
 */

#include "include/Node.h"
#include <queue>

using namespace std;

class Solution {
public:
    bool isEvenOddTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        vector<TreeNode*> level_node;
        int level = 0;
        while(!q.empty())
        {
            level_node.clear();
            while(!q.empty())
            {
                if(!(((q.front() -> val) & 1) ^ (level & 1)))
                    return false;
                level_node.push_back(q.front());
                q.pop();
            }
            int prev = -1;
            for(TreeNode *node: level_node)
            {
                if(prev != -1 && (level & 1) == 1 && node -> val <= prev)
                    return false;
                if(prev != -1 && (level & 1) == 0 && node -> val >= prev)
                    return false;
                prev = node -> val;
                if(node -> left)
                    q.push(node -> left);
                if(node -> right)
                    q.push(node -> right);
            }
            level ^= 1;
        }
        return true;
    }
};
