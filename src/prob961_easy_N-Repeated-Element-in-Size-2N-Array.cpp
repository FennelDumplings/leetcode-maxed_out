// prob961: N-Repeated Element in Size 2N Array

/*
 * https://leetcode-cn.com/problems/n-repeated-element-in-size-2n-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int repeatedNTimes(vector<int>& A) {
        int cnt = 0;
        int cand = 0;
        int prev = 0;
        for(const int a: A)
        {
            if(cnt == 0)
            {
                cand = a;
                ++cnt;
                continue;
            }
            if(a == cand)
                ++cnt;
            else
                --cnt;
            prev = a;
        }
        int cnt_prev = 0;
        int cnt_cand = 0;
        for(int a: A)
        {
            if(a == prev)
            {
                ++cnt_prev;
                if(cnt_prev > 1)
                    return prev;
            }
            if(a == cand)
            {
                ++cnt_cand;
                if(cnt_cand > 1)
                    return cand;
            }
        }
        return -1;
    }
};
