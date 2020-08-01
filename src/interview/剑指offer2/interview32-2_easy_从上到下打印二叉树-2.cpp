// interview32-2: 从上到下打印二叉树 II

/*
 * https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof/
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
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            result.push_back({});
            for(TreeNode *node: level_nodes)
            {
                result.back().push_back(node -> val);
                if(node -> left)
                    q.push(node -> left);
                if(node -> right)
                    q.push(node -> right);
            }
        }
        return result;
    }
};
