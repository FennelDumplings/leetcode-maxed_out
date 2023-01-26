// prob683: K Empty Slots

/*
 * You have N bulbs in a row numbered from 1 to N. Initially, all the bulbs are turned off. We turn on exactly one bulb
 * everyday until all bulbs are on after N days.
 * You are given an array bulbs of length N where bulbs[i] = x means that on the (i+1)th day, we will turn on the bulb at
 * position x where i is 0-indexed and x is 1-indexed.
 * Given an integer K, find out the minimum day number such that there exists two turned on bulbs that have exactly K bulbs
 * between them that are all turned off.
 * If there isn't such day, return -1.
 */

/*
 * Example 1:
 * Input:
 * bulbs: [1,3,2]
 * K: 1
 * Output: 2
 * Explanation:
 * On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
 * On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
 * On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
 * We return 2 because on the second day, there were two on bulbs with one off bulb between them.
 * Example 2:
 * Input:
 * bulbs: [1,2,3]
 * K: 1
 * Output: -1
 */

/*
 * Note:
 * 1 <= N <= 20000
 * 1 <= bulbs[i] <= N
 * bulbs is a permutation of numbers from 1 to N.
 * 0 <= K <= 20000
 */

#include <set>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int kEmptySlots(vector<int>& bulbs, int K) {
        int N = bulbs.size();
        if(N <= 1) return -1;
        if(K >= N - 1) return -1;
        // N >= 2
        if(abs(bulbs[0] - bulbs[1]) - 1 == K)
            return 2;
        set<int> bloom({0, bulbs[0], bulbs[1], N + 1});
        for(int i = 2; i < N; ++i)
        {
            auto ins = bloom.insert(bulbs[i]);
            auto it = ins.first;
            auto prev_it = prev(it, 1);
            auto next_it = next(it, 1);
            if(*prev_it != 0)
            {
                int gap = *it - *prev_it;
                if(gap - 1 == K)
                    return i + 1;
            }
            if(*next_it != N + 1)
            {
                int gap = *next_it - *it;
                if(gap - 1 == K)
                    return i + 1;
            }
        }
        return -1;
    }
};
