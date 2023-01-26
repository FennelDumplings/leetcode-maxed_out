// prob1523: Count Odd Numbers in an Interval Range

/*
 * https://leetcode-cn.com/problems/count-odd-numbers-in-an-interval-range/
 */

class Solution {
public:
    int countOdds(int low, int high) {
        int len = high - low + 1;
        if((len & 1) && (low & 1))
            return len / 2 + 1;
        return len / 2;
    }
};
