// prob25: Reverse Nodes in k-Group

/*
 * Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
 * k is a positive integer and is less than or equal to the length of the linked list.
 * If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
 */

/*
 * Example:
 * Given this linked list: 1->2->3->4->5
 * For k = 2, you should return: 2->1->4->3->5
 * For k = 3, you should return: 3->2->1->4->5
 */

#include "include/Node.h"

// 递归
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k < 2) return head;
        return _reverseKGroup(head, k);
    }

private:
    ListNode* _reverseKGroup(ListNode* head, int k)
    {
        ListNode *tail;
        if(!check(head, k, tail)) return head;
        head = _reverse(head, tail);
        tail -> next = _reverseKGroup(tail -> next, k);
        return head;
    }

    ListNode* _reverse(ListNode* head, ListNode*& tail)
    {
        ListNode *tmp = head -> next;
        head -> next = tail;
        ListNode *iter = tmp;
        ListNode *prev = head;
        while(iter != tail)
        {
            tmp = iter -> next;
            iter -> next = prev;
            prev = iter;
            iter = tmp;
        }
        head -> next = iter -> next;
        iter -> next = prev;
        tail = head;
        return iter;
    }

    bool check(ListNode* head, int k, ListNode*& tail)
    {
        int i = 0;
        ListNode *iter = head;
        tail = iter;
        while(i < k)
        {
            if(iter == nullptr)
                return false;
            tail = iter;
            iter = iter -> next;
            ++i;
        }
        return true;
    }
};


// 用朴素链表翻转作 helper
// 迭代写法(推荐)
// 不用先check，而是直接翻转，还没翻到k个的时候就到尾了，就再把已经翻转的再翻回来就行
// check 的遍历就省了
class Solution_2 {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == nullptr) return nullptr;
        ListNode *dummy = new ListNode(0);
        dummy -> next = head;
        ListNode *pretail = dummy;
        while(head != nullptr)
        {
            ListNode *tmp = head; // 调用 reverseK 之后 tmp 指向了尾部节点
            head = reverseK(pretail, head, k);
            pretail = tmp;
        }
        return dummy -> next;
    }

private:
    // 翻转链表，翻转k个元素
    // pretail 是上一段的尾部
    // pretail -> next 是当前段的开头
    ListNode* reverseK(ListNode *pretail, ListNode* cur, int k)
    {
        ListNode *pre = nullptr;
        ListNode *nxt = cur -> next;
        for(int i = 1; i <= k; ++i)
        {
            cur -> next = pre;
            // 下面两条判断是核心，且顺序不能错
            if(i == k) break;
            if(nxt == nullptr) // 当前只翻转了 i 个节点就达到了末尾，不够长
                return reverseK(pretail, cur, i); // 把已经翻转的再翻转回来
            pre = cur;
            cur = nxt;
            nxt = nxt -> next;
        }
        pretail -> next = cur;
        return nxt;
    }
};
