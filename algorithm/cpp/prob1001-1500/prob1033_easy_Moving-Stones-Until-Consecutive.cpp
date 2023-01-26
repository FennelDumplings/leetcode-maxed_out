// prob1033: Moving Stones Until Consecutive

/*
 * https://leetcode-cn.com/problems/moving-stones-until-consecutive/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        if(a > c) swap(a, c);
        if(b > c) swap(b, c);
        if(a > b) swap(a, b);
        // a < b < c
        if(a + 1 == b && b + 1 == c)
            return {0, 0};
        if(a + 1 == b)
        {
            int d = c - b;
            // d > 1
            return {1, d - 1};
        }
        if(b + 1 == c)
        {
            int d = b - a;
            // d > 1
            return {1, d - 1};
        }
        int d1 = b - a;
        int d2 = c - b;
        if(d1 == 2 || d2 == 2)
            return {1, d1 + d2 - 2};
        return {2, d1 + d2 - 2};
    }
};
