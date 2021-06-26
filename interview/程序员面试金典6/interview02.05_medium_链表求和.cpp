// interview02.05: 链表求和

/*
 * https://leetcode-cn.com/problems/sum-lists-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(!l1) return l2;
        if(!l2) return l1;
        ListNode *iter1 = l1;
        ListNode *iter2 = l2;
        int carry = 0;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        ListNode *result = dummy;
        while(iter1 && iter2)
        {
            int sum = iter1 -> val + iter2 -> val + carry;
            int digit = sum % 10;
            result -> next = new ListNode(digit);
            result = result -> next;
            carry = sum / 10;
            iter1 = iter1 -> next;
            iter2 = iter2 -> next;
        }
        while(iter1)
        {
            int sum = iter1 -> val + carry;
            int digit = sum % 10;
            result -> next = new ListNode(digit);
            result = result -> next;
            carry = sum / 10;
            iter1 = iter1 -> next;
        }
        while(iter2)
        {
            int sum = iter2 -> val + carry;
            int digit = sum % 10;
            result -> next = new ListNode(digit);
            result = result -> next;
            carry = sum / 10;
            iter2 = iter2 -> next;
        }
        if(carry)
        {
            result -> next = new ListNode(carry);
            result = result -> next;
        }
        return dummy -> next;
    }
};
