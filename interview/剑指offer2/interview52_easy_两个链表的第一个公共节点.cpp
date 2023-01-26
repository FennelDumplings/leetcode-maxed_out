// interview52: 两个链表的第一个公共节点

/*
 * https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/
 */

#include "../../include/Node.h"
#include <cmath>

using namespace std;

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return nullptr;
        int len1 = get_len(headA);
        int len2 = get_len(headB);
        if(len2 < len1) return getIntersectionNode(headB, headA);
        // len1 <= len2
        int diff = len2 - len1;
        // 0 -> 0
        // 0 -> 0 -> 0 -> 0
        // headB先往前走 diff
        for(int i = 1; i <= diff; ++i)
        {
            headB = headB -> next;
        }
        while(headA && headB && headA != headB)
        {
            headA = headA -> next;
            headB = headB -> next;
        }
        return headA;
    }

private:
    int get_len(ListNode* head)
    {
        int len = 0;
        while(head)
        {
            head = head -> next;
            ++len;
        }
        return len;
    }
};
