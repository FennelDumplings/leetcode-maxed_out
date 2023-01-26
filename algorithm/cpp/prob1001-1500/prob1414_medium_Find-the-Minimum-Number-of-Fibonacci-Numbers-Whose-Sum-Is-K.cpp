// prob1414: Find the Minimum Number of Fibonacci Numbers Whose Sum Is K

/*
 * https://leetcode-cn.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        // 预处理所有 f <= k
        vector<int> f{1, 2};
        int prev = 1;
        while(f.back() + prev <= k)
        {
            int cur = f.back();
            f.push_back(cur + prev);
            prev = cur;
        }
        int ans = 0;
        int m = f.size();
        int it = m - 1;
        while(k > 0)
        {
            while(it >= 0 && f[it] > k)
                --it;
            if(it < 0)
                return -1;
            k -= f[it];
            ++ans;
        }
        return ans;
    }
};
