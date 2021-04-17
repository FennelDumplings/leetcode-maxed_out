// prob86: Partition List

/*
 * Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of the two partitions.
 */

/*
 * Example:
 * Input: head = 1->4->3->2->5->2, x = 3
 * Output: 1->2->2->4->3->5
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(!head || !(head -> next)) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        while(iter -> next && iter -> next -> val < x)
            iter = iter -> next;
        if(!(iter -> next)) return dummy -> next;
        ListNode *partition_point = iter;
        iter = iter -> next;
        while(iter -> next)
        {
            if(iter -> next -> val >= x)
            {
                iter = iter -> next;
                continue;
            }
            ListNode *tmp = iter -> next;
            iter -> next = tmp -> next;
            tmp -> next = partition_point -> next;
            partition_point -> next = tmp;
            partition_point = partition_point -> next;
        }
        return dummy -> next;
    }
};
