// prob234: Palindrome Linked List

/*
 * Given a singly linked list, determine if it is a palindrome.
 */

#include "include/Node.h"

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head || !(head -> next)) return true;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *slow = dummy, *fast = dummy;
        while(fast && fast -> next)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        ListNode *pretail = slow;
        slow = slow -> next; // 后半部分
        pretail -> next = nullptr;
        slow = _reverseList(slow);

        ListNode *iter1 = head, *iter2 = slow;
        while(iter2 != nullptr)
        {
            if(iter1 -> val != iter2 -> val)
            {
                slow = _reverseList(slow);
                pretail -> next = slow;
                return false;
            }
            iter1 = iter1 -> next;
            iter2 = iter2 -> next;
        }
        slow = _reverseList(slow);
        pretail -> next = slow;
        return true;
    }

private:
    // 反转链表，leetcode 206
    ListNode* _reverseList(ListNode* head) {
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
