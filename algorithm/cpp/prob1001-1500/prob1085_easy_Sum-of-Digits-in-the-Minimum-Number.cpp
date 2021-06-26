// prob1085: Sum of Digits in the Minimum Number

/*
 * https://leetcode-cn.com/problems/sum-of-digits-in-the-minimum-number/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumOfDigits(vector<int>& A) {
        auto it = min_element(A.begin(), A.end());
        int t = *it;
        int ans = 0;
        while(t)
        {
            ans += t % 10;
            t /= 10;
        }
        return (ans & 1) ^ 1;
    }
};
