// interview02.04: 分割链表

/*
 * 编写程序以 x 为基准分割链表，使得所有小于 x 的节点排在大于或等于 x 的节点之前。如果链表中包含 x，x 只需出现在小于 x 的元素之后(如下所示)。分割元素 x 只需处于“右半部分”即可，其不需要被置于左右两部分之间。
 */

/*
 * 示例:
 * 输入: head = 3->5->8->5->10->2->1, x = 5
 * 输出: 3->1->2->10->5->5->8
 */

#include "../../include/Node.h"

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(!head || !head -> next) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode pretail_node(0);
        ListNode *pretail = &pretail_node;
        ListNode *iter = dummy;
        while(iter -> next)
        {
            int cur = iter -> next -> val;
            if(cur < x)
            {
                iter = iter -> next;
            }
            else
            {
                ListNode *tmp = iter -> next;
                iter -> next = iter -> next -> next;
                tmp -> next = pretail -> next;
                pretail -> next = tmp;
            }
        }
        iter -> next = pretail -> next;
        return dummy -> next;
    }
};
