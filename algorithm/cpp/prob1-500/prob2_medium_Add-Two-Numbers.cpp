// Prob2: Add Two Numbers

/*
 * You are given two non-empty linked lists representing two non integers.
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.

 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/

// Tags
// Linked List
// Math

#include "include/Node.h"
#include <iostream>
using namespace std;

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *tmp1 = l1;
        ListNode *tmp2 = l2;
        int carry = 0;
        ListNode *tmp = new ListNode((tmp1 -> val + tmp2 -> val) % 10);
        carry = (tmp1 -> val + tmp2 -> val) / 10;
        ListNode *result = tmp;
        while(tmp1 -> next != nullptr && tmp2 -> next != nullptr)
        {
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
            ListNode *tmp3 = new ListNode((tmp1 -> val + tmp2 -> val + carry) % 10);
            carry = (tmp1 -> val + tmp2 -> val + carry) / 10;
            tmp -> next = tmp3;
            tmp = tmp -> next;
        }
        if(tmp2 -> next == nullptr)
        {
            while(tmp1 -> next != nullptr)
            {
                tmp1 = tmp1 -> next;
                ListNode *tmp3 = new ListNode((tmp1->val + carry) % 10);
                carry = (tmp1 -> val + carry) / 10;
                tmp -> next = tmp3;
                tmp = tmp -> next;
            }
        }
        else
        {
            while(tmp2 -> next != nullptr)
            {
                tmp2 = tmp2 -> next;
                ListNode *tmp3 = new ListNode((tmp2 -> val + carry) % 10);
                carry = (tmp2 -> val + carry) / 10;
                tmp -> next = tmp3;
                tmp = tmp -> next;
            }
        }
        if(carry == 1)
        {
            tmp -> next = new ListNode(1);
        }
        return result;
    }
};

int main()
{
    //The first number
    ListNode *head1 = new ListNode(3);
    ListNode *tmp1 = head1;
    tmp1 -> next = new ListNode(5);
    tmp1 = tmp1 -> next;
    tmp1 -> next = new ListNode(6);
    tmp1 = tmp1 -> next;
    tmp1 -> next = new ListNode(2);
    //the second number
    ListNode *head2 = new ListNode(7);
    ListNode *tmp2 = head2;
    tmp2 -> next = new ListNode(8);
    //显示两个数
    tmp1 = head1;
    tmp2 = head2;
    while(tmp1 != nullptr)
    {
        cout << tmp1 -> val << " ";
        tmp1 = tmp1 -> next;
    }
    cout << endl;
    while(tmp2 != nullptr)
    {
        cout << tmp2 -> val << " ";
        tmp2 = tmp2 -> next;
    }
    cout << endl;
    //计算
    Solution solution;
    ListNode *res = solution.addTwoNumbers(head1, head2);
    //显示结果
    ListNode *tmp3 = res;
    while(tmp3 != nullptr)
    {
        cout << tmp3 -> val << " ";
        tmp3 = tmp3 -> next;
    }
}

/*
 * Similar Problem
 * Multiply Strings -- Medium
 * Add Binary -- Easy
 * Sum of Two Integers -- Easy
 * Add Strings -- Easy
 * Add Two Numbers II -- Medium
 * Add to Array-Form of Integer -- Easy
 */
