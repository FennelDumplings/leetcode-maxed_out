// prob143: Reorder List

/*
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 * You may not modify the values in the list's nodes, only nodes itself may be changed.
 */

/*
 * Example 1:
 * Given 1->2->3->4, reorder it to 1->4->2->3.
 * Example 2:
 * Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
 */

#include "include/Node.h"
#include <stack>

using namespace std;

class Solution_2 {
public:
    void reorderList(ListNode* head) {
        if(!head) return;
        stack<ListNode*> st;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        while(iter -> next)
        {
            ListNode *cur = iter -> next;
            st.push(cur);
            iter = iter -> next;
        }
        iter = dummy;
        int flag = 1;
        ListNode *left = head;
        while(left != st.top())
        {
            if(flag & 1)
            {
                iter -> next = left;
                left = left -> next;
                iter = iter -> next;
                flag ^= 1;
            }
            else
            {
                ListNode *right = st.top();
                iter -> next = right;
                st.pop();
                iter = iter -> next;
                flag ^= 1;
            }
        }
        iter -> next = left;
        iter = iter -> next;
        iter -> next = nullptr;
        head = dummy -> next;
    }
};

// 1. 快慢指针找中点
class Solution_206 {
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

class Solution_786 {
public:
    ListNode* middleNode(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode *slow = head, *fast = head;
        while(fast != nullptr && fast -> next != nullptr)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return slow;
    }
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head) return;
        Solution_786 solution786;
        Solution_206 solution206;
        ListNode *middlenode = solution786.middleNode(head);
        middlenode = solution206.reverseList(middlenode);
        ListNode *iter1 = head, *iter2 = middlenode;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        ListNode *iter = dummy;
        int flag = 1;
        while(iter1 != iter2)
        {
            if(flag & 1)
            {
                iter -> next = iter1;
                iter1 = iter1 -> next;
                iter = iter -> next;
                flag ^= 1;
            }
            else
            {
                iter -> next = iter2;
                iter2 = iter2 -> next;
                iter = iter -> next;
                flag ^= 1;
            }
        }
        iter -> next = iter1;
        head = dummy -> next;
    }
};

