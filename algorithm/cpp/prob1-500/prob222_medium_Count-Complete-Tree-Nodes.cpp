// prob222: Count Complete Tree Nodes

/*
 * Given a complete binary tree, count the number of nodes.
 */

/*
 *Example:
 * Input:
 *     1
 *    / \
 *   2   3
 *  / \  /
 * 4  5 6
 * Output: 6
 */

#include "include/Node.h"
#include <cmath>

// 先求树的高度(h + 1 层的数，高度是 h)
// 节点个数 1 ~ 2^h
// 以高度为3为例，路径对应的二进制编码 000 ~ 111
// check():由编码得到路径看结果是否为空
class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        int h = 0;
        TreeNode *iter = root -> left;
        while(iter != nullptr)
        {
            ++h;
            iter = iter -> left;
        }
        if(h == 0) return 1;
        // 高度至少为1, 至少两层
        long long left = 1;
        long long right = (1 << h) - 1;
        while(left < right)
        {
            long long mid = left + (right - left) / 2;
            if(check(mid, h, root))
                left = mid + 1;
            else
                right = mid - 1;
        }
        long long result = (1 << h) - 1;
        if(check(left, h, root))
            result += left + 1;
        else
            result += left;
        return (int)result;
    }

private:
    bool check(long long mid, int h, TreeNode* root)
    {
        TreeNode *iter = root;
        for(int i = h - 1; i >= 0; --i)
        {
            if((mid >> i & 1) == 1)
                iter = iter -> right;
            else
                iter = iter-> left;
        }
        if(iter == nullptr)
            return false;
        else
            return true;
    }
};
