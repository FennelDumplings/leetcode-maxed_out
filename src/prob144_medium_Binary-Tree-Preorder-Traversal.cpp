// prob144: Binary Tree Preorder Traversal

/*
 * Given a binary tree, return the preorder traversal of its nodes' values.
 */

/*
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 */

#include <stack>
#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        vector<int> result;
        _preOrder(root, result);
        return result;
    }

private:
    void _preOrder(TreeNode* root, vector<int>& result)
    {
        // 调用方保证 root 合法
        result.push_back(root -> val);

        if(root -> left)
            _preOrder(root -> left, result);
        if(root -> right)
            _preOrder(root -> right, result);
    }
};

// 递归，一次进栈
class Solution_2 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if(!root) return vector<int>();
        stack<TreeNode*> st;
        st.push(root);
        vector<int> result;
        while(!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            result.push_back(cur -> val);
            if(cur -> right)
                st.push(cur -> right);
            if(cur -> left)
                st.push(cur -> left);
        }
        return result;
    }
};

// Morris 遍历
class Solution_3 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
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
                    result.push_back(cur1 -> val); // preOrder 推左子树非空的根
                    cur1 = cur1 -> left;
                    continue;
                }
                else
                {
                    cur2 -> right = nullptr; // 断开线索
                }
            }
            else
                result.push_back(cur1 -> val); // preOrder 推叶子或只有右子树的根
            cur1 = cur1 -> right;
        }
        return result;
    }
};
