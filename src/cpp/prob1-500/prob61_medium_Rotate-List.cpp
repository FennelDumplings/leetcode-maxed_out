// prob61: Rotate List

/*
 * Given a linked list, rotate the list to the right by k places, where k is non-negative.
 */

/*
 * Example 1:
 * Input: 1->2->3->4->5->NULL, k = 2
 * Output: 4->5->1->2->3->NULL
 * Example 2:
 * Input: 0->1->2->NULL, k = 4
 * Output: 2->0->1->NULL
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !k) return head;
        // k > 0, head 非空
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy, *prev = dummy;
        int n = 0;
        int k_iter = k;
        while(iter -> next && k_iter)
        {
            iter = iter -> next;
            --k_iter;
            ++n;
        }
        if(!(iter -> next))
        {
            k_iter = k % n;
            if(k_iter == 0) return head;
            iter = dummy;
            while(iter -> next && k_iter)
            {
                iter = iter -> next;
                --k_iter;
                ++n;
            }
        }
        while(iter -> next)
        {
            iter = iter -> next;
            prev = prev -> next;
        }
        iter -> next = dummy -> next;
        dummy -> next = prev -> next;
        prev -> next = nullptr;
        return dummy -> next;
    }
};
