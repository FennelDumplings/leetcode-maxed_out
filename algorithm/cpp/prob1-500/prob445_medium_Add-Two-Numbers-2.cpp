// prob445: Add Two Numbers

/*
 * You are given two non-empty linked lists representing two non-negative integers.
 * The most significant digit comes first and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 */

/*
 * Example:
 * Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 8 -> 0 -> 7
 */

/*
 * Follow up:
 * What if you cannot modify the input lists? In other words, reversing the lists is not allowed.
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
#include <stack>

using namespace std;

// 使用链表反转
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr || l1 -> val == 0) return l2;
        if(l2 == nullptr || l2 -> val == 0) return l1;
        // 两个链表均非空且大于 0
        l1 = _reverseList(l1);
        l2 = _reverseList(l2);
        ListNode *iter1 = l1, *iter2 = l2;
        ListNode *dummy = new ListNode(0); // dummy 是虚拟头结点，初始化什么值不重要
        ListNode *iter = dummy -> next;
        int carry = 0, sum = 0;
        while(iter1 != nullptr && iter2 != nullptr)
        {
            sum = iter1 -> val + iter2 -> val + carry;
            carry = sum / 10;
            sum %= 10;
            ListNode *tmp = new ListNode(sum);
            tmp -> next = iter;
            iter = tmp;
            dummy -> next = iter;
            iter1 = iter1 -> next;
            iter2 = iter2 -> next;
        }
        if(iter1 != nullptr)
        {
            while(iter1)
            {
                sum = iter1 -> val + carry;
                carry = sum / 10;
                sum %= 10;
                ListNode *tmp = new ListNode(sum);
                tmp -> next = iter;
                iter = tmp;
                dummy -> next = iter;
                iter1 = iter1 -> next;
            }
        }
        if(iter2 != nullptr)
        {
            while(iter2)
            {
                sum = iter2 -> val + carry;
                carry = sum / 10;
                sum %= 10;
                ListNode *tmp = new ListNode(sum);
                tmp -> next = iter;
                iter = tmp;
                dummy -> next = iter;
                iter2 = iter2 -> next;
            }
        }
        if(carry > 0)
        {
            ListNode *tmp = new ListNode(carry);
            tmp -> next = iter;
            iter = tmp;
            dummy -> next = iter;
        }
        return dummy -> next;
    }

private:
    // 206 题的普通链表反转
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

// 不用链表反转
// 迭代
class Solution_2 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr || l1 -> val == 0) return l2;
        if(l2 == nullptr || l2 -> val == 0) return l1;
        // 两个链表均非空且大于 0
        stack<int> st1, st2;
        ListNode *iter = l1;
        while(iter != nullptr)
        {
            st1.push(iter -> val);
            iter = iter -> next;
        }
        iter = l2;
        while(iter != nullptr)
        {
            st2.push(iter -> val);
            iter = iter -> next;
        }
        ListNode *dummy = new ListNode(0);
        iter = dummy -> next;
        int carry = 0;
        while(!st1.empty() && !st2.empty())
        {
            int sum = st1.top() + st2.top() + carry;
            st1.pop();
            st2.pop();
            carry = sum / 10;
            sum %= 10;
            ListNode *tmp = new ListNode(sum);
            tmp -> next = iter;
            iter = tmp;
            dummy -> next = iter;
        }
        while(!st2.empty())
        {
            int sum = st2.top() + carry;
            st2.pop();
            carry = sum / 10;
            sum %= 10;
            ListNode *tmp = new ListNode(sum);
            tmp -> next = iter;
            iter = tmp;
            dummy -> next = iter;
        }
        while(!st1.empty())
        {
            int sum = st1.top() + carry;
            st1.pop();
            carry = sum / 10;
            sum %= 10;
            ListNode *tmp = new ListNode(sum);
            tmp -> next = iter;
            iter = tmp;
            dummy -> next = iter;
        }
        if(carry > 0)
        {
            ListNode *tmp = new ListNode(carry);
            tmp -> next = iter;
            iter = tmp;
            dummy -> next = iter;
        }
        return dummy -> next;
    }
};


// 不用链表反转
// 递归
// 先补零
class Solution_3 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(l1 == nullptr || l1 -> val == 0) return l2;
        if(l2 == nullptr || l2 -> val == 0) return l1;
        // 两个链表均非空且大于 0
        ListNode *iter = l1;
        int count1 = 0;
        while(iter != nullptr)
        {
            ++count1;
            iter = iter -> next;
        }
        iter = l2;
        int count2 = 0;
        while(iter != nullptr)
        {
            ++count2;
            iter = iter -> next;
        }
        ListNode *l2_head = l2;
        ListNode *l1_head = l1;
        if(count1 > count2)
        {
            for(int i = 0; i < count1 - count2; ++i)
            {
                ListNode *tmp = new ListNode(0);
                tmp -> next = l2_head;
                l2_head = tmp;
            }
        }
        if(count1 < count2)
        {
            for(int i = 0; i < count2 - count1; ++i)
            {
                ListNode *tmp = new ListNode(0);
                tmp -> next = l1_head;
                l1_head = tmp;
            }
        }
        ListNode *dummy = new ListNode(0);
        int carry = 0;
        dummy -> next = _addTwoNumbers(l1_head, l2_head, carry);
        if(carry > 0)
        {
            ListNode *tmp = new ListNode(carry);
            tmp -> next = dummy -> next;
            dummy -> next = tmp;
        }
        return dummy -> next;
    }

private:
    ListNode* _addTwoNumbers(ListNode* l1, ListNode* l2, int &carry)
    {
        if(l1 == nullptr)
            return nullptr;

        ListNode *iter = _addTwoNumbers(l1 -> next, l2 -> next , carry);
        int sum = l1 -> val + l2 -> val + carry;
        carry = sum / 10;
        sum %= 10;
        ListNode *tmp = new ListNode(sum);
        tmp -> next = iter;
        iter = tmp;
        return iter;
    }
};
