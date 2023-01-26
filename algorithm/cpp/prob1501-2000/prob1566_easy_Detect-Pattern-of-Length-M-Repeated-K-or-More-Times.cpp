// prob1566: Detect Pattern of Length M Repeated K or More Times

/*
 * https://leetcode-cn.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int n = arr.size();
        // n = 5 [0..4], m = 3
        for(int i = 0; i <= n - k * m; ++i)
        {
            vector<int> cur(arr.begin() + i, arr.begin() + i + m);
            bool flag = true;
            for(int j = i + m; j < i + k * m; j += m)
            {
                for(int k = 0; k < m; ++k)
                    if(arr[j + k] != cur[k])
                    {
                        flag = false;
                        break;
                    }
                if(!flag)
                    break;
            }
            if(flag)
                return true;
        }
        return false;
    }
};
