// prob328: Odd Even Linked List

/*
 * Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.
 * You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.
 */

/*
 * Example 1:
 * Input: 1->2->3->4->5->NULL
 * Output: 1->3->5->2->4->NULL
 * Example 2:
 * Input: 2->1->3->5->6->4->7->NULL
 * Output: 2->3->6->7->1->5->4->NULL
 */

/*
 * Constraints:
 * The relative order inside both the even and odd groups should remain as it was in the input.
 * The first node is considered odd, the second node even and so on ...
 * The length of the linked list is between [0, 10^4].
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head -> next || !head -> next -> next)
            return head;
        ListNode *iter_odd = head;
        ListNode *iter_even = head -> next;
        ListNode *iter = head -> next -> next;
        ListNode *head_even = head -> next;
        iter_odd -> next = nullptr;
        iter_even -> next = nullptr;
        int odd = 1;
        while(iter)
        {
            if(odd & 1)
            {
                iter_odd -> next = iter;
                iter_odd = iter_odd -> next;
                iter_odd -> next = nullptr;
            }
            else
            {
                iter_even -> next = iter;
                iter_even = iter_even -> next;
                iter_even -> next = nullptr;
            }
            iter = iter -> next;
            odd ^= 1;
        }
        iter_odd -> next = head_even;
        return head;
    }
};
