// prob82: Remove Duplicates from Sorted List

/*
 * Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 * Return the linked list sorted as well.
 */

/*
 * Example 1:
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->5
 * Example 2:
 * Input: 1->1->1->2->3
 * Output: 2->3
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !(head -> next)) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        while(iter -> next && iter -> next -> next)
        {
            if(iter -> next -> val != iter -> next -> next -> val)
                iter = iter -> next;
            else
            {
                ListNode *right = iter -> next -> next;
                while(right -> next && right -> next -> val == right -> val)
                    right = right -> next;
                iter -> next = right -> next;
            }
        }
        return dummy -> next;
    }
};
