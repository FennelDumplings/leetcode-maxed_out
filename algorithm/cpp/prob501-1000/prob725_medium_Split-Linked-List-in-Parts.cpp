// prob725: Split Linked List in Parts

/*
 * https://leetcode-cn.com/problems/split-linked-list-in-parts/
 */

#include <vector>
#include "include/Node.h"

using namespace std;

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        if(!root) return vector<ListNode*>(k, nullptr);
        int n = 0;
        ListNode *iter = root;
        while(iter)
        {
            ++n;
            iter = iter -> next;
        }
        int x = n / k;
        // 有 t 个长为 x，s 个长为 x + 1 (s + t = k)
        int s = n - k * x;
        int t = k - s;
        // n = 14, k = 3
        // x = 4
        // s = 2
        // t = k - s = 1
        vector<ListNode*> result(k, nullptr);
        iter = root;
        for(int i = 0; i < s; ++i)
        {
            result[i] = iter;
            iter = _split(iter, x + 1);
        }
        for(int i = 0; i < t; ++i)
        {
            result[s + i] = iter;
            iter = _split(iter, x);
        }
        return result;
    }

private:
    ListNode* _split(ListNode* iter, int x)
    {
        if(!iter) return nullptr;
        while(--x && iter)
            iter = iter -> next;
        ListNode* nxt = nullptr;
        if(iter)
        {
            nxt = iter -> next;
            iter -> next = nullptr;
        }
        return nxt;
    }
};
