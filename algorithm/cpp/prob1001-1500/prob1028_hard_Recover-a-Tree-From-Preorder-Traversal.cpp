// prob1028: Recover a Tree From Preorder Traversal

/*
 * We run a preorder depth first search on the root of a binary tree.
 *
 * At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)
 *
 * If a node has only one child, that child is guaranteed to be the left child.
 *
 * Given the output S of this traversal, recover the tree and return its root.
 */

/*
 * Example 1:
 * Input: "1-2--3--4-5--6--7"
 * Output: [1,2,5,3,4,6,7]
 * Example 2:
 * Input: "1-2--3---4-5--6---7"
 * Output: [1,2,5,3,null,6,null,4,null,7]
 * Example 3:
 * Input: "1-401--349---90--88"
 * Output: [1,401,null,349,88,90]
 */

/*
 * Note:
 *
 * The number of nodes in the original tree is between 1 and 1000.
 * Each node will have a value between 1 and 10^9.
 */

#include "include/Node.h"
#include <string>
#include <sstream>
#include <stack>

using namespace std;

class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        int n = S.size();
        int iter = 0;
        while(iter < n && '0' <= S[iter] && S[iter] <= '9')
            ++iter;
        int num;
        stringstream ss;
        ss << S.substr(0, iter);
        ss >> num;
        TreeNode *root = new TreeNode(num);
        TreeNode *node = root;
        stack<PTI> st;
        st.push(PTI(node, 0));
        while(iter < n)
        {
            int right = iter;
            while(right < n && S[right] == '-')
                ++right;
            int level = right - iter;
            // 此时 st.top().second + 1 == level
            iter = right;
            while(iter < n && '0' <= S[iter] && S[iter] <= '9')
                ++iter;
            int num;
            stringstream ss;
            ss << S.substr(right, iter - right);
            ss >> num;
            TreeNode *p = new TreeNode(num);
            if(st.top().second + 1 == level)
            {
                st.top().first -> left = p;
            }
            else
            {
                while(!st.empty() && st.top().second >= level)
                    st.pop();
                st.top().first -> right = p;
            }
            st.push(PTI(p, level));
        }
        return root;
    }

private:
    using PTI = pair<TreeNode*, int>;
};
