// prob236: Lowest Common Ancestor of a Binary Tree

/*
 *
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined
 * between two nodes p and q as the lowest node in T that has both p and q as descendants
 * (where we allow a node to be a descendant of itself).”
 */

/*
 * Note:
 *
 * All of the nodes' values will be unique.
 * p and q are different and both values will exist in the binary tree.
 */

#include <stack>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 调用方保证树至少有两个点，且p,q有效
        stack<TreeNode*> st;
        _preOrder(root, st, p, q);

        TreeNode *target;
        if(st.top() == p)
            target = q;
        else
            target = p;

        TreeNode *cur = st.top();
        st.pop();
        if(cur -> left && dfs(cur -> left, target))
            return cur;
        if(cur -> right && dfs(cur -> right, target))
            return cur;
        TreeNode *prev = cur;
        while(!st.empty())
        {
            cur = st.top();
            st.pop();
            if(cur -> left == prev && cur -> right && dfs(cur -> right, target))
                return cur;
            if(cur -> right == prev && cur -> left && dfs(cur -> left, target))
                return cur;
            prev = cur;
        }
        return nullptr;
    }

private:
    bool _preOrder(TreeNode* root, stack<TreeNode*>& st, TreeNode* p, TreeNode* q)
    {
        // 调用方保证 root 合法
        st.push(root);

        if(root == p || root == q)
            return true;

        if(root -> left && _preOrder(root -> left, st, p, q))
            return true;
        if(root -> right && _preOrder(root -> right, st, p, q))
            return true;

        st.pop();
        return false;
    }

    bool dfs(TreeNode* root, TreeNode* target)
    {
        // 调用方保证 root 合法
        if(root == target)
            return true;

        bool result = false;
        if(root -> left)
            result = result || dfs(root -> left, target);
        if(result) return true;
        if(root -> right)
            result = result || dfs(root -> right, target);
        return result;
    }
};

// 递归
class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root -> left, p, q);
        TreeNode *right = lowestCommonAncestor(root -> right, p, q);
        if(!left) return right;
        if(!right) return left;
        return root;
    }
};
