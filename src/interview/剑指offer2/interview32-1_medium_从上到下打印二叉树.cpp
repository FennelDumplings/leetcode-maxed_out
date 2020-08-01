// interview32-1: 从上到下打印二叉树

/*
 * https://leetcode-cn.com/problemset/all/
 */

#include <vector>
#include <queue>
#include "../../include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        if(!root) return {};
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode *cur = q.front();
            q.pop();
            result.push_back(cur -> val);
            if(cur -> left)
                q.push(cur -> left);
            if(cur -> right)
                q.push(cur -> right);
        }
        return result;
    }
};
