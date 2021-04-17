// prob926: Flip String to Monotone Increasing

/*
 * https://leetcode-cn.com/problems/flip-string-to-monotone-increasing/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        if(n <= 0) return 0;
        vector<int> L(n + 1), R(n + 1);
        for(int i = 1; i <= n; ++i)
            L[i] = L[i - 1] + (S[i - 1] == '1');
        for(int i = n - 1; i >= 0; --i)
            R[i] = R[i + 1] + (S[i] == '0');
        int ans = n;
        for(int i = 0; i <= n; ++i)
            ans = min(ans, L[i] + R[i]);
        return ans;
    }
};
