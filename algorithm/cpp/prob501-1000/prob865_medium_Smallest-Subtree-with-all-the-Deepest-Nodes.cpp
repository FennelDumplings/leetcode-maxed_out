// prob865: Smallest Subtree with all the Deepest Nodes

/*
 * Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.
 * A node is deepest if it has the largest depth possible among any node in the entire tree.
 * The subtree of a node is that node, plus the set of all descendants of that node.
 * Return the node with the largest depth such that it contains all the deepest nodes in its subtree.
 */

/*
 * Example 1:
 * Input: [3,5,1,6,2,0,8,null,null,7,4]
 * Output: [2,7,4]
 * Explanation:
 * We return the node with value 2, colored in yellow in the diagram.
 * The nodes colored in blue are the deepest nodes of the tree.
 * The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
 * The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
 * Both the input and output have TreeNode type.
 */

/*
 * Note:
 * The number of nodes in the tree will be between 1 and 500.
 * The values of each node are unique.
 */

#include "include/Node.h"
#include <unordered_map>

using namespace std;

class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        unordered_map<TreeNode*, PII> mapping;
        int deep = _postOrder(root, mapping, 0);
        TreeNode *result = root;
        int max_deep = 0;
        _preOrder(root, mapping, result, deep, max_deep);
        return result;
    }

private:
    using PII = pair<int, int>;
    int _postOrder(TreeNode* root, unordered_map<TreeNode*, PII>& mapping, int level)
    {
        // 记录子树 root 的最深的叶子的 level, 和 root 本身的 level
        int most_deep_left = level, most_deep_right = level;
        if(root -> left)
        {
            most_deep_left = _postOrder(root -> left, mapping, level + 1);
        }
        if(root -> right)
        {
            most_deep_right = _postOrder(root -> right, mapping, level + 1);
        }
        int most_deep = max(most_deep_left, most_deep_right);
        mapping[root] = PII({most_deep, level});
        return most_deep;
    }

    void _preOrder(TreeNode* root, unordered_map<TreeNode*, PII>& mapping, TreeNode*& result, int deep, int& max_deep)
    {
        if(mapping[root].second > max_deep)
        {
            max_deep = mapping[root].second;
            result = root;
        }
        if(!(root -> right) && root -> left)
            _preOrder(root -> left, mapping, result, deep, max_deep);
        if(!(root -> left) && root -> right)
            _preOrder(root -> right, mapping, result, deep, max_deep);
        if(root -> left && root -> right)
        {
            if(mapping[root -> left].first < deep)
                _preOrder(root -> right, mapping, result, deep, max_deep);
            if(mapping[root -> right].first < deep)
                _preOrder(root -> left, mapping, result, deep, max_deep);
        }
    }
};
