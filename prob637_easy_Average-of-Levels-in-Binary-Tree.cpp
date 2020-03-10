// prob637: Average of Levels in Binary Tree

/*
 * Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
 */

/*
 * Example 1:
 * Input:
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * Output: [3, 14.5, 11]
 * Explanation:
 * The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
 */

/*
 * Note:
 * The range of node's value is in the range of 32-bit signed integer.
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
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if(!root) return vector<double>();
        queue<TreeNode*> q;
        q.push(root);
        vector<double> result;
        vector<TreeNode*> level_nodes;
        double level_sum = 0.0;
        while(!q.empty())
        {
            level_nodes.clear();
            level_sum = 0.0;
            int num = 0;
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
                ++num;
            }
            for(TreeNode *node: level_nodes)
            {
                level_sum += (double)(node -> val);
                if(node -> left) q.push(node -> left);
                if(node -> right) q.push(node -> right);
            }
            result.push_back(level_sum / num);
        }
        return result;
    }
};
