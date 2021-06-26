// prob382: Linked List Random Node

/*
 * https://leetcode-cn.com/problems/linked-list-random-node/
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include "include/Node.h"
#include <random>

class Solution {
public:
    Solution(ListNode* head) {
        this -> head = head;
        int random_seed = rand();
        std::default_random_engine dre(random_seed);
        std::uniform_real_distribution<double> dr;
    }

    int getRandom() {
        int i = 0;
        ListNode *iter = head;
        int ans = -1;
        int m = 1;
        while(iter != nullptr)
        {
            if(i < m)
                ans = iter -> val;
            else
            {
                // [0, i]
                int random_idx = floor((i + 1) * dr(dre));
                if(random_idx < m)
                    ans = iter -> val;
            }
            iter = iter -> next;
            ++i;
        }
        return ans;
    }

private:
    ListNode *head;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
