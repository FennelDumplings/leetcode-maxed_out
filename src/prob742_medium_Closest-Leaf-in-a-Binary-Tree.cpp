// prob742: Closest Leaf in a Binary Tree

/*
 * Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.
 * Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a
 * node is called a leaf if it has no children.
 * In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.
 */

/*
 * Example 1:
 * Input:
 * root = [1, 3, 2], k = 1
 * Diagram of binary tree:
 *           1
 *          / \
 *         3   2
 * Output: 2 (or 3)
 * Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
 * Example 2:
 * Input:
 * root = [1], k = 1
 * Output: 1
 * Explanation: The nearest leaf node is the root node itself.
 * Example 3:
 * Input:
 * root = [1,2,3,4,null,null,null,5,null,6], k = 2
 * Diagram of binary tree:
 *              1
 *             / \
 *            2   3
 *           /
 *          4
 *         /
 *        5
 *       /
 *      6
 * Output: 3
 * Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
 */

/*
 * Note:
 * root represents a binary tree with at least 1 node and at most 1000 nodes.
 * Every node has a unique node.val in range [1, 1000].
 * There exists some node in the given binary tree for which node.val == k.
 */

#include <unordered_map>
#include <climits>
#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int findClosestLeaf(TreeNode* root, int k) {
        unordered_map<TreeNode*, int> path;
        unordered_map<TreeNode*, TreeNode*> father;
        vector<TreeNode*> leaves;
        TreeNode *target = _postOrder(root, father, leaves, path, 0, k);
        int min_len = INT_MAX;
        int result = 0;
        for(TreeNode* leaf: leaves)
        {
            TreeNode *iter = leaf;
            int len = 0;
            while(path.find(iter) == path.end())
            {
                iter = father[iter];
                ++len;
            }
            len += path[target] - path[iter];
            if(min_len > len)
            {
                result = leaf -> val;
                min_len = len;
            }
        }
        return result;
    }

private:
    TreeNode* _postOrder(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& father,
            vector<TreeNode*>& leaf, unordered_map<TreeNode*, int>& path, int level, int k)
    {
        // 返回值表示该子树是否在 path 上
        // unorderd_map 记录所有节点的父节点
        // vector 记录所有叶子节点
        // unordered_map 记录所有到目标节点路径上的所有点及其到根的距离
        if(!(root -> left) && !(root -> right))
            leaf.push_back(root);
        TreeNode *target_left = nullptr, *target_right = nullptr;
        TreeNode *target = nullptr;
        if(root -> left)
        {
            father[root -> left] = root;
            target_left = _postOrder(root -> left, father, leaf, path, level + 1, k);
            if(target_left) target = target_left;
        }
        if(root -> right)
        {
            father[root -> right] = root;
            target_right = _postOrder(root -> right, father, leaf, path, level + 1, k);
            if(target_right) target = target_right;
        }

        if(root -> val == k)
            target = root;
        if(target)
            path[root] = level;
        return target;
    }
};
