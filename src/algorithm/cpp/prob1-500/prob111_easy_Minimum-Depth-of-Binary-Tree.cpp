// prob111: Minimum Depth of Binary Tree

/*
 * Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
 * Note: A leaf is a node with no children.
 */

#include "include/Node.h"
#include <queue>

using namespace std;

class Solution {
public:
    int minDepth(TreeNode* root) {
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
                if(!(node -> left) && !(node -> right))
                    return level;
                if(node -> left) q.push(node -> left);
                if(node -> right) q.push(node -> right);
            }
            ++level;
        }
        return -1;
    }
};

// ID
class Solution_2 {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int depth = 1;
        while(!dfs(root, 1, depth))
            ++depth;
        return depth;
    }

private:
    bool dfs(TreeNode* node, int depth, const int max_depth)
    {
        if(!node -> left && !node -> right)
            return true;

        if(depth == max_depth)
            return false;

        if(node -> left)
            if(dfs(node -> left, depth + 1, max_depth))
                return true;
        if(node -> right)
            if(dfs(node -> right, depth + 1, max_depth))
                return true;
        return false;
    }
};
