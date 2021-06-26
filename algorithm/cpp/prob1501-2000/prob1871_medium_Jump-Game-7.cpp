#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        vector<int> dp(n);
        dp[0] = 1;
        vector<int> sums(n + 1);
        sums[1] = 1;
        for(int i = 1; i < n; ++i)
        {
            if(s[i] == '0' && (i - minJump >= 0))
                if(sums[i - minJump + 1] - sums[max(i - maxJump, 0)] > 0)
                    dp[i] = 1;
            sums[i + 1] = sums[i] + dp[i];
        }
        return dp[n - 1];
    }
};
