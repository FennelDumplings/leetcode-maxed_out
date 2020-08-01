// interview24: 反转链表

/*
 * https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head -> next) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        ListNode *iter = head;
        while(iter)
        {
            ListNode *tmp = iter;
            iter = iter -> next;
            tmp -> next = dummy -> next;
            dummy -> next = tmp;
        }
        return dummy -> next;
    }
};
