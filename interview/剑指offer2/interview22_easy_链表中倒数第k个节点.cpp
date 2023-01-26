// interview22: 链表中倒数第k个节点

/*
 * https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
 */

#include "../../include/Node.h"

class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        if(!head) return nullptr;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *pretail = dummy;
        ListNode *iter = dummy;
        for(int i = 1; i <= k; ++i)
        {
            if(iter -> next)
                iter = iter -> next;
        }
        while(iter -> next)
        {
            iter = iter -> next;
            pretail = pretail -> next;
        }
        return pretail -> next;
    }
};
