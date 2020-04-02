// prob99: Recover Binary Search Tree

/*
 * Two elements of a binary search tree (BST) are swapped by mistake.
 * Recover the tree without changing its structure.
 */

/*
 * Follow up:
 * A solution using O(n) space is pretty straight forward.
 * Could you devise a constant space solution?
 */

#include "include/Node.h"
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// 递归中序
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *prev = nullptr;
        PTT result(nullptr, nullptr);
        _inOrder(root, prev, result, false);
        swap(result.first -> val, result.second -> val);
    }

private:
    using PTT = pair<TreeNode*, TreeNode*>;

    void _inOrder(TreeNode* root, TreeNode*& prev, PTT& result, bool flag)
    {
        // 调用方保证 root 合法
        // 每次递归只对比 root 及其中序前驱
        if(flag) return;

        if(root -> left)
            _inOrder(root -> left, prev, result, flag);

        if(prev && prev -> val >= root -> val)
        {
            result.second = root;
            if(!result.first)
                result.first = prev;
            else // 第二次 swap 出现时返回
            {
                flag = true;
                return;
            }
        }

        prev = root;

        if(root -> right)
            _inOrder(root -> right, prev, result, flag);
    }
};

// 非递归中序


// Morris 遍历 (二叉线索树)


