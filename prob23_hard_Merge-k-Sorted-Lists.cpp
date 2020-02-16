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
