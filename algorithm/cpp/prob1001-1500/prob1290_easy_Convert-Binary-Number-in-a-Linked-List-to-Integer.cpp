// prob1290: Convert Binary Number in a Linked List to Integer

/*
 * https://leetcode-cn.com/problems/convert-binary-number-in-a-linked-list-to-integer/
 */

#include "include/Node.h"

class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int num = 0;
        ListNode *iter = head;
        while(iter)
        {
            num <<= 1;
            num += iter -> val;
            iter = iter -> next;
        }
        return num;
    }
};
