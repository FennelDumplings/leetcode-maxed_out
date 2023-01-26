// interview02.06: 回文链表

/*
 * https://leetcode-cn.com/problems/palindrome-linked-list-lcci/
 */

#include "../../include/Node.h"

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head || !head -> next) return true;

        ListNode left_dummy_node(0);
        ListNode *left_dummy = &left_dummy_node;
        left_dummy -> next = head;

        ListNode *pretail = get_middle(left_dummy -> next);

        ListNode right_dummy_node(0);
        ListNode *right_dummy = &right_dummy_node;
        right_dummy -> next = pretail -> next;

        pretail -> next = nullptr;

        right_dummy -> next =  reverse(right_dummy -> next);
        bool result = compare(left_dummy -> next, right_dummy -> next);
        right_dummy -> next = reverse(right_dummy -> next);

        pretail -> next = right_dummy -> next;

        return result;
    }

private:
    ListNode* get_middle(ListNode* head)
    {
        // 返回 pretail
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *fast = dummy, *slow = dummy;
        while(fast -> next && fast -> next -> next)
        {
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        if(fast -> next)
        {
            fast = fast -> next;
            slow = slow -> next;
        }
        return slow;
    }

    ListNode* reverse(ListNode* head)
    {
        if(!head || !head -> next)
            return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy -> next;
        while(iter -> next)
        {
            ListNode *tmp = dummy -> next;
            dummy -> next = iter -> next;
            iter -> next = dummy -> next -> next;
            dummy -> next -> next = tmp;
        }
        return dummy -> next;
    }

    bool compare(ListNode* head1, ListNode* head2)
    {
        while(head1 && head2)
        {
            if(head1 -> val != head2 -> val)
                return false;
            head1 = head1 -> next;
            head2 = head2 -> next;
        }
        return true;
    }

    void view(ListNode *head)
    {
        while(head)
        {
            cout << head -> val << " ";
            head = head -> next;
        }
        cout << endl;
    }
};
