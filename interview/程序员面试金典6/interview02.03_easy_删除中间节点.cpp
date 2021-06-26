// interview02.03: 删除中间节点

/*
 * 实现一种算法，删除单向链表中间的某个节点（即不是第一个或最后一个节点），假定你只能访问该节点。
 */

#include <vector>
#include "../../include/Node.h"

using namespace std;

class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode *left = node;
        ListNode *right = left -> next;;
        while(right -> next)
        {
            swap(left -> val, right -> val);
            left = left -> next;
            right = right -> next;
        }
        swap(left -> val, right -> val);
        left -> next = nullptr;
    }
};
