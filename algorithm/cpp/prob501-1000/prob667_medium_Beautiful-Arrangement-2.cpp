// prob667: Beautiful Arrangement II

/*
 * https://leetcode-cn.com/problems/beautiful-arrangement-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> constructArray(int n, int k) {
        vector<int> result(n, -1);
        int remain = n;
        result[n - 1] = n;
        --remain;
        while(k < remain)
        {
            result[remain - 1] = remain;
            --remain;
        }
        int l = 1, r = remain;
        int odd = 1;
        for(int i = remain; i >= 1; --i)
        {
            if(odd == 1)
                result[i - 1] = l++;
            else
                result[i - 1] = r--;
            odd ^= 1;
        }
        return result;
    }
};
