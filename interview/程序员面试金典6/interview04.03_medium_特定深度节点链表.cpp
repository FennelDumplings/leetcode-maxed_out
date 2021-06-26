// interview04.03: 特定深度节点链表

/*
 * https://leetcode-cn.com/problems/list-of-depth-lcci/
 */

#include <vector>
#include <queue>

#include "../../include/Node.h"

using namespace std;

class Solution {
public:
    vector<ListNode*> listOfDepth(TreeNode* tree) {
        if(!tree) return {};
        queue<TreeNode*> q;
        q.push(tree);
        vector<TreeNode*> level_nodes;
        vector<ListNode*> result;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ListNode *list = nullptr;
            ListNode *iter = nullptr;
            for(TreeNode *node: level_nodes)
            {
                if(!iter)
                {
                    iter = new ListNode(node -> val);
                    list = iter;
                }
                else
                {
                    iter -> next = new ListNode(node -> val);
                    iter = iter -> next;
                }
                if(node -> left)
                    q.push(node -> left);
                if(node -> right)
                    q.push(node -> right);
            }
            result.push_back(list);
        }
        return result;
    }
};
