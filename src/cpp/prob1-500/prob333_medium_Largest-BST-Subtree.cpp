// prob333: Largest BST Subtree

/*
 * Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.
 * Note:
 * A subtree must include all of its descendants.
 */

/*
 * Example:
 * Input: [10,5,15,1,8,null,7]
 *
 *    10
 *    / \
 *   5  15
 *  / \   \
 * 1   8   7
 *
 * Output: 3
 * Explanation: The Largest BST Subtree in this case is the highlighted one.
 *              The return value is the subtree's size, which is 3.
 */

/*
 * Follow up:
 * Can you figure out ways to solve it with O(n) time complexity?
 */

#include "include/Node.h"
#include <vector>

using namespace std;

struct Node {
    int minx;
    int maxx;
    int cnt;
    TreeNode *root;
};

class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        dfs(root, ans);
        return ans;
    }

private:
    Node dfs(TreeNode* root, int& ans)
    {
        bool left_is_bst = true, right_is_bst = true;
        Node node;
        node.minx = root -> val;
        node.maxx = root -> val;
        node.cnt = 1;
        if(root -> left)
        {
            Node left = dfs(root -> left, ans);
            node.minx = min(node.minx, left.minx);
            node.maxx = max(node.maxx, left.maxx);
            node.cnt += left.cnt;
            if(left.root != root -> left || left.maxx >= root -> val)
                left_is_bst = false;
        }
        if(root -> right)
        {
            Node right = dfs(root -> right, ans);
            node.minx = min(node.minx, right.minx);
            node.maxx = max(node.maxx, right.maxx);
            node.cnt += right.cnt;
            if(right.root != root -> right || right.minx <= root -> val)
                right_is_bst = false;
        }
        if(left_is_bst && right_is_bst)
        {
            ans = max(ans, node.cnt);
            node.root = root;
        }
        return node;
    }
};
