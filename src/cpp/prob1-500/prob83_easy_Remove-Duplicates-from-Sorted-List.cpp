// prob83: Remove Duplicates from Sorted List

/*
 * Given a sorted linked list, delete all duplicates such that each element appear only once.
 */

/*
 * Example 1:
 * Input: 1->1->2
 * Output: 1->2
 * Example 2:
 * Input: 1->1->2->3->3
 * Output: 1->2->3
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
                iter = iter -> next;
                iter -> next = right -> next;
            }
        }
        return dummy -> next;
    }
};
