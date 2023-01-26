// prob1161: Maximum Level Sum of a Binary Tree

/*
 * Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
 * Return the smallest level X such that the sum of all the values of nodes at level X is maximal.
 */

/*
 * Example 1:
 * Output: 2
 * Explanation:
 * Level 1 sum = 1.
 * Level 2 sum = 7 + 0 = 7.
 * Level 3 sum = 7 + -8 = -1.
 * So we return the level with the maximum sum which is level 2.
 */

/*
 * Note:
 * The number of nodes in the given tree is between 1 and 10^4.
 * -10^5 <= node.val <= 10^5
 */

#include <vector>
#include <queue>
#include <climits>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        if(!root) return 0;
        queue<TreeNode*> q;
        int level = 1;
        q.push(root);
        vector<TreeNode*> level_nodes;
        int result = -1;
        int max_sum = INT_MIN;
        while(!q.empty())
        {
            level_nodes.clear();
            int level_sum = 0;
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                level_sum += q.front() -> val;
                q.pop();
            }
            if(level_sum > max_sum)
            {
                max_sum = level_sum;
                result = level;
            }
            for(TreeNode *node: level_nodes)
            {
                if(node -> left)
                {
                    q.push(node -> left);
                }
                if(node -> right)
                {
                    q.push(node -> right);
                }
            }
            ++level;
        }
        return result;
    }
};
