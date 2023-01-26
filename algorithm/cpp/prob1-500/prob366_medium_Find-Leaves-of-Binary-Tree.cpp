// prob366: Find Leaves of Binary Tree

/*
 * Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.
 */

/*
 * Example:
 * Input: [1,2,3,4,5]
 *           1
 *          / \
 *         2   3
 *        / \
 *       4   5
 * Output: [[4,5,3],[2],[1]]
 * Explanation:
 * 1. Removing the leaves [4,5,3] would result in this tree:
 *           1
 *          /
 *         2
 * 2. Now removing the leaf [2] would result in this tree:
 *           1
 * 3. Now removing the leaf [1] would result in the empty tree:
 *           []
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        if(!root) return vector<vector<int> >();
        vector<vector<int> > result;
        _postOrder(root, result);
        return result;
    }

private:
    int _postOrder(TreeNode* root, vector<vector<int> >& result)
    {
        int h_left = 0, h_right = 0;
        if(root -> left)
            h_left = _postOrder(root -> left, result);
        if(root -> right)
            h_right = _postOrder(root -> right, result);
        int h = max(h_left, h_right) + 1;
        // 叶子节点 h = 0
        if((int)result.size() < h)
            result.push_back(vector<int>());
        result[h - 1].push_back(root -> val);
        return h;
    }
};
