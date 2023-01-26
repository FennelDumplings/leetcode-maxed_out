// interview54: 二叉搜索树的第k大节点

/*
 * https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    int kthLargest(TreeNode* root, int k) {
        if(!root) return 0;
        int result = -1;
        int rank = 0;
        _inOrder(root, rank, k, result);
        return result;
    }

private:
    void _inOrder(TreeNode* node, int& rank, int k, int& result)
    {
        if(rank == k) return;
        if(node -> right)
            _inOrder(node -> right, rank, k, result);
        ++rank;
        if(rank == k)
        {
            result = node -> val;
        }
        if(node -> left)
            _inOrder(node -> left, rank, k, result);
    }
};
