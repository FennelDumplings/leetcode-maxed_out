// prob145: Binary Tree Postorder Traversal

/*
 * Given a binary tree, return the postorder traversal of its nodes' values.
 */

/*
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 */

#include <vector>
#include <stack>
#include "include/Node.h"

using namespace std;

// 递归
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        _postOrder(root, result);
        return result;
    }

private:
    void _postOrder(TreeNode* root, vector<int>& result)
    {
        // 调用方保证 root 合法
        if(root -> left)
            _postOrder(root -> left, result);
        if(root -> right)
            _postOrder(root -> right, result);

        result.push_back(root -> val);
    }
};

// 迭代
class Solution_2 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        stack<TreeNode*> output;
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            output.push(cur);
            if(cur -> left)
                st.push(cur -> left);
            if(cur -> right)
                st.push(cur -> right);
        }
        vector<int> result;
        while(!output.empty())
        {
            result.push_back(output.top() -> val);
            output.pop();
        }
        return result;
    }
};
