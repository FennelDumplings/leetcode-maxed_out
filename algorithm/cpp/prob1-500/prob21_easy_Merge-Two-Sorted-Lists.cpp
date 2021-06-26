// prob21: Merge Two Sorted Lists

/*
 * Merge two sorted linked lists and return it as a new list.
 * The new list should be made by splicing together the nodes of the first two lists.
 */

/*
 * Example:
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
 */

#include "include/Node.h"

using namespace std;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // 边界特判
        if(l1 == nullptr && l2 == nullptr) return nullptr;
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        // l1 和 l2 均非空
        // 确定结果的头指针
        ListNode *iter1 = l1;
        ListNode *iter2 = l2;
        ListNode *result = nullptr;
        ListNode *iter = nullptr;
        if(l1 -> val <= l2 -> val)
        {
            iter1 = l1 -> next;
            l1 -> next = l2;
            result = l1;
            iter = result;
        }
        else
        {
            iter2 = l2 -> next;
            l2 -> next = l1;
            result = l2;
            iter = result;
        }
        while(iter1 != nullptr && iter2 != nullptr)
        {
            if(iter1 -> val <= iter2 -> val)
            {
                iter -> next = iter1;
                iter = iter -> next;
                iter1 = iter1 -> next;
            }
            else
            {
                iter -> next = iter2;
                iter = iter -> next;
                iter2 = iter2 -> next;
            }
        }
        if(iter1 == nullptr)
            iter -> next = iter2;
        else
            iter -> next = iter1;
        return result;
    }
};

// 代码简化
class Solution_2 {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *result = new ListNode(-1);
        ListNode *cur = result;
        while (l1 && l2) {
            if(l1 -> val < l2 -> val) {
                cur -> next = l1;
                l1 = l1 -> next;
            } else {
                cur -> next = l2;
                l2 = l2 -> next;
            }
            cur = cur -> next;
        }
        if(l1) cur -> next = l1;
        if(l2) cur -> next = l2;
        return result -> next;
    }
};
