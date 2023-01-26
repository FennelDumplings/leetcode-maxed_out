// prob369: Plus One Linked List

/*
 * https://leetcode-cn.com/problems/plus-one-linked-list/
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* plusOne(ListNode* head) {
        head = reverse(head);
        ListNode *iter = head;
        int carry = 1;
        ListNode *pretail = nullptr;
        while(iter != nullptr || carry > 0)
        {
            int d = carry;
            if(iter)
            {
                d += iter -> val;
                pretail = iter;
                iter -> val = d % 10;
                iter = iter -> next;
            }
            else
            {
                ListNode *tmp = new ListNode(d % 10);
                pretail -> next = tmp;
                pretail = tmp;
            }
            carry = d / 10;
        }
        return reverse(head);
    }

private:
    ListNode* reverse(ListNode* head)
    {
        if(!head) return head;
        ListNode *iter = head;
        ListNode *pretail = nullptr;
        while(iter)
        {
            ListNode *tmp = iter -> next;
            iter -> next = pretail;
            pretail = iter;
            iter = tmp;
        }
        return pretail;
    }
};

