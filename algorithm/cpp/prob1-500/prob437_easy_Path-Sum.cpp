// prob437: Path Sum

/*
 * You are given a binary tree in which each node contains an integer value.
 * Find the number of paths that sum to a given value.
 * The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
 * The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000
 */

#include <vector>
#include <unordered_map>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        if(!root) return 0;
        mapping = unordered_map<int, int>();
        mapping[0] = 1;
        int ans = 0;
        _preOrder(root, targetSum, 0, ans);
        return ans;
    }

private:
    unordered_map<int, int> mapping;

    void _preOrder(TreeNode* node, const int targetSum, int presum, int& ans)
    {
        presum += node -> val;
        ans += mapping[presum - targetSum];
        ++mapping[presum];
        if(node -> left)
            _preOrder(node -> left, targetSum, presum, ans);
        if(node -> right)
            _preOrder(node -> right, targetSum, presum, ans);
        --mapping[presum];
    }
};
