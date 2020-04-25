// prob235: Lowest Common Ancestor of a Binary Search Tree

/*
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
 */

/*
 * Example 1:
 * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
 * Output: 6
 * Explanation: The LCA of nodes 2 and 8 is 6.
 * Example 2:
 * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
 * Output: 2
 * Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
 */

/*
 * Note:
 * All of the nodes' values will be unique.
 * p and q are different and both values will exist in the BST.
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int left = min(p -> val, q -> val);
        int right = max(p -> val, q -> val);
        if(left == right) return p;
        TreeNode *iter = root;
        while(iter)
        {
            if(iter -> val > right)
                iter = iter -> left;
            else if(iter -> val < left)
                iter = iter -> right;
            else
                return iter;
        }
        return  root;
    }
};
