// prob1422: Maximum Score After Splitting a String

/*
 * https://leetcode-cn.com/problems/maximum-score-after-splitting-a-string/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int maxScore(string s) {
        int n = s.size();
        vector<int> R(n); // R[i] := [i..n-1] 1 个数
        R[n - 1] = s[n - 1] == '1';
        for(int i = n - 2; i >= 0; --i)
            R[i] = R[i + 1] + (s[i] == '1');
        int ans = 0;
        int cnt = 0; // 0 个数
        for(int i = 0; i < n - 1; ++i)
        {
            cnt += s[i] == '0';
            ans = max(ans, cnt + R[i + 1]);
        }
        return ans;
    }
};
