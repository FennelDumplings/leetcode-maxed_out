// prob971: Flip Binary Tree To Match Preorder Traversal

/*
 * Given a binary tree with N nodes, each node has a different value from {1, ..., N}.
 * A node in this binary tree can be flipped by swapping the left child and the right child of that node.
 * Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a
 * sequence of N values the voyage of the tree.
 * (Recall that a preorder traversal of a node means we report the current node's value, then
 * preorder-traverse the left child, then preorder-traverse the right child.)
 * Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.
 * If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.
 * If we cannot do so, then return the list [-1].
 */

/*
 * Example 1:
 * Input: root = [1,2], voyage = [2,1]
 * Output: [-1]
 * Example 2:
 * Input: root = [1,2,3], voyage = [1,3,2]
 * Output: [1]
 * Example 3:
 * Input: root = [1,2,3], voyage = [1,2,3]
 * Output: []
 */

/*
 * Note:
 * 1 <= N <= 100
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        if(root -> val != voyage[0])
            return vector<int>({-1});
        vector<int> result;
        int n = voyage.size();
        vector<int> mapping(n + 1, -1);
        for(int i = 0; i < n; ++i)
            mapping[voyage[i]] = i;
        _preOrder(root, result, voyage, 0, n - 1, mapping);
        return result;
    }

private:
    bool _preOrder(TreeNode* root, vector<int>& result, vector<int>& voyage, int left, int right, const vector<int>& mapping)
    {
        // 调用方保证 root -> val == result[left]
        if(!root -> left && !root -> right)
            return true;
        if(!root -> right)
        {
            if(root -> left -> val != voyage[left + 1])
            {
                result.clear();
                result.push_back(-1);
                return false;
            }
            else
                return _preOrder(root -> left, result, voyage, left + 1, right, mapping);
        }
        if(!root -> left)
        {
            if(root -> right -> val != voyage[left + 1])
            {
                result.clear();
                result.push_back(-1);
                return false;
            }
            else
                return _preOrder(root -> right, result, voyage, left + 1, right, mapping);
        }

        int root_left_idx = mapping[root -> left -> val];
        if(root_left_idx > right || root_left_idx < left)
        {
            result.clear();
            result.push_back(-1);
            return false;
        }
        int root_right_idx = mapping[root -> right -> val];
        if(root_right_idx > right || root_right_idx < left)
        {
            result.clear();
            result.push_back(-1);
            return false;
        }

        if(root_left_idx == left + 1)
        {
            if(!_preOrder(root -> left, result, voyage, left + 1, root_right_idx - 1, mapping))
                return false;
            if(!_preOrder(root -> right, result, voyage, root_right_idx, right, mapping))
                return false;
        }
        else if(root_right_idx == left + 1)
        {
            result.push_back(root -> val);
            if(!_preOrder(root -> right, result, voyage, left + 1, root_left_idx - 1, mapping))
                return false;
            if(!_preOrder(root -> left, result, voyage, root_left_idx, right, mapping))
                return false;
        }
        else
        {
            result.clear();
            result.push_back(-1);
            return false;
        }
        return true;
    }
};
