// prob958: Check Completeness of a Binary Tree

/*
 * Given a binary tree, determine if it is a complete binary tree.
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in
 * the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
 */

/*
 * Example 1:
 * Input: [1,2,3,4,5,6]
 * Output: true
 * Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
 * Example 2:
 * Input: [1,2,3,4,5,null,7]
 * Output: false
 * Explanation: The node with value 7 isn't as far left as possible.
 */

/*
 * Note:
 * The tree will have between 1 and 100 nodes.
 */

#include <queue>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if(!root) return false;
        queue<TreeNode*> q;
        q.push(root);
        bool level_complete = true;
        vector<TreeNode*> level_nodes;
        while(level_complete)
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(TreeNode* node: level_nodes)
            {
                if(!level_complete)
                {
                    if(!node -> left && !node -> right)
                        continue;
                    else
                        return false;
                }
                if(!node -> left && node -> right)
                    return false;
                else if(node -> left && node -> right)
                {
                    q.push(node -> left);
                    q.push(node -> right);
                }
                else
                {
                    if(node -> left)
                        q.push(node -> left);
                    level_complete = false;
                }
            }
        }
        while(!q.empty())
        {
            TreeNode *cur = q.front();
            if(cur -> left || cur -> right)
                return false;
            q.pop();
        }
        return true;
    }
};
