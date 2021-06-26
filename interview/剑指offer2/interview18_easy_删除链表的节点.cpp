// interview18: 删除链表的节点

/*
 * https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/
 */


#include "../../include/Node.h"

class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(!head) return nullptr;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        while(iter -> next)
        {
            if(iter -> next -> val == val)
            {
                iter -> next = iter -> next -> next;
                break;
            }
            else
                iter = iter -> next;
        }
        return dummy -> next;
    }
};
