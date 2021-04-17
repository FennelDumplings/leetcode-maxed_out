// prob993: cousins in Binary Tree

/*
 * In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.
 * Two nodes of a binary tree are cousins if they have the same depth, but have different parents.
 * We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.
 * Return true if and only if the nodes corresponding to the values x and y are cousins.
 */

/*
 * Note:
 * The number of nodes in the tree will be between 2 and 100.
 * Each node has a unique integer value from 1 to 100.
 */

#include "include/Node.h"
#include <queue>

using namespace std;

class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if(!root) return false;
        if(!(root -> left) && !(root -> right)) return false;
        using PTT = pair<TreeNode*, TreeNode*>;
        queue<PTT> q;
        q.push(PTT(root -> left, root -> right));
        vector<pair<TreeNode*, TreeNode*>> level_nodes;
        while(!q.empty())
        {
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            int n = level_nodes.size();
            int idx_x = -1, idx_y = -1;
            for(int i = 0; i < n; ++i)
            {
                PTT node_pair = level_nodes[i];
                if(node_pair.first && node_pair.first -> val == x) idx_x = i;
                if(node_pair.second && node_pair.second -> val == x) idx_x = i;
                if(node_pair.first && node_pair.first -> val == y) idx_y = i;
                if(node_pair.second && node_pair.second -> val == y) idx_y = i;
                if(node_pair.first && (node_pair.first -> left || node_pair.first -> right))
                    q.push(PTT(node_pair.first -> left, node_pair.first -> right));
                if(node_pair.second && (node_pair.second -> left || node_pair.second -> right))
                    q.push(PTT(node_pair.second -> left, node_pair.second -> right));
            }
            if(idx_x == -1 && idx_y == -1)
                continue;
            if(idx_x == -1 || idx_y == -1)
                return false;
            if(idx_x == idx_y)
                return false;
            else
                return true;
        }
        return false;
    }
};
