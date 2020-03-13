// prob173: Binary Search Tree Iterator

/*
 * Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
 * Calling next() will return the next smallest number in the BST.
 */

/*
 * Note:
 * next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
 * You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.
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

#include <stack>
#include "include/Node.h"

using namespace std;

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        while(root)
        {
            st.push(root);
            root = root -> left;
        }
    }

    /** @return the next smallest number */
    int next() {
        if(!hasNext()) return -1;
        TreeNode *cur = st.top();
        int result = cur -> val;
        st.pop();
        cur = cur -> right;
        while(cur)
        {
            st.push(cur);
            cur = cur -> left;
        }
        return result;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return(!st.empty());
    }

private:
    stack<TreeNode*> st;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
