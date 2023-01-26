// prob107: Binary Tree Level Order Traversal II

/*
 * Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
 */

/*
 * Example
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its bottom-up level order traversal as:
 * [
 *   [15,7],
 *   [9,20],
 *   [3]
 * ]
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
#include <queue>
#include <algorithm>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(!root) return vector<vector<int> >();
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int> > result;
        vector<TreeNode*> level_nodes;
        vector<int> level_items;
        while(!q.empty())
        {
            level_items.clear();
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(TreeNode* node: level_nodes)
            {
                level_items.push_back(node -> val);
                if(node -> left) q.push(node -> left);
                if(node -> right) q.push(node -> right);
            }
            result.push_back(level_items);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
