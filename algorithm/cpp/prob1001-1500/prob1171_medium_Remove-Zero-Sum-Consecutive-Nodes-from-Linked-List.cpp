// prob1171: Remove Zero Sum Consecutive Nodes from Linked List

/*
 * Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.
 * After doing so, return the head of the final linked list.  You may return any such answer.
 * (Note that in the examples below, all sequences are serializations of ListNode objects.)
 */

/*
 * Example 1:
 * Input: head = [1,2,-3,3,1]
 * Output: [3,1]
 * Note: The answer [1,2,1] would also be accepted.
 * Example 2:
 * Input: head = [1,2,3,-3,4]
 * Output: [1,2,4]
 * Example 3:
 * Input: head = [1,2,3,-3,-2]
 * Output: [1]
 */

/*
 * Constraints:
 * The given linked list will contain between 1 and 1000 nodes.
 * Each node in the linked list has -1000 <= node.val <= 1000.
 */

#include <stack>
#include <unordered_set>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        if(!head) return head;
        ListNode dummy_node(0);
        ListNode *dummy = &dummy_node;
        dummy -> next = head;
        ListNode *iter = dummy;
        stack<ListNode*> st;
        int sum = 0;
        unordered_set<int> setting({0});
        while(iter -> next)
        {
            int cur = iter -> next -> val;
            if(setting.find(sum + cur) != setting.end())
            {
                int remain = -cur;
                _delete(iter);
                while(remain != 0)
                {
                    int top_val = st.top() -> next -> val;
                    if(sum != 0)
                        setting.erase(sum);
                    _delete(st.top());
                    st.pop();
                    sum -= top_val;
                    remain -= top_val;
                }
                if(!st.empty())
                    iter = st.top() -> next;
                else
                    iter = dummy;
            }
            else
            {
                setting.insert(sum + cur);
                st.push(iter);
                sum += cur;
                iter = iter -> next;
            }
        }
        return dummy -> next;
    }

private:
    void _delete(ListNode *pretail)
    {
        pretail -> next = pretail -> next -> next;
    }
};
