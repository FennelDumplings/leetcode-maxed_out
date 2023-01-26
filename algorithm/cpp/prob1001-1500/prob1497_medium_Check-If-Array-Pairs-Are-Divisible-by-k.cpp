// prob1497: Check If Array Pairs Are Divisible by k

/*
 * https://leetcode-cn.com/problems/check-if-array-pairs-are-divisible-by-k/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        // 余数为 0~k-1 计数
        vector<int> cnt(k);
        for(int num: arr)
            ++cnt[((num % k) + k) % k];
        if(cnt[0] & 1)
            return false;
        for(int i = 1; i + i <= k; ++i)
        {
            if(i + i == k)
            {
                if(cnt[i] & 1)
                    return false;
            }
            else
            {
                int j = k - i;
                if(cnt[i] != cnt[j])
                    return false;
            }
        }
        return true;
    }
};
