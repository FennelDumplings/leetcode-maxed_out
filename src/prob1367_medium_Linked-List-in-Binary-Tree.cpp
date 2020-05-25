// prob1367: Linked List in Binary Tree

/*
 * Given a binary tree root and a linked list with head as the first node. 
 * Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
 * In this context downward path means a path that starts at some node and goes downwards.
 */

/*
 * Example 1:
 * Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
 * Output: true
 * Explanation: Nodes in blue form a subpath in the binary Tree.
 * Example 2:
 * Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
 * Output: true
 * Example 3:
 * Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
 * Output: false
 * Explanation: There is no path in the binary tree that contains all the elements of the linked list from head.
 */

/*
 * Constraints:
 * 1 <= node.val <= 100 for each node in the linked list and binary tree.
 * The given linked list will contain between 1 and 100 nodes.
 * The given binary tree will contain between 1 and 2500 nodes.
 */

#include "include/Node.h"

// 也可参考 572 的写法
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        return _preOrder(root, head, head);

    }

private:
    bool _preOrder(TreeNode* root, ListNode* iter, ListNode*& head)
    {
        // 返回 root 子树和 iter 子链表是否成立
        if(root -> val == iter -> val)
        {
            if(!iter -> next) return true;
            if(root -> left)
                if(_preOrder(root -> left, iter -> next, head))
                    return true;
            if(root -> right)
                if(_preOrder(root -> right, iter -> next, head))
                    return true;
        }

        // iter 与 root 不匹配
        if(iter == head)
        {
            if(root -> left)
                if(_preOrder(root -> left, head, head))
                    return true;
            if(root -> right)
                if(_preOrder(root -> right, head, head))
                    return true;
        }

        return false;
    }
};
