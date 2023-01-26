// prob92: Reverse Linked List

/*
 * Reverse a linked list from position m to n. Do it in one-pass.
 * Note: 1 ≤ m ≤ n ≤ length of list.
 */

/*
 * Example:
 * Input: 1->2->3->4->5->NULL, m = 2, n = 4
 * Output: 1->4->3->2->5->NULL
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // 调用方保证 head 不为空(长度至少是1)，且 1 <= m <= n <= 长度
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;

        // iter 前进 m - 1次
        for(int i = 0; i < m - 1; ++i)
            iter = iter -> next;

        // n - m 次操作(反转 n - m + 1 个点)
        // 一次操作包含一次删除和一次插入
        ListNode *pretail = iter;
        ListNode *prev = iter -> next;
        iter = iter -> next -> next;
        for(int i = 0; i < n - m; ++i)
        {
            prev -> next = iter -> next;
            iter -> next = pretail -> next;
            pretail -> next = iter;
            iter = prev -> next;
        }
        return dummy -> next;
    }
};
