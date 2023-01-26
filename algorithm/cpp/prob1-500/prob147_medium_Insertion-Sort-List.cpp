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
#include <algorithm>

using namespace std;

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        // return _insertionSortList(head);
        // return _selectSortList(head);
        return _bubbleSortList(head);
        // return _quickSortList(head);
        // return _mergeSortList(head);
    }

private:
    // 链表插入排序, 交换链表节点，而不是交换值
    ListNode* _insertionSortList(ListNode* head) {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node, *iter = head -> next;
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

    // 链表选择排序，只交换值
    ListNode* _selectSortList(ListNode* head)
    {
        if(head == nullptr || head -> next == nullptr) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node, *pretail = dummy;
        dummy -> next = head;

        while(pretail -> next != nullptr)
        {
            ListNode *minNode = pretail -> next; // 从左侧第一个开始，记录最小节点
            ListNode *iter = pretail -> next -> next;
            while(iter != nullptr)
            {
                if(iter -> val < minNode -> val)
                    minNode = iter;
                iter = iter -> next;
            }
            swap(pretail -> next, minNode);
            pretail = pretail -> next;
        }
        return dummy -> next;
    }

    // 链表快排
    ListNode* _quickSortList(ListNode* head)
    {
        if(head == nullptr || head -> next == nullptr) return head;
        // 只交换值
        // _quicksortlist1(head, nullptr);
        // return head;
        // 交换节点
        ListNode dummy_node(0);
        ListNode* dummy = &dummy_node;
        dummy -> next = head;
        _quicksortlist2(dummy, head, nullptr);
        return dummy -> next;
    }

    // 链表快排，只交换值, 注意点
    // 1. partition 使用单指针版本, 因为链表到最右节点需要 O(N)
    // 2. partition 使用左闭右开的
    void _quicksortlist1(ListNode* head, ListNode* tail)
    {
        if(head != nullptr && head -> next != nullptr)
        {
            if(head != tail)
            {
                ListNode *mid = _divide_list1(head, tail);
                _quicksortlist1(head, mid);
                _quicksortlist1(mid -> next, tail);
            }
        }
    }

    ListNode* _divide_list1(ListNode* head, ListNode* tail)
    {
        int pivot = head -> val;
        ListNode* loc = head; // pivot 的位置 [head, loc) 比 pivot 小
        for(ListNode* i = head -> next; i != tail; i = i -> next)
            if(i -> val < pivot)
            {
                loc = loc -> next;
                _swap_value(i, loc);
            }
        _swap_value(loc, head);
        return loc;
    }

    // 链表快排，交换链表节点
    // 第一个节点作为 pivot, 小于枢纽的放到第一个链，不小于的放后一个链
    // 然后把两条链和 pivot 连接成一条链，注意点
    // 1. 对一条子链 partition 时候, 节点的顺序被打乱了(交换了节点而不是只交换值)
    //    所以得保证重新组合乘一条新链表的时候，要和该子链表的前后部分连接起来
    //    因此我们的partition传入三个参数，除了子链表的范围（也是前闭后开区间），
    //    还要传入子链表头结点的前驱
    // 2. partition后链表的头结点可能已经改变
    void _quicksortlist2(ListNode* pretail, ListNode* head, ListNode* tail)
    {
        // head 和 tail 是开区间
        if(head != tail && head -> next != tail)
        {
            ListNode *mid = _divide_list2(pretail, head, tail);
            // 排序子链时 mid 未包含在内
            _quicksortlist2(pretail, pretail -> next, mid);
            _quicksortlist2(mid, mid -> next, tail);
        }
    }

    ListNode* _divide_list2(ListNode* pretail, ListNode* head, ListNode* tail)
    {
        int pivot = head -> val;
        ListNode dummy_left_node(0), dummy_right_node(0); // 左链和右链的虚拟头结点
        ListNode *dummy_left = &dummy_left_node, *dummy_right = &dummy_right_node;
        ListNode *left = dummy_left, *right = dummy_right;
        for(ListNode* i = head -> next; i != tail; i = i -> next)
        {
            if(i -> val < pivot)
            {
                left -> next = i;
                left = i;
            }
            else
            {
                right -> next = i;
                right = i;
            }
        }
        right -> next = tail;
        left -> next = head; // head 是 pivot
        head -> next = dummy_right -> next;
        pretail -> next = dummy_left -> next;
        return head;
    }

    // 归并排序, 这里只有自顶向下写法
    // 另参考 leetcode prob148, 自顶向下和自底向上两种写法(自底向上好)
    ListNode* _mergeSortList(ListNode* head)
    {
        if(head == nullptr || head -> next == nullptr) return head;

        // 快慢指针找中间节点
        ListNode *fast = head, *slow = head;
        while(fast -> next != nullptr && fast -> next -> next != nullptr)
        {
            fast = fast -> next -> next;
            slow = slow -> next;
        }
        ListNode *l1 = head;
        ListNode *l2 = slow -> next;
        slow -> next = nullptr; // 先断链再分治
        l1 = _mergeSortList(l1);
        l2 = _mergeSortList(l2);
        return _merge(l1, l2);
    }

    ListNode* _merge(ListNode* l1, ListNode* l2)
    {
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        ListNode *pretail = dummy;
        while(l1 != nullptr && l2 != nullptr)
        {
            if(l1 -> val < l2 -> val)
            {
                pretail -> next = l1;
                l1 = l1 -> next;
            }
            else
            {
                pretail -> next = l2;
                l2 = l2 -> next;
            }
            pretail = pretail -> next;
        }
        if(l1 == nullptr)
            pretail -> next = l2;
        else
            pretail -> next = l1;
        return dummy -> next;
    }

    // 冒泡排序，仅交换节点的值
    ListNode* _bubbleSortList(ListNode* head)
    {
        if(head == nullptr || head -> next == nullptr) return head;

        ListNode* right = nullptr;
        bool isChange = true;
        while(right != head -> next && isChange)
        {
            ListNode *left = head;
            isChange = false;
            for(; left -> next != right; left = left -> next)
            {
                if(left -> val > left -> next -> val)
                {
                    _swap_value(left, left -> next);
                    isChange = true;
                }
            }
            right = left; // 第i次起泡时，至少最右边的i个已经排好
        }
        return head; // 只交换节点值没有交换和插删节点，可直接返回 haed
    }

    // 交换链表节点值
    void _swap_value(ListNode* a, ListNode* b)
    {
        int tmp = a -> val;
        a -> val = b -> val;
        b -> val = tmp;
    }
};


// 链表的快排下面的写法能过，但是时空都不理想, 用的是闭区间
class Solution_2 {
public:
    ListNode* insertionSortList(ListNode* head) {
        return sortList(head);
    }

    ListNode* sortList(ListNode* head) {
        if(!head || !(head -> next)) return head;
        return _quicksortList(head).first;
    }

private:
    pair<ListNode*, ListNode*> _quicksortList(ListNode* head)
    {
        if(!head || !(head -> next)) return pair<ListNode*, ListNode*>(head, head);

        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *pivot_prev = dummy, *pivot = dummy -> next; // pivot 为最左元素
        ListNode *iter_prev = pivot, *iter = pivot -> next;

        while(iter != nullptr)
        {
            if(pivot -> val > iter -> val)
            {
                pivot_prev -> next = iter;
                iter_prev -> next = iter -> next;
                iter -> next = pivot;
                iter = iter_prev -> next;
                pivot_prev = pivot_prev -> next;
            }
            else
            {
                iter = iter -> next;
                iter_prev = iter_prev -> next;
            }
        }

        ListNode *l1 = dummy -> next;
        ListNode *l2 = pivot -> next;
        pivot -> next = nullptr;
        pair<ListNode*, ListNode*> l1_result = _quicksortList(l1);
        pair<ListNode*, ListNode*> l2_result = _quicksortList(l2);
        if(l1_result.first == nullptr) return l2_result;
        if(l2_result.first == nullptr) return l1_result;
        l1_result.second -> next = l2_result.first;
        return pair<ListNode*, ListNode*>(l1_result.first, l2_result.second);
    }
};

