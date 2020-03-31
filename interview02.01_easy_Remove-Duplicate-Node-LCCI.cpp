// interview02.01: Remove Duplicate Node LCCI

/*
 * Write code to remove duplicates from an unsorted linked list.
 */

/*
 * Example1:
 * Input: [1, 2, 3, 3, 2, 1]
 * Output: [1, 2, 3]
 * Example2:
 * Input: [1, 1, 1, 1, 2]
 * Output: [1, 2]
 */

/*
 * Note:
 * The length of the list is within the range[0, 20000].
 * The values of the list elements are within the range [0, 20000].
 */

/*
 * Follow Up:
 * How would you solve this problem if a temporary buffer is not allowed?
 */

#include "include/Node.h"
#include <unordered_set>

using namespace std;

class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if(!head || !(head -> next)) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        unordered_set<int> setting;
        while(iter -> next)
        {
            auto it = setting.find(iter -> next -> val);
            if(it != setting.end())
            {
                iter -> next = iter -> next -> next;
            }
            else
            {
                setting.insert(iter -> next -> val);
                iter = iter -> next;
            }
        }
        return dummy -> next;
    }
};

// 不用额外空间 O(N^2)
class Solution_2 {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if(!head || !(head -> next)) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *left = dummy;
        while(left -> next)
        {
            int cur = left -> next -> val;
            ListNode *right = left -> next;
            while(right -> next)
            {
                if(right -> next -> val == cur)
                    right -> next = right -> next -> next;
                else
                    right = right -> next;
            }
            left = left -> next;
        }
        return dummy -> next;
    }
};
