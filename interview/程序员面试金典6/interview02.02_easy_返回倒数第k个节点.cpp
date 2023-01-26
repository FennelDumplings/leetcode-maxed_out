// interview02.02: 返回倒数第 k 个节点

/*
 * 实现一种算法，找出单向链表中倒数第 k 个节点。返回该节点的值。
 * 注意：本题相对原题稍作改动
 */

#include "include/Node.h"

class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *left = dummy;
        ListNode *right = left;
        for(int i = 0; i < k; ++i)
            right = right -> next;
        while(right -> next)
        {
            right = right -> next;
            left = left -> next;
        }
        return left -> next -> val;
    }
};
