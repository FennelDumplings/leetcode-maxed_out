// prob314: Binary Tree Vertical Order Traversal

/*
 * Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).
 * If two nodes are in the same row and column, the order should be from left to right.
 */

#include <deque>
#include <queue>
#include <vector>
#include <map>
#include "include/Node.h"

using namespace std;

// deque
// 注意 deque 与 list 的区别

// dfs + deque
// dfs, 可以得结果，但顺序不对
// 加了 deep 到 dfs 里如何纠正顺序，待解决
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if(!root) return vector<vector<int> >();
        deque<vector<int> > result_deque(1, vector<int>());
        auto iter = result_deque.begin();
        dfs(root, result_deque, iter, 0);
        vector<vector<int> > result;
        for(vector<int> item: result_deque)
            result.push_back(item);
        return result;
    }

private:
    void dfs(TreeNode* cur, deque<vector<int> >& result, deque<vector<int> >::iterator iter, int deep)
    {
        iter -> push_back(cur -> val);
        if(cur -> left)
        {
            if(iter == result.begin())
                result.push_front(vector<int>());
            --iter;
            dfs(cur -> left, result, iter, deep + 1);
            ++iter;
        }
        if(cur -> right)
        {
            ++iter;
            if(iter == result.end())
                result.push_back(vector<int>());
            dfs(cur -> right, result, iter, deep + 1);
            --iter;
        }
    }
};

// bfs + deque
class Solution_2 {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if(!root) return vector<vector<int> >();
        deque<vector<int> > result_deque(1, vector<int>());
        using DQI = deque<vector<int> >::iterator;

        DQI iter = result_deque.begin();
        queue<pair<TreeNode*, DQI> > q;
        q.push(pair<TreeNode*, DQI>(root, iter));

        vector<pair<TreeNode*, DQI> > level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(auto item: level_nodes)
            {
                TreeNode *node = item.first;
                DQI iter = item.second;
                iter -> push_back(node -> val);
                if(node -> left)
                {
                    if(iter == result_deque.begin())
                        result_deque.push_front(vector<int>());
                    --iter;
                    q.push(pair<TreeNode*, DQI>(node -> left, iter));
                    ++iter;
                }
                if(node -> right)
                {
                    ++iter;
                    if(iter == result_deque.end())
                        result_deque.push_back(vector<int>());
                    q.push(pair<TreeNode*, DQI>(node -> right, iter));
                    --iter;
                }
            }
        }

        vector<vector<int> > result;
        for(vector<int> item: result_deque)
            result.push_back(item);
        return result;
    }
};

// bfs + map
// https://leetcode-cn.com/problems/binary-tree-vertical-order-traversal/solution/c-ceng-xu-bian-li-you-xu-hash-by-sptuan/
class Solution_3 {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if(!root) return ans;

        queue<TreeNode*> q;
        queue<int> state;
        q.push(root);
        state.push(0);

        while(!q.empty())
        {
            auto temp = q.front();
            auto temp_state = state.front();
            q.pop();
            state.pop();

            if(mapping.find(temp_state) == mapping.end())
            {
                vector<int> ans_layer;
                ans_layer.push_back(temp -> val);
                ans.push_back(ans_layer);
                mapping[temp_state] = ans.size() - 1;
            }
            else
                ans[mapping[temp_state]].push_back(temp -> val);

            if(temp -> left)
            {
                q.push(temp -> left);
                state.push(temp_state - 1);
            }
            if(temp->right != NULL)
            {
                q.push(temp -> right);
                state.push(temp_state + 1);
            }

        }

        vector<vector<int>> ordered_ans;
        for(auto &it:mapping){
            ordered_ans.push_back(ans[(it).second]);
        }
        return ordered_ans;
    }

private:
    map<int, int> mapping;
    vector<vector<int> > ans;
};
