// inerview02.07: 链表相交

/*
 * https://leetcode-cn.com/problems/intersection-of-two-linked-lists-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return nullptr;
        int lenA = get_len(headA);
        int lenB = get_len(headB);
        if(lenB > lenA)
            return get_intersection(headB, headA, lenB - lenA);
        else
            return get_intersection(headA, headB, lenA - lenB);
    }

private:
    ListNode* get_intersection(ListNode *longer, ListNode *shorter, int diff)
    {
        ListNode *iter1 = longer;
        for(int i = 1; i <= diff; ++i)
            iter1 = iter1 -> next;
        ListNode *iter2 = shorter;
        while(iter1)
        {
            if(iter1 == iter2)
                return iter1;
            iter1 = iter1 -> next;
            iter2 = iter2 -> next;
        }
        return nullptr;
    }

    int get_len(ListNode* head)
    {
        int result = 0;
        while(head)
        {
            ++result;
            head = head -> next;
        }
        return result;
    }
};
