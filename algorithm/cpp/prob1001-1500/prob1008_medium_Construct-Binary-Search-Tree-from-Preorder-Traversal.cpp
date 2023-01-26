// prob1008: Construct Binary Search Tree from Preorder Traversal

/*
 * Return the root node of a binary search tree that matches the given preorder traversal.
 * (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left
 * has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a
 * preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)
 * It's guaranteed that for the given test cases there is always possible to find a binary search tree with the given requirements.
 */

/*
 * Example 1:
 * Input: [8,5,1,7,10,12]
 * Output: [8,5,10,1,7,null,12]
 */

/*
 * Constraints:
 * 1 <= preorder.length <= 100
 * 1 <= preorder[i] <= 10^8
 * The values of preorder are distinct.
 */

#include "include/Node.h"
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n = preorder.size();
        TreeNode *root = new TreeNode(preorder[0]);
        stack<TreeNode*> st;
        st.push(root);
        for(int i = 1; i < n; ++i)
        {
            int val = preorder[i];
            TreeNode *tmp = new TreeNode(val);
            if(st.top() -> val > val)
            {
                st.top() -> left = tmp;
                st.push(tmp);
            }
            else
            {
                while(st.top() -> val < val)
                {
                    TreeNode *top = st.top();
                    st.pop();
                    if(st.empty() || st.top() -> val > val)
                    {
                        top -> right = tmp;
                        st.push(tmp);
                    }
                }
            }
        }
        return root;
    }
};
