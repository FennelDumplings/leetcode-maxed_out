// prob572: Subtree of Another Tree

/*
 * Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a
 * subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants.
 * The tree s could also be considered as a subtree of itself.
 */

/*
 * Example 1:
 * Given tree s:
 *      3
 *     / \
 *    4   5
 *   / \
 *  1   2
 * Given tree t:
 *    4
 *   / \
 *  1   2
 * Return true, because t has the same structure and node values with a subtree of s.
 * Example 2:
 * Given tree s:
 *      3
 *     / \
 *    4   5
 *   / \
 *  1   2
 *     /
 *    0
 * Given tree t:
 *    4
 *   / \
 *  1   2
 * Return false.
 */

#include "include/Node.h"

class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(!s && !t) return true;
        if(!s || !t) return false;
        return _isSametree(s, t) || isSubtree(s -> left, t) || isSubtree(s -> right, t);
    }

private:
    bool _isSametree(TreeNode* s, TreeNode* t) {
        // lc100
        return _preOrder(s, t);
    }

    bool _preOrder(TreeNode* p, TreeNode* q)
    {
        if(!p && !q)
            return true;
        if(!p || !q)
            return false;
        bool result = true;
        result = result && (p -> val == q -> val);
        if(!result) return false;
        result = result && _preOrder(p -> left, q -> left);
        if(!result) return false;
        result = result && _preOrder(p -> right, q -> right);
        return result;
    }
};
