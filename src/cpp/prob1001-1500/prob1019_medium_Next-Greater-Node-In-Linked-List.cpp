// prob1019: Next Greater Node In Linked List

/*
 * We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.
 * Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i,
 * node_j.val > node_i.val, and j is the smallest possible choice.  If such a j does not exist, the next larger value is 0.
 * Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).
 * Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a
 * linked list with a head node value of 2, second node value of 1, and third node value of 5.
 */

/*
 * Example 1:
 * Input: [2,1,5]
 * Output: [5,5,0]
 * Example 2:
 * Input: [2,7,4,3,5]
 * Output: [7,0,5,5,0]
 * Example 3:
 * Input: [1,7,5,1,9,2,5,1]
 * Output: [7,9,9,9,0,5,0,0]
 */

/*
 * Note:
 * 1 <= node.val <= 10^9 for each node in the linked list.
 * The given list has length in the range [0, 10000].
 */

#include <vector>
#include <stack>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        if(!(head -> next)) return vector<int>();
        ListNode *iter = head;
        int i = 0;
        vector<int> result;
        using PII = pair<int, int>;
        stack<PII> st;
        while(iter -> next)
        {
            int cur = iter -> next -> val;
            while(!st.empty() && st.top().first < cur)
            {
                result[st.top().second] = cur;
                st.pop();
            }
            st.push(PII(cur, i));
            iter = iter -> next;
            result.push_back(0);
            ++i;
        }
        return result;
    }
};
