// interview06: 从尾到头打印链表

/*
 * 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
 */

/*
 * 示例 1：
 * 输入：head = [1,3,2]
 * 输出：[2,3,1]
 */

/*
 * 限制：
 * 0 <= 链表长度 <= 10000
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        if(!head) return {};
        vector<int> result;
        traverse(head, result);
        return result;
    }

private:
    void traverse(ListNode *head, vector<int>& result)
    {
        if(head -> next)
            traverse(head -> next, result);
        result.push_back(head -> val);
    }
};
