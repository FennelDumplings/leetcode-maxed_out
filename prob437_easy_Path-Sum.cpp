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
    int pathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        int result = 0;
        vector<int> sums(1, 0);
        unordered_map<int, int> mapping;
        mapping.insert(PII(0, 1));
        _preOrder(root, result, sums, mapping, sum);
        return result;
    }

private:
    using PII = pair<int, int>;

    void _preOrder(TreeNode* root, int& result, vector<int>& sums,
            unordered_map<int, int>& mapping, int target)
    {
        // 调用方保证 root 合法
        int cur = root -> val;
        int cur_sum = cur + sums.back();
        int gap = cur_sum - target;
        if(mapping.find(gap) != mapping.end())
            result += mapping[gap];

        if(!(root -> left) && !(root -> right))
            return;

        sums.push_back(cur_sum);
        if(mapping.find(cur_sum) != mapping.end())
            ++mapping[cur_sum];
        else
            mapping[cur_sum] = 1;

        if(root -> left)
            _preOrder(root -> left, result, sums, mapping, target);
        if(root -> right)
            _preOrder(root -> right, result, sums, mapping, target);

        sums.pop_back();
        if(mapping[cur_sum] == 1)
            mapping.erase(mapping.find(cur_sum));
        else
            --mapping[cur_sum];
    }
};
