// prob662: Maximum Width of Binary Tree

/*
 * Given a binary tree, write a function to get the maximum width of the given tree.
 * The width of a tree is the maximum width among all levels.
 * The binary tree has the same structure as a full binary tree, but some nodes are null.
 * The width of one level is defined as the length between the end-nodes
 * (the leftmost and right most non-null nodes in the level,
 * where the null nodes between the end-nodes are also counted into the length calculation.
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

#include "include/Node.h"
#include <queue>

using namespace std;

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root == nullptr) return 0;
        int result = 1;
        queue<TreeNode*> q1, q2;
        q1.push(root);
        while(!q1.empty() || !q2.empty())
        {
            if(!q1.empty())
            {
                while(!q1.empty() && q1.front() == nullptr)
                    q1.pop();
                if(!q1.empty())
                {
                    int width = 0;
                    int cur_null = 0;
                    while(!q1.empty())
                    {
                        if(q1.front() == nullptr)
                        {
                            ++cur_null;
                            q2.push(nullptr);
                            q2.push(nullptr);
                            q1.pop();
                        }
                        else
                        {
                            q2.push(q1.front() -> left);
                            q2.push(q1.front() -> right);
                            q1.pop();
                            width += cur_null + 1;
                            cur_null = 0;
                        }
                    }
                    result = max(result, width);
                }
            }
            else
            {
                while(!q2.empty() && q2.front() == nullptr)
                    q2.pop();
                if(!q2.empty())
                {
                    int width = 0;
                    int cur_null = 0;
                    while(!q2.empty())
                    {
                        if(q2.front() == nullptr)
                        {
                            ++cur_null;
                            q1.push(nullptr);
                            q1.push(nullptr);
                            q2.pop();
                        }
                        else
                        {
                            q1.push(q2.front() -> left);
                            q1.push(q2.front() -> right);
                            q2.pop();
                            width += cur_null + 1;
                            cur_null = 0;
                        }
                    }
                    result = max(result, width);
                }
            }
        }
        return result;
    }
};

// 基本 BFS 解法插入弹出了很多 nullptr
// 队列中不止存儿子的指针，还存儿子的编号，这样可以由编号算宽度
class Solution_2 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root == nullptr) return 0;
        int result = 1;
        queue<pair<TreeNode*, unsigned long long>> q1, q2;
        q1.push(make_pair(root, 0ull));
        while(!q1.empty() || !q2.empty())
        {
            if(!q1.empty())
            {
                while(!q1.empty() && q1.front().first == nullptr)
                    q1.pop();
                if(!q1.empty())
                {
                    int left = q1.front().second;
                    int right = left;
                    while(!q1.empty())
                    {
                        if(q1.front().first == nullptr)
                            q1.pop();
                        else
                        {
                            q2.push(make_pair(q1.front().first -> left, q1.front().second * 2 + 1));
                            q2.push(make_pair(q1.front().first -> right, q1.front().second * 2 + 2));
                            right = q1.front().second;
                            q1.pop();
                        }
                    }
                    int width = right - left + 1;
                    result = max(result, width);
                }
            }
            else
            {
                while(!q2.empty() && q2.front().first == nullptr)
                    q2.pop();
                if(!q2.empty())
                {
                    int left = q2.front().second;
                    int right = left;
                    while(!q2.empty())
                    {
                        if(q2.front().first == nullptr)
                            q2.pop();
                        else
                        {
                            q1.push(make_pair(q2.front().first -> left, q2.front().second * 2 + 1));
                            q1.push(make_pair(q2.front().first -> right, q2.front().second * 2 + 2));
                            right = q2.front().second;
                            q2.pop();
                        }
                    }
                    int width = right - left + 1;
                    result = max(result, width);
                }
            }
        }
        return result;
    }
};
