// prob1372: Longest ZigZag Path in a Binary Tree

/*
 * Given a binary tree root, a ZigZag path for a binary tree is defined as follow:
 * Choose any node in the binary tree and a direction (right or left).
 * If the current direction is right then move to the right child of the current node otherwise move to the left child.
 * Change the direction from right to left or right to left.
 * Repeat the second and third step until you can't move in the tree.
 * Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).
 * Return the longest ZigZag path contained in that tree.
 */

/*
 * Example 1:
 * Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
 * Output: 3
 * Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
 * Example 2:
 * Input: root = [1,1,1,null,1,null,null,1,1,null,1]
 * Output: 4
 * Explanation: Longest ZigZag path in blue nodes (left -> right -> left -> right).
 * Example 3:
 * Input: root = [1]
 * Output: 0
 */

/*
 * Constraints:
 * Each tree has at most 50000 nodes..
 */

#include "include/Node.h"
#include <vector>

using namespace std;

class Solution {
public:
    int longestZigZag(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        _postOrder(root, ans);
        return ans - 1;
    }

private:
    struct Node
    {
        int left_max_len = 0;
        int right_max_len = 0;
        Node(int left_max_len, int right_max_len):left_max_len(left_max_len),right_max_len(right_max_len){}
    };

    Node _postOrder(TreeNode* root, int& ans)
    {
        Node result_left(0, 0);
        Node result_right(0, 0);
        Node result(1, 1);
        if(root -> left)
        {
            result_left = _postOrder(root -> left, ans);
            result.left_max_len = result_left.right_max_len + 1;
        }
        if(root -> right)
        {
            result_right = _postOrder(root -> right, ans);
            result.right_max_len = result_right.left_max_len + 1;
        }
        ans = max(ans, result.left_max_len);
        ans = max(ans, result.right_max_len);
        return result;
    }
};
