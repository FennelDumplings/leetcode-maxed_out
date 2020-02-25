// prob147: Insertion Sort List

/*
 * Sort a linked list using insertion sort.
 */

/*
 * Algorithm of Insertion Sort:
 * Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
 * At each iteration, insertion sort removes one element from the input data,
 * finds the location it belongs within the sorted list, and inserts it there.
 * It repeats until no input elements remain.
 */

#include "include/Node.h"


class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode *dummy = new ListNode(0), *iter = head -> next;
        dummy -> next = head;

        while(iter != nullptr)
        {
            ListNode *prev = dummy, *tmp = dummy -> next;
            while(tmp != iter && tmp -> val <= iter -> val)
            {
                tmp = tmp -> next;
                prev = prev -> next;
            }

            if(tmp != iter)
            {
                head -> next = iter -> next;
                iter -> next = tmp;
                prev -> next = iter;
                iter = head -> next;
            }
            else
            {
                head = iter;
                iter = iter -> next;
            }
        }
        return dummy -> next;
    }
};


// 递归, 不好的写法，最好情况也变成了 O(N^2), flag 的剪枝无效
class Solution_2 {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode *iter = head -> next, *prev = head;
        while(iter != nullptr)
        {
            prev = iter;
            iter = iter -> next;
            bool flag = false;
            head = insert(head, prev, flag);
        }
        return head;
    }

private:
    ListNode* insert(ListNode* head, ListNode* iter, bool& flag)
    {
        if(flag) return head;
        if(head -> next == iter)
        {
            return _insert_adjecent(head, iter, flag);
        }
        else
        {
            head -> next = insert(head -> next, iter, flag);
            return  _insert_adjecent(head, head -> next, flag);
        }
    }

    ListNode* _insert_adjecent(ListNode* insert_pos, ListNode* cur, bool& flag)
    {
        if(cur == nullptr) return insert_pos;
        if(insert_pos -> val > cur -> val)
        {
            insert_pos -> next = cur -> next;
            cur -> next = insert_pos;
            return cur;
        }
        else
        {
            flag = true;
            return insert_pos;
        }
    }
};

