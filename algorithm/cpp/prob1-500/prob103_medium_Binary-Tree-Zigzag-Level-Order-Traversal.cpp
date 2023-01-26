// prob103: Binary Tree Zigzag Level Order Traversal

/*
 * Given a binary tree, return the zigzag level order traversal of its nodes' values.
 * (ie, from left to right, then right to left for the next level and alternate between).
 */

/*
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its zigzag level order traversal as:
 * [
 *   [3],
 *   [20,9],
 *   [15,7]
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
#include <stack>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(!root) return vector<vector<int> >();
        stack<TreeNode*> st;
        st.push(root);
        int level = 1;
        vector<TreeNode*> level_nodes;
        vector<vector<int> > result;
        vector<int> level_items;
        while(!st.empty())
        {
            level_nodes.clear();
            level_items.clear();
            while(!st.empty())
            {
                level_nodes.push_back(st.top());
                st.pop();
            }
            for(TreeNode *node: level_nodes)
            {
                level_items.push_back(node -> val);
                if(level & 1)
                {
                    if(node -> left) st.push(node -> left);
                    if(node -> right) st.push(node -> right);
                }
                else
                {
                    if(node -> right) st.push(node -> right);
                    if(node -> left) st.push(node -> left);
                }
            }
            result.push_back(level_items);
            ++level;
        }
        return result;
    }
};
