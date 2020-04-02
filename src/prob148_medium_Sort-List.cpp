// prob 148: Sort List

/*
 * Sort a linked list in O(n log n) time using constant space complexity.
 */

#include "include/Node.h"
#include <algorithm>

using namespace std;

// 自底向上
// split(head, n) 返回断链后剩余的指针
// merge 返回头尾两个指针
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;

        ListNode *iter = head;
        int n = 0;
        while(iter != nullptr)
        {
            ++n;
            iter = iter -> next;
        }

        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *before_merge = dummy;
        ListNode *it;
        ListNode *list1, *list2;
        for(int size = 1; size < n; size *= 2)
        {
            before_merge = dummy; // 归并的 list1 节点的前一个节点
            it = before_merge -> next;
            for(int left = 0; left < n - size; left += size * 2)
            {
                list1 = it;
                it = _split(it, size);
                list2 = it;
                it = _split(it, size);
                pair<ListNode*, ListNode*> merged = merge(list1, list2);
                before_merge -> next = merged.first;
                before_merge = merged.second;
                before_merge -> next = it;
            }
        }
        return dummy -> next;
    }

private:
    ListNode* _split(ListNode* head, int n)
    {
        while(--n && head)
            head = head -> next;
        ListNode* rest = nullptr;
        if(head)
        {
            rest = head -> next;
            head -> next = nullptr;
        }
        return rest;
    }

    pair<ListNode*, ListNode*> merge(ListNode* list1, ListNode* list2)
    {
        ListNode *dummy = new ListNode(0);
        ListNode *iter = dummy;
        while(list1 != nullptr && list2 != nullptr)
        {
            if(list1 -> val <= list2 -> val)
            {
                iter -> next = list1;
                iter = iter -> next;
                list1 = list1 -> next;
            }
            else
            {
                iter -> next = list2;
                iter = iter -> next;
                list2 = list2 -> next;
            }
        }
        if(list2 == nullptr)
        {
            while(list1 != nullptr)
            {
                iter -> next = list1;
                iter = iter -> next;
                list1 = list1 -> next;
            }
        }
        if(list1 == nullptr)
        {
            while(list2 != nullptr)
            {
                iter -> next = list2;
                iter = iter -> next;
                list2 = list2 -> next;
            }
        }
        return pair<ListNode*, ListNode*>(dummy -> next, iter);
    }
};

// 自顶向下 O(NlogN)时间  O(logN)空间
class Solution_2 {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !(head -> next)) return head;
        ListNode *slow = head;
        ListNode *fast = head -> next;
        while(fast && fast -> next)
        {
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        ListNode* mid = slow -> next;
        slow -> next = nullptr;
        return _merge(sortList(head), sortList(mid));
    }

private:
    ListNode* _merge(ListNode* l1, ListNode* l2)
    {
        if(!l1) return l2;
        if(!l2) return l1;
        // ListNode *dummy = new ListNode(0);
        // ListNode *iter = dummy;
        ListNode dummy(0);
        ListNode *iter = &dummy;
        while(l1 && l2)
        {
            if(l1 -> val <= l2 -> val)
            {
                iter -> next = l1;
                iter = iter -> next;
                l1 = l1 -> next;
            }
            else
            {
                iter -> next = l2;
                iter = iter -> next;
                l2 = l2 -> next;
            }
        }
        while(l1)
        {
            iter -> next = l1;
            iter = iter -> next;
            l1 = l1 -> next;
        }
        while(l2)
        {
            iter -> next = l2;
            iter = iter -> next;
            l2 = l2 -> next;
        }
        return dummy.next;
    }
};
