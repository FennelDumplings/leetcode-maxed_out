/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include "include/Node.h"
#include <algorithm>

using namespace std;

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        int n = get_list_len(head);
        ListNode *p1 = get_p(head, k);
        ListNode *p2 = get_p(head, n + 1 - k);
        swap(p1 -> val, p2 -> val);
        return head;
    }

private:
    ListNode* get_p(ListNode* head, int k)
    {
        for(int i = 0; i < k - 1; ++i)
        {
            head = head -> next;
        }
        return head;
    }

    int get_list_len(ListNode* head)
    {
        int n = 0;
        while(head)
        {
            ++n;
            head = head -> next;
        }
        return n;
    }
};
