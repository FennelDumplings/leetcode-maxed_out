// prob94: Binary Tree Inorder Traversal

/*
 * Given a binary tree, return the inorder traversal of its nodes' values.
 */

#include <stack>
#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        _inOrder(root, result);
        return result;
    }

private:
    void _inOrder(TreeNode* root, vector<int>& result)
    {
        if(root -> left)
            _inOrder(root -> left, result);
        result.push_back(root -> val);
        if(root -> right)
            _inOrder(root -> right, result);
    }
};

// 非递归
class Solution_2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;

        stack<TreeNode*> st;
        TreeNode *iter = root;
        while(!st.empty() || iter)
        {
            while(iter)
            {
                st.push(iter);
                iter = iter -> left;
            }
            if(!st.empty())
            {
                iter = st.top();
                st.pop();
                result.push_back(iter -> val);
                iter = iter -> right;
            }
        }
        return result;
    }
};

// Morris 遍历
class Solution_3 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        TreeNode *cur1 = root;
        TreeNode *cur2 = nullptr;
        while(cur1)
        {
            cur2 = cur1 -> left;
            if(cur2)
            {
                while(cur2 -> right && cur2 -> right != cur1)
                    cur2 = cur2 -> right;
                if(!(cur2 -> right))
                {
                    cur2 -> right = cur1; // 接线索
                    cur1 = cur1 -> left;
                    continue;
                }
                else
                {
                    cur2 -> right = nullptr; // 断开线索
                }
            }
            result.push_back(cur1 -> val); // inOrder 在向右，或者通过线索向上之前，打印该点
            cur1 = cur1 -> right;
        }
        return result;
    }
};
