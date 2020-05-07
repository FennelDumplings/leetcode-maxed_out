// prob515: Find Largest Value in Each Tree Row

/*
 * You need to find the largest value in each row of a binary tree.
 */

/*
 * Example:
 * Input:
 *           1
 *          / \
 *         3   2
 *        / \   \
 *       5   3   9
 * Output: [1, 3, 9]
 */

#include <vector>
#include <queue>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        _levelOrder(root, result);
        return result;
    }

private:
    void _levelOrder(TreeNode* root, vector<int>& result)
    {
        queue<TreeNode*> q;
        q.push(root);
        vector<TreeNode*> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            int n = level_nodes.size();
            int maxx = level_nodes[0] -> val;
            for(int i = 0; i < n; ++i)
            {
                TreeNode *node = level_nodes[i];
                if(node -> val > maxx)
                    maxx = node -> val;
                if(node -> left)
                    q.push(node -> left);
                if(node -> right)
                    q.push(node -> right);
            }
            result.push_back(maxx);
        }
    }
};
