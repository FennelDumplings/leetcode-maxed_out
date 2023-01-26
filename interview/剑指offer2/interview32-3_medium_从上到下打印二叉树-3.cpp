// interview32-3: 从上到下打印二叉树 III

/*
 * https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof/
 */

#include <vector>
#include <queue>
#include "../../include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root) return {};
        queue<TreeNode*> q;
        q.push(root);
        vector<TreeNode*> level_nodes;
        vector<vector<int>> result;
        int level = 1;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            result.push_back({});
            int n = level_nodes.size();
            if(level & 1)
            {
                for(int i = 0; i < n; ++i)
                    result.back().push_back(level_nodes[i] -> val);
            }
            else
            {
                for(int i = n - 1; i >= 0; --i)
                    result.back().push_back(level_nodes[i] -> val);
            }
            for(TreeNode *node: level_nodes)
            {
                if(node -> left)
                    q.push(node -> left);
                if(node -> right)
                    q.push(node -> right);
            }
            level ^= 1;
        }
        return result;
    }
};
