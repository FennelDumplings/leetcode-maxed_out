// Prob102: Binary Tree Level Order Traversal

/*Description
 * Given a binary tree, return the level order traversal of its nodes' values.
 * (ie, from left to right, level by level).
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

#include <vector>
#include <deque>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(root == nullptr) return result;
        deque<TreeNode*> queue;
        queue.push_back(root);
        while(!queue.empty())
        {
            vector<TreeNode*> level_treenodes;
            vector<int> level_items;
            while(!queue.empty())
            {
                level_treenodes.push_back(queue.front());
                queue.pop_front();
            }
            for(TreeNode* treenode:level_treenodes)
            {
                level_items.push_back(treenode -> val);
                if(treenode -> left != nullptr)
                    queue.push_back(treenode -> left);
                if(treenode -> right != nullptr)
                    queue.push_back(treenode -> right);
            }
            result.push_back(level_items);
        }
        return result;
    }
};
