// prob 160 Intersection of Two Linked Lists

/*
 * Write a program to find the node at which the intersection of two singly linked lists begins.
 */

/*
 * Notes:
 * If the two linked lists have no intersection at all, return null.
 * The linked lists must retain their original structure after the function returns.
 * You may assume there are no cycles anywhere in the entire linked structure.
 * Your code should preferably run in O(n) time and use only O(1) memory.
 */

#include "include/Node.h"

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr)
            return nullptr;

        int len_A = length(headA);
        int len_B = length(headB);
        if(len_A > len_B)
            for(int i = 0; i < (len_A - len_B); ++i)
                headA = headA -> next;
        if(len_A < len_B)
            for(int i = 0; i < (len_B - len_A); ++i)
                headB = headB -> next;

        while(headA != headB)
        {
            headA = headA -> next;
            headB = headB -> next;
        }
        return headA;
    }

private:
    int length(ListNode *head)
    {
        int i = 0;
        while(head != nullptr)
        {
            head = head -> next;
            ++i;
        }
        return i;
    }
};


