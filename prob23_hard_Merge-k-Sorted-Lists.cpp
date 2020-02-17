// prob23: Merge k Sorted Lists

/*
 * Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
 */

/*
 * Example:
 *
 * Input:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * Output: 1->1->2->3->4->4->5->6
 */

#include "include/Node.h"
#include <vector>
#include <queue>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 自定义比较函数法一：pq 中存节点指针
// 推荐写法
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
        for(ListNode *iter : lists)
        {
            if(iter != nullptr)
                pq.push(iter);
        }
        if(pq.empty()) return  nullptr;
        ListNode *top = pq.top();
        pq.pop();
        ListNode *result = top;
        if(top -> next != nullptr)
            pq.push(top -> next);
        ListNode *tail = result;
        while(!pq.empty())
        {
            ListNode *top = pq.top();
            pq.pop();
            tail -> next = top;
            if(top -> next != nullptr)
                pq.push(top -> next);
            tail = tail -> next;
        }
        return result;
    }

private:
    // 自定义比较数的一法：定义结构体，里面只重载 ()
    // 此法也可以用于pq中存节点：() 的形参从指针改为节点即可
    // 结构体内含“bool operator()（const int &a,const int &b）”。这其实等价于Class cmp，不过更省事
    struct Compare
    {
        bool operator () (ListNode *left, ListNode *right)
        {
            return (left -> val) > (right -> val); // > 是小顶堆；< 是大顶堆
        }
    };
};


// 自定义比较函数法二
// pq 中存节点
bool operator <(const ListNode &left, const ListNode &right)
{
    // 形参必须写引用
    return (left.val) > (right.val);
}

class Solution_2 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        priority_queue<ListNode> pq;
        for(ListNode *iter : lists)
        {
            if(iter != nullptr)
                pq.push(*iter);
        }
        if(pq.empty()) return  nullptr;
        ListNode top = pq.top();
        pq.pop();
        if(top.next != nullptr)
            pq.push(*(top.next));
        ListNode *result = new ListNode(top.val);
        ListNode *tail = result; // 迭代的时候还是用指针
        while(!pq.empty())
        {
            ListNode top = pq.top();
            pq.pop();
            if(top.next != nullptr)
                pq.push(*(top.next));
            tail -> next = new ListNode(top.val);
            tail = tail -> next;
        }
        return result;
    }
};

// 分治法 O(NlogN)
// 递归分治
class Solution_3 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        int n = lists.size();
        ListNode *result = _mergeKLists(lists, 0, n - 1);
        return result;

    }

private:
    ListNode* _mergeKLists(vector<ListNode*>& lists, int left, int right)
    {
        if(left == right)
            return lists[left];
        if(left + 1 == right)
            return _mergeTwoLists(lists[left], lists[right]);
        int mid = left + (right - left) / 2;
        ListNode *left_merged = _mergeKLists(lists, left, mid - 1);
        ListNode *right_merged = _mergeKLists(lists, mid, right);
        return _mergeTwoLists(left_merged, right_merged);
    }

    ListNode* _mergeTwoLists(ListNode* l1, ListNode* l2) {
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
        if(l1) cur->next = l1;
        if(l2) cur->next = l2;
        return result -> next;
    }
};

// 分治法 O(NlogN)
// 迭代分治
class Solution_4 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        int n = lists.size();
        while (n > 1)
        {
            // n 每轮减小一半
            int k = (n + 1) / 2;
            for(int i = 0; i < n / 2; ++i)
                lists[i] = _mergeTwoLists(lists[i], lists[i + k]);
            n = k;
        }
        return lists[0];
    }

private:
    ListNode* _mergeTwoLists(ListNode* l1, ListNode* l2) {
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
        if(l1) cur->next = l1;
        if(l2) cur->next = l2;
        return result -> next;
    }
};
