// interview04.12: 求和路径

/*
 * https://leetcode-cn.com/problems/paths-with-sum-lcci/
 */

#include "../../include/Node.h"
#include <unordered_map>

using namespace std;

class Solution {
public:
    int pathSum(TreeNode* root, int target) {
        if(!root) return 0;
        unordered_map<int, int> mapping;
        mapping[0] = 1;
        int ans = 0;
        _preOrder(root, target, root -> val, mapping, ans);
        return ans;
    }

private:
    void _preOrder(TreeNode* node, const int target, int sum, unordered_map<int, int>& mapping, int& ans)
    {
        int gap = sum - target;
        ans += mapping[gap];
        ++mapping[sum];
        if(node -> left)
            _preOrder(node -> left, target, sum + node -> left -> val, mapping, ans);
        if(node -> right)
            _preOrder(node -> right, target, sum + node -> right -> val, mapping, ans);
        --mapping[sum];
    }
};
