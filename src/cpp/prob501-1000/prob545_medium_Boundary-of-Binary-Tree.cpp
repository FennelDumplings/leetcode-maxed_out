// prob545: Boundary of Binary Tree

/*
 * Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root.
 * Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes. 
 * (The values of the nodes may still be duplicates.)
 * Left boundary is defined as the path from root to the left-most node. Right boundary is
 * defined as the path from root to the right-most node. If the root doesn't have left subtree or right subtree,
 * then the root itself is left boundary or right boundary. Note this definition only applies
 * to the input binary tree, and not applies to any subtrees.
 * The left-most node is defined as a leaf node you could reach when you always firstly travel
 * to the left subtree if exists. If not, travel to the right subtree. Repeat until you reach a leaf node.
 * The right-most node is also defined by the same way with left and right exchanged.
 */

/*
 * Example 1
 * Input:
 *   1
 *    \
 *     2
 *    / \
 *   3   4
 * Ouput:
 * [1, 3, 4, 2]
 * Explanation:
 * The root doesn't have left subtree, so the root itself is left boundary.
 * The leaves are node 3 and 4.
 * The right boundary are node 1,2,4. Note the anti-clockwise direction means you should output reversed right boundary.
 * So order them in anti-clockwise without duplicates and we have [1,3,4,2].
 * Example 2
 * Input:
 *     ____1_____
 *    /          \
 *   2            3
 *  / \          /
 * 4   5        6
 *    / \      / \
 *   7   8    9  10
 * Ouput:
 * [1,2,4,7,8,9,10,6,3]
 * Explanation:
 * The left boundary are node 1,2,4. (4 is the left-most node according to definition)
 * The leaves are node 4,7,8,9,10.
 * The right boundary are node 1,3,6,10. (10 is the right-most node).
 * So order them in anti-clockwise without duplicate nodes we have [1,2,4,7,8,9,10,6,3].
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if(!root) return vector<int>();
        if(_is_leaf(root)) return vector<int>({root -> val});
        vector<int> right_nodes, result;
        if(root -> left)
            _get_left(root, result);
        else
            result.push_back(root -> val);
        _get_leaf(root, result);
        if(root -> right)
            _get_right(root, right_nodes);
        for(int i = (int)right_nodes.size() - 1; i >= 1; --i)
            result.push_back(right_nodes[i]);
        return result;
    }

private:
    void _get_left(TreeNode* root, vector<int>& result)
    {
        if(_is_leaf(root))
            return;
        result.push_back(root -> val);
        if(root -> left)
            _get_left(root -> left, result);
        else
            _get_left(root -> right, result);
    }

    void _get_right(TreeNode* root, vector<int>& result)
    {
        if(_is_leaf(root))
            return;
        result.push_back(root -> val);
        if(root -> right)
            _get_right(root -> right, result);
        else
            _get_right(root -> left, result);
    }

    void _get_leaf(TreeNode* root, vector<int>& result)
    {
        if(_is_leaf(root))
            result.push_back(root -> val);
        if(root -> left)
            _get_leaf(root -> left, result);
        if(root -> right)
            _get_leaf(root -> right, result);
    }

    bool _is_leaf(TreeNode* root)
    {
        return !(root -> left) && !(root -> right);
    }
};
