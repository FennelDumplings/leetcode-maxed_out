// prob203: Remove Linked List Elements

/*
 * Remove all elements from a linked list of integers that have value val.
 * Example:
 * Input:  1->2->6->3->4->5->6, val = 6
 * Output: 1->2->3->4->5
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        while(iter -> next)
        {
            if(iter -> next -> val == val)
                iter -> next = iter -> next -> next;
            else
                iter = iter -> next;
        }
        return dummy -> next;
    }
};
