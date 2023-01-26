// prob1023: Lowest Common Ancestor of Deepest Leaves

/*
 * Given a rooted binary tree, return the lowest common ancestor of its deepest leaves.
 * Recall that:
 * The node of a binary tree is a leaf if and only if it has no children
 * The depth of the root of the tree is 0, and if the depth of a node is d, the depth of each of its children is d+1.
 * The lowest common ancestor of a set S of nodes is the node A with the largest depth such that every node in S is in the subtree with root A.
 */

/*
 * Example 1:
 * Input: root = [1,2,3]
 * Output: [1,2,3]
 * Explanation:
 * The deepest leaves are the nodes with values 2 and 3.
 * The lowest common ancestor of these leaves is the node with value 1.
 * The answer returned is a TreeNode object (not an array) with serialization "[1,2,3]".
 * Example 2:
 * Input: root = [1,2,3,4]
 * Output: [4]
 * Example 3:
 * Input: root = [1,2,3,4,5]
 * Output: [2,4,5]
 */

/*
 * Constraints:
 * The given tree will have between 1 and 1000 nodes.
 * Each node of the tree will have a distinct value between 1 and 1000.
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        if(!root) return nullptr;
        if(!root -> left && !root -> right) return nullptr;
        PIT result = _postOrder(root, 0);
        return result.second;
    }

private:
    using PIT = pair<int, TreeNode*>;

    PIT _postOrder(TreeNode* root, int level)
    {
        if(!root -> left && !root -> right)
            return PIT(level, root);

        PIT left(-1, nullptr), right(-1, nullptr);
        if(root -> left)
            left = _postOrder(root -> left, level + 1);
        if(root -> right)
            right = _postOrder(root -> right, level + 1);
        if(left.first == right.first)
            return PIT(left.first, root);
        else if(left.first > right.first)
            return left;
        else
            return right;
    }
};
