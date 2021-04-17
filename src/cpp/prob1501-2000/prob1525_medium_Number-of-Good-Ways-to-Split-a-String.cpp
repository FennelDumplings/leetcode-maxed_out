// prob1525: Number of Good Ways to Split a String

/*
 * https://leetcode-cn.com/problems/number-of-good-ways-to-split-a-string/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numSplits(string s) {
        int n = s.size();
        vector<int> L(n), R(n);
        L[0] |= 1 << (s[0] - 'a');
        for(int i = 1; i < n; ++i)
            L[i] = L[i - 1] | (1 << (s[i] - 'a'));
        R[n - 1] |= 1 << (s[n - 1] - 'a');
        for(int i = n - 2; i >= 0; --i)
            R[i] = R[i + 1] | (1 << (s[i] - 'a'));
        int ans = 0;
        for(int i = 0; i < n - 1; ++i)
            if(cnt1(L[i]) == cnt1(R[i + 1]))
                ++ans;
        return ans;
    }

private:
    int cnt1(int x)
    {
        int ans = 0;
        while(x)
        {
            x &= x - 1;
            ++ans;
        }
        return ans;
    }
};
