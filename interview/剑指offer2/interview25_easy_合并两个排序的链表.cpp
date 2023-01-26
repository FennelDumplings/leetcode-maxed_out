// interview25: 合并两个排序的链表

/*
 * https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1) return l2;
        if(!l2) return l1;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        ListNode *pretail = dummy;
        while(l1 && l2)
        {
            if(l1 -> val < l2 -> val)
            {
                pretail -> next = l1;
                l1 = l1 -> next;
            }
            else
            {
                pretail -> next = l2;
                l2 = l2 -> next;
            }
            pretail = pretail -> next;
        }
        if(l1)
            pretail -> next = l1;
        else
            pretail -> next = l2;
        return dummy -> next;
    }
};
