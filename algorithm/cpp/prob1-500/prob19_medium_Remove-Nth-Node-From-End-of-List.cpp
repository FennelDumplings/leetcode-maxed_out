// prob19: Remove Nth Node From End of List

/*
 * Given a linked list, remove the n-th node from the end of list and return its head.
 */

/*
 * Example:
 * Given linked list: 1->2->3->4->5, and n = 2.
 * After removing the second node from the end, the linked list becomes 1->2->3->5.
 */

/*
 * Note:
 * Given n will always be valid.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == nullptr || n == 0) return head;

        ListNode *start = head;
        for(int i = 0; i < n; ++i)
            start = start -> next;
        if(start == nullptr)
        {
            head = head -> next;
            return head;
        }
        start = start -> next;
        ListNode *target = head;
        while(start != nullptr)
        {
            start = start -> next;
            target = target -> next;
        }
        target -> next = target -> next -> next;
        return head;
    }
};
