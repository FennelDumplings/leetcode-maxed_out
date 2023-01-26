// prob141:

/*
 * Given a linked list, determine if it has a cycle in it.
 * To represent a cycle in the given linked list, we use an integer
 * pos which represents the position (0-indexed) in the linked list where tail connects to.
 * If pos is -1, then there is no cycle in the linked list.
 */

/*
 * Example 1:
 * Input: head = [3,2,0,-4], pos = 1
 * Output: true
 */

#include "include/Node.h"

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == nullptr || head -> next == nullptr) return false;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *slow = dummy;
        ListNode *fast = dummy;
        while(slow != nullptr && fast != nullptr && fast -> next != nullptr)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
            if(slow == fast) return true;
        }
        return false;
    }
};
