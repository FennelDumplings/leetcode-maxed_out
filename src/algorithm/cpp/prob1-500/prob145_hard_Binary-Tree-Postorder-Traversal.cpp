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

// Morris 遍历
class Solution_3 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
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
                    _right_list_reverse_result(cur1 -> left, result);
                }
            }
            cur1 = cur1 -> right;
        }
        _right_list_reverse_result(root, result);
        return result;
    }

private:
    void _right_list_reverse_result(TreeNode* root, vector<int>& result)
    {
        TreeNode *tmp = _reverseTreeRightList(root);
        TreeNode *iter = tmp;
        while(iter)
        {
            result.push_back(iter -> val);
            iter = iter -> right;
        }
        root = _reverseTreeRightList(tmp);
    }

    TreeNode* _reverseTreeRightList(TreeNode* head) {
        // 空链表
        if(head == nullptr) return head;
        // 只有一个元素的链表
        if(head -> right == nullptr) return head;

        // 至少两个元素，prev初始为第一个，iter初始为第二个
        TreeNode *prev = head;
        TreeNode *iter = head -> right;
        TreeNode *tmp = nullptr;

        while(iter -> right != nullptr)
        {
            tmp = iter -> right;
            iter -> right = prev;
            prev = iter;
            iter = tmp;
        }

        iter -> right = prev;
        head -> right = nullptr;
        head = iter;

        return head;
    }
};
