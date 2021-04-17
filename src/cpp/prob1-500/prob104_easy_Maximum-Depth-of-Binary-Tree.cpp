// prob104: Maximum Depth of Binary Tree

/*
 * Given a binary tree, find its maximum depth.
 * The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
 * Note: A leaf is a node with no children.
 */

#include "include/Node.h"
#include <queue>

using namespace std;

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int level = 1;
        vector<TreeNode*> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(TreeNode *node: level_nodes)
            {
                if(node -> left) q.push(node -> left);
                if(node -> right) q.push(node -> right);
            }
            ++level;
        }
        return level - 1;
    }
};
