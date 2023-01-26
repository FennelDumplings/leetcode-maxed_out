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

// 不用队列层序遍历
class Solution_2 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(root == nullptr) return result;
        for(int i = 0; ;++i)
        {
            result.push_back(vector<int>());
            if(!_levelOrder(root, result[i], i))
            {
                if(result[i].empty())
                    result.pop_back();
                break;
            }
        }
        return result;
    }

private:
    int _levelOrder(TreeNode* root, vector<int>& level_result, int level)
    {
        if(!root || level < 0)
            return 0;
        if(level == 0)
        {
            level_result.push_back(root -> val);
            return 1;
        }
        return _levelOrder(root -> left, level_result, level - 1)
            + _levelOrder(root -> right, level_result, level - 1);
    }
};

// 双指针
class Solution_3 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(root == nullptr) return result;
        vector<TreeNode*> nodes;
        nodes.push_back(root);
        int cur = 0, end = 1;
        while(cur < (int)nodes.size()) // 随着更新，nodes 的 size 动态变化
        {
            result.push_back({});
            end = nodes.size();
            while(cur < end)
            {
                // 处理节点数据 nodes[cur] -> data
                result.back().push_back(nodes[cur] -> val);
                if(nodes[cur] -> left)
                    nodes.push_back(nodes[cur] -> left);
                if(nodes[cur] -> right)
                    nodes.push_back(nodes[cur] -> right);
                ++cur;
            }
        }
        return result;
    }
};
