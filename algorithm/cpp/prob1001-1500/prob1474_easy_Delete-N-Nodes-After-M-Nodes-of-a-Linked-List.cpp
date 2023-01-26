// prob1474: Delete N Nodes After M Nodes of a Linked List

/*
 * https://leetcode-cn.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/
 */

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        while(iter -> next)
        {
            int k = m;
            while(iter -> next && k > 0)
            {
                iter = iter -> next;
                --k;
            }
            k = n;
            while(iter -> next && k > 0)
            {
                iter -> next = iter -> next -> next;
                --k;
            }
        }
        return dummy -> next;
    }
};
