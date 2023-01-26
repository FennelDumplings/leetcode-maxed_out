// prob817: Linked List Components

/*
 * https://leetcode-cn.com/problems/linked-list-components/
 */

#include "include/Node.h"
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        if(G.empty() || !head) return 0;
        unordered_set<int> setting(G.begin(), G.end());
        ListNode *iter = head;
        int ans = 0;
        while(iter)
        {
            if(setting.count(iter -> val) == 0)
            {
                iter = iter -> next;
                continue;
            }
            ++ans;
            while(iter && setting.count(iter -> val))
                iter = iter -> next;
            if(iter)
                iter = iter -> next;
        }
        return ans;
    }
};
