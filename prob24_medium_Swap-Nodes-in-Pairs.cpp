// prob24: Swap Nodes in Pairs

/*
 * Given a linked list, swap every two adjacent nodes and return its head.
 * You may not modify the values in the list's nodes, only nodes itself may be changed.
 */

/*
 * example:
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
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

// 递归
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        return _swapPairs(head);
    }

private:
    ListNode* _swapPairs(ListNode* head)
    {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode *tmp = head -> next;
        head -> next = head -> next -> next;
        tmp -> next = head;
        head = tmp;
        head -> next -> next = _swapPairs(head -> next -> next);
        return head;
    }
};

// 非递归
class Solution_2 {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;

        ListNode *tmp = head -> next;
        head -> next = head -> next -> next;
        tmp -> next = head;
        head = tmp;

        ListNode *iter = head -> next;
        while(iter -> next != nullptr && iter -> next -> next != nullptr)
        {
            tmp = iter -> next -> next;
            iter -> next -> next = iter -> next -> next -> next;
            tmp -> next = iter -> next;
            iter -> next = tmp;
            iter = iter -> next -> next;
        }
        return head;
    }
};
