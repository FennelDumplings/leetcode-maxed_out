// Prob206: Reverse Linked List

/*Description
 * Reverse a Linked List
 */

/*
 * Input: 1->2->3->4->5->NULL
 * Output: 5->4->3->2->1->NULL
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include "include/Node.h"

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 空链表
        if(head == nullptr) return head;
        // 只有一个元素的链表
        if(head -> next == nullptr) return head;

        // 至少两个元素，prev初始为第一个，iter初始为第二个
        ListNode *prev = head;
        ListNode *iter = head -> next;
        ListNode *tmp = nullptr;

        while(iter -> next != nullptr)
        {
            tmp = iter -> next;
            iter -> next = prev;
            prev = iter;
            iter = tmp;
        }

        iter -> next = prev;
        head -> next = nullptr;
        head = iter;

        return head;
    }
};


class Solution_Recurrsion {
public:
    ListNode* reverseList(ListNode* head) {
        // 空链表
        if(head == nullptr) return head;
        // 只有一个元素的链表
        if(head -> next == nullptr) return head;

        // 至少两个元素，iter初始为第二个
        ListNode *iter = head -> next;
        head -> next = nullptr;
        ListNode *result = reverseList(iter);
        iter -> next = head;
        return result;
    }
};
