// interview55-2: 平衡二叉树

/*
 * https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof/
 */

#include "../../include/Node.h"
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        PBI result = _postOrder(root);
        return result.first;
    }

private:
    using PBI = pair<bool, int>;

    PBI _postOrder(TreeNode* node)
    {
        PBI left(true, 0), right(true, 0);
        if(node -> left)
            left = _postOrder(node -> left);
        if(node -> right)
            right = _postOrder(node -> right);
        int diff = abs(left.second - right.second);
        bool flag = left.first && right.first && diff <= 1;
        int h = 1 + max(left.second, right.second);
        return PBI(flag, h);
    }
};
