// interview04.04: 检查平衡性

/*
 * 实现一个函数，检查二叉树是否平衡。在这个问题中，平衡树的定义如下：任意一个节点，其两棵子树的高度差不超过 1。
 */

/*
 * 示例 1:
 * 给定二叉树 [3,9,20,null,null,15,7]
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * 返回 true 。
 * 示例 2:
 * 给定二叉树 [1,2,2,3,3,null,null,4,4]
 *       1
 *      / \
 *     2   2
 *    / \
 *   3   3
 *  / \
 * 4   4
 * 返回 false 。
 * /
 */

#include "include/Node.h"
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        return _postOrder(root) != -1;
    }

private:
    int _postOrder(TreeNode* root)
    {
        int h_l = 0, h_r = 0;
        if(root -> left)
        {
            h_l = _postOrder(root -> left);
            if(h_l == -1)
                return -1;
        }
        if(root -> right)
        {
            h_r = _postOrder(root -> right);
            if(h_r == -1)
                return -1;
        }
        if(abs(h_r - h_l) > 1)
            return -1;
        return 1 + max(h_l, h_r);
    }
};
