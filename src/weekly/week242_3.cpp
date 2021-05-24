
#include <string>
#include <vector>

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
                dp[i] = (sums[i - minJump + 1] - sums[max(i - maxJump, 0)]) > 0;
            sums[i + 1] = sums[i] + dp[i];
        }
        return dp[n - 1];
    }
};

#include <queue>

class Solution2 {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        queue<int> q;
        q.push(0);
        int r = 0;
        while(!q.empty())
        {
            int i = q.front();
            if(i == n - 1)
                return true;
            q.pop();
            for(int j = max(r + 1, i + minJump); j <= min(n - 1, i + maxJump); ++j)
            {
                if(s[j] == '0')
                    q.push(j);
                r = i + maxJump;
            }
        }
        return false;
    }
};
