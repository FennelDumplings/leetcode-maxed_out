// prob876: Middle of the Linked List

/*
 * Given a non-empty, singly linked list with head node head, return a middle node of linked list.
 * If there are two middle nodes, return the second middle node.
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode *slow = head, *fast = head;
        while(fast != nullptr && fast -> next != nullptr)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }
};
