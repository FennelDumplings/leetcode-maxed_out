// prob1373: Maximum Sum BST in Binary Tree

/*
 * Given a binary tree root, the task is to return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
 * Assume a BST is defined as follows:
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 */

/*
 * Example 1:
 * Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
 * Output: 20
 * Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
 * Example 2:
 * Input: root = [4,3,null,1,2]
 * Output: 2
 * Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.
 * Example 3:
 * Input: root = [-4,-2,-5]
 * Output: 0
 * Explanation: All values are negatives. Return an empty BST.
 * Example 4:
 * Input: root = [2,1,3]
 * Output: 6
 * Example 5:
 * Input: root = [5,4,8,3,null,6,3]
 * Output: 7
 */

/*
 * Constraints:
 * Each tree has at most 40000 nodes..
 * Each node's value is between [-4 * 10^4 , 4 * 10^4]
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

#include "include/Node.h"
#include <climits>
#include <algorithm>

using namespace std;

struct Node
{
    int maxx, minx, sum;
    bool is_bst;
    Node(int maxx, int minx, int sum, bool is_bst):maxx(maxx),minx(minx),sum(sum),is_bst(is_bst){}
};

class Solution {
public:
    int maxSumBST(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        _postOrder(root, ans);
        return ans;
    }

private:
    Node _postOrder(TreeNode* root, int& ans)
    {
        Node result_left(INT_MIN, INT_MAX, 0, true);
        Node result_right(INT_MIN, INT_MAX, 0, true);
        Node result(root -> val, root -> val, root -> val, true);
        if(root -> left)
        {
            result_left = _postOrder(root -> left, ans);
            result.maxx = max(result.maxx, result_left.maxx);
            result.minx = min(result.minx, result_left.minx);
            result.sum += result_left.sum;
            if(!result_left.is_bst || result_left.maxx >= root -> val)
                result.is_bst = false;
        }
        if(root -> right)
        {
            result_right = _postOrder(root -> right, ans);
            result.maxx = max(result.maxx, result_right.maxx);
            result.minx = min(result.minx, result_right.minx);
            result.sum += result_right.sum;
            if(!result_right.is_bst || result_right.minx <= root -> val)
                result.is_bst = false;
        }
        if(result.is_bst)
            ans = max(ans, result.sum);
        return result;
    }
};
